//Harshavardhan Reddipalli
//CS 230
//Project #6
//String Bot
//I have written comments for each function as to how it works.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAXLINE 8192 /* Max text line length */

int open_clientfd(char *hostname, int port) {
// The client's socket file descriptor.
int clientfd;
// serveraddr is used to record the server information (IP address and port number).   
struct sockaddr_in serveraddr;
printf("Echo Client is creating a socket.\n");
// First, we create the socket file descriptor with the given protocol and protocol family.
if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
// The socket API requires that you zero out the bytes!
bzero((char *)&serveraddr, sizeof(serveraddr));
// Record the protocol family we are using to connect.
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = inet_addr(hostname);
// Convert the port from host byte order to network byte order and store this in the server address structure.
serveraddr.sin_port = htons(port);
printf("Echo Client is trying to connect to %s (%s:%d).\n", hostname,inet_ntoa(serveraddr.sin_addr), port);
// Establish a connection with the server.
if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) return -1;
  printf("Echo Client connected.\n");
// Return the connected file descriptor.
  return clientfd;
}

int main(int argc, char **argv) {
// The client socket file descriptor.
int clientfd;
// The port number.
int port;
// Variable to store the host/server domain name.
char *host;
// Variable to store my UMass NETID.
char *netid;
// A buffer to receive data from the server.
char buf[MAXLINE];
// First, we check the program arguments:
if (argc != 4)
  {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }
// First argument is netid, second is port, third is the host:
  host = argv[3];
  port = atoi(argv[2]);
// I initially set it to argv[1] but changed later to my email as I believing seeing in piazza that it has to be hard coded.
  netid = "hreddipalli@umass.edu";
// Open the client socket file descriptor given the host and port:
  clientfd = open_clientfd(host, port);
// A character array to store our initial message "cs230 HELLO <NETID>@umass.edu\n".
  char stringx[MAXLINE];
  strcpy(stringx, "cs230 HELLO ");
  strcat(stringx, netid);
  strcat(stringx, "\n");
  printf("%s", stringx);
// To check if our message is being sent to the server.
if(send(clientfd, stringx, strlen(stringx), 0) < 0) 
  {
    exit(0);
  }
// Used 1 here to have an infinite loop.
while(1) {
// To make sure the server receives our message.
  recv(clientfd, buf, MAXLINE, 0);
// Print our the message sent from the server "cs230 STATUS <SHIFT> <MESSAGE>\n". 
  printf("%s", buf);
// Created a pointer to store our message.  
  char *ptr = buf;
// For the "cs230" part of our message.
  char cs230[MAXLINE];
// For the "STATUS" part of our message.
  char status[MAXLINE];
// For the Status number part of our message,which is our shift key.
  char statusnum[MAXLINE];
// For the actual part of the message we perform the shifts on.
  char message[MAXLINE];
// Used to put each part of the message in it's corresponding category.
  sscanf(ptr,"%s %s %s %s",cs230,status,statusnum,message);
  char character;
  int key = atoi(statusnum);
// Here we perform basic Caesar cipher encryption.
  for(int i = 0; i < strlen(message); i++)
  {
    character = message[i];
    if(character >= 'A' && character <= 'Z')
    {
      character = character + key;
      if(character > 'Z')
      {
        character = character - 'Z' + 'A' - 1;
      }
      message[i] = character;
    }
  }
// Make a new buffer to store the message we have to send back.
    char newbuf[MAXLINE] = "cs230 ";
    strcat(newbuf,message);
    strcat(newbuf,"\n");
// Sends our message back to the server until this loop runs.
    send(clientfd, newbuf, strlen(newbuf), 0);
    }
// Close the file descriptor:
  close(clientfd);
  exit(0);
}



