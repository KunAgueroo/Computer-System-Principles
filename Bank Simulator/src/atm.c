#include "atm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "command.h"
#include "errors.h"
#include "trace.h"

//Harshavardhan Reddipalli
//CS 230
//Project #5
//Bank
//I have written comments for each function as to how it works.

// The following functions should be used to read and write
// groups of data over the pipes.  Use them in the implementation
// of the `atm` function below!

// Performs a `write` call, checking for errors and handlings
// partial writes. If there was an error it returns ERR_PIPE_WRITE_ERR.
// Note: data is void * since the actual type being written does not matter.

static int checked_write(int fd, void *data, int n) {
  char *d = (char *)data;
  while (n > 0) {
    int result = write(fd, data, n);
    if (result >= 0) {
      // this approach handles both complete and partial writes
      d += result;
      n -= result;
    } else {
      error_msg(ERR_PIPE_WRITE_ERR, "could not write message to bank");
      return ERR_PIPE_WRITE_ERR;
    }
  }
  return SUCCESS;
}

// Performs a `read` call, checking for errors and handlings
// partial read. If there was an error it returns ERR_PIPE_READ_ERR.
// Note: data is void * since the actual type being read does not matter.

static int checked_read(int fd, void *data, int n) {
  char *d = (char *)data;
  while (n > 0) {
    int result = read(fd, data, n);
    if (result >= 0) {
      // this approach handles both complete and partial reads
      d += result;
      n -= result;
    } else {
      error_msg(ERR_PIPE_READ_ERR, "could not read message from bank");
      return ERR_PIPE_READ_ERR;
    }
  }
  return SUCCESS;
}

// The `atm` function processes commands received from a trace
// file.  It communicates to the bank transactions with a matching
// ID.  It then receives a response from the bank process and handles
// the response appropriately.

int atm(int bank_out_fd, int atm_in_fd, int atm_id, Command *cmd) {
  byte c;
  int i, f, t, a;
  Command atmcmd;

  cmd_unpack(cmd, &c, &i, &f, &t, &a);

  int status = SUCCESS;

  // TODO1: your code here
  if(i != atm_id)//Checking if the ID unpacked is the same as the atm ID.
  { 
    return ERR_UNKNOWN_ATM;
  }
    else//If the ID is the same as the atm ID.
    {
      status = checked_write(bank_out_fd, cmd, MESSAGE_SIZE);//Used to send the cmd received from the trace file to the bank process.
      if(status != SUCCESS)//If the returned status code is not successful.
      {
        return status;
      }
      status = checked_read(atm_in_fd, &atmcmd, MESSAGE_SIZE);//Used to read the response from the bank.
      if(status != SUCCESS)//If the returned status code is not successful.
      {
        return status;
      }
      cmd_unpack(&atmcmd, &c, &i, &f, &t, &a);//If the status is successful,we unpack the command into it's individual parts.
      //I then set the status according to the command type using switch statements.
      switch (c)
      {//I changed to using switch statements as I believe the professor expected us to use these.
        case OK:
        status = SUCCESS;
        break;
        case NOFUNDS:
        status = ERR_NOFUNDS;
        break;
        case ACCUNKN:
        status = ERR_UNKNOWN_ACCOUNT;
        break;
        default://If none of these commands were received,we send an error message.
        error_msg(ERR_UNKNOWN_CMD,"Received unknown command");
        status = ERR_UNKNOWN_CMD;
        break;
      }//I didn't repeat this again as I've asked the TA and found out that what the question was asking was basically redundant.
    }
  return status;
}

int atm_run(const char *trace, int bank_out_fd, int atm_in_fd, int atm_id) {
  int status = trace_open(trace);
  if (status == -1) {
    error_msg(ERR_BAD_TRACE_FILE, "could not open trace file");
    return ERR_BAD_TRACE_FILE;
  }

  Command cmd;
  while (trace_read_cmd(&cmd)) {
    status = atm(bank_out_fd, atm_in_fd, atm_id, &cmd);

    switch (status) {
      // We continue if the ATM was unknown. This is ok because the trace
      // file contains commands for all the ATMs.
      case ERR_UNKNOWN_ATM:
        break;

      // We display an error message to the ATM user if the account
      // is not valid.
      case ERR_UNKNOWN_ACCOUNT:
        printf("ATM error: unknown account! ATM Out of service\n");
        break;

      // We display an error message to the ATM user if the account
      // does not have sufficient funds.
      case ERR_NOFUNDS:
        printf("not enough funds, retry transaction\n");
        break;

      // If we receive some other status that is not successful
      // we return with the status.
      default:
        if (status != SUCCESS) {
          printf("status is %d\n", status);
          return status;
        }
    }
  }

  trace_close();

  return SUCCESS;
}
