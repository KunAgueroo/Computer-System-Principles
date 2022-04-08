#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "hw.h"

//Harshavardhan Reddipalli
//CS 230
//Project #5
//Bank
//I have written comments for each function as to how it works.

// This is the main driver file for the bank simulation.
// The `main` function takes one argument, the name of a
// trace file to use.  The test directory contains a
// short sample trace that exercises at least one interesting
// case.

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s trace_file\n", argv[0]);
    exit(1);
  }

  int result = 0;
  int atm_count = 0;
  int account_count = 0;

  // open the trace file
  result = trace_open(argv[1]);
  if (result == -1) {
    printf("%s: could not open file %s\n", argv[0], argv[1]);
    exit(1);
  }

  // Get the number of ATMs and accounts:
  atm_count = trace_atm_count();
  account_count = trace_account_count();
  trace_close();

  // This is a table of atm_out file descriptors. It will be used by
  // the bank process to communicate to each of the ATM processes.
  int atm_out_fd[atm_count];

  // This is a table of bank_in file descriptors. It will be used by
  // the bank process to receive communication from each of the ATM processes.
  int bank_in_fd[atm_count];

  // TODO3: ATM PROCESS FORKING
  for(int i = 0; i < atm_count; i++){//The body of this part of the implementation is a for loop that iterates on i from 0 to atm_count-1.
    int to_atmfd[2];//Declare an integer array of size 2 for the ATM’s to-the-ATM pipe, called to_atmfd.
    pipe(to_atmfd);//Call pipe on this array to create the pipe.
    atm_out_fd[i] = to_atmfd[1];//Store in the ith entry of atm_out_fd the to-the-ATM’s output file descriptor, to_atmfd[1].
    int to_bankfd[2];//Same thing repeated for the ATM’s into-the-bank pipe.
    pipe(to_bankfd);
    bank_in_fd[i] = to_bankfd[0];
      if(fork() == 0)//If in the child process.
      {
        close(to_atmfd[1]);//Call close on the ATM’s output pipe file descriptor.
        close(to_bankfd[0]);//Call close on the bank’s input pipe file descriptor.
        int returnval = atm_run(argv[1], to_bankfd[1], to_atmfd[0], i);
          if(returnval != SUCCESS)//If the return value of atm_run is not SUCCESS then you should call error_print.
          {
            error_print();
          }
            exit(0);//To exit the child process.      
      }
      else 
      {//Simply close these as they are not used in the bank process.
        close(to_atmfd[0]);
        close(to_bankfd[1]);
      }
  }

  // TODO3: BANK PROCESS FORKING
      if(fork() == 0)//If in the child process.
      {
        bank_open(atm_count, account_count);//Call the bank_open function, providing it the atm_count and the account_count.
        int returnval = run_bank(bank_in_fd, atm_out_fd);
          if(returnval != SUCCESS)//If the return value of run_bank is not SUCCESS then you should call error_print.
          {
            error_print();
          }
      bank_dump();
      bank_close();
      exit(0);//To exit the child process. 
    }

  // Wait for each of the child processes to complete. We include
  // atm_count to include the bank process (i.e., this is not a
  // fence post error!)
  for (int i = 0; i <= atm_count; i++) {
    wait(NULL);
  }
  return 0;
}


