/*///////////////////////////////////////////////////////////
*
* FILE:		server.c
* AUTHOR:	Niandong Xu
* PROJECT:	CS 3251 Project 1 - Professor Jun Xu
* DESCRIPTION:	Network Server Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/*Included libraries*/

#include <stdio.h>	  /* for printf() and fprintf() */
#include <sys/socket.h>	  /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>	  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>	  /* supports all sorts of functionality */
#include <unistd.h>	  /* for close() */
#include <string.h>	  /* support any string ops */
#include <time.h>

#define RCVBUFSIZE 512		/* The receive buffer size */
#define SNDBUFSIZE 512		/* The send buffer size */
#define BUFSIZE 40		/* Your name can be as many as 40 chars*/

void push(int (*arr)[3], int *val); //used for pushing a value to a timeout array

/* The main function */
int main(int argc, char *argv[]) //called like ./server port
{

    int serverSock;				/* Server Socket */
    int clientSock;				/* Client Socket */
    struct sockaddr_in changeServAddr;		/* Local address */
    struct sockaddr_in changeClntAddr;		/* Client address */
    unsigned short changeServPort;		/* Server port */
    unsigned int clntLen = sizeof(changeClntAddr);			/* Length of address data struct */

    char nameBuf[BUFSIZE];			/* Buff to store account name from client */

    /* Account Name: mySavings, myChecking, myRetirement, myCollege  */
    char sav[] = "mySavings";
    char chk[] = "myChecking";
    char rtr[] = "myRetirement";
    char cll[] = "myCollege";

    int savBal = 1000;
    int chkBal = 2000;
    int rtrBal = 3000;
    int cllBal = 4000;

    int savTime[3] = {0,0,0};
    int chlTime[3] = {0,0,0};
    int rtrTime[3] = {0,0,0};
    int cllTime[3] = {0,0,0};

    if (argc != 2)
    {
    	printf("Incorrect number of arguments. The correct format is:\n serverPort\n");
    	exit(1);
    }
    changeServPort = (unsigned short)(strtol(argv[1], NULL, 10));

    /* Create new TCP Socket for incoming requests*/
    /*	    FILL IN	*/
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct local address structure*/
    /*	    FILL IN	*/
    changeServAddr.sin_family = AF_INET;
    changeServAddr.sin_port = htons(changeServPort);
    changeServAddr.sin_addr.s_addr = INADDR_ANY;

    /* Bind to local address structure */
    /*	    FILL IN	*/
    bind(serverSock, (struct sockaddr *) &changeServAddr, sizeof(changeServAddr));

    /* Listen for incoming connections */
    /*	    FILL IN	*/
    listen(serverSock, 32);
    /* Loop server forever*/
    while(1)
    {

	/* Accept incoming connection */
	/*	FILL IN	    */
  clientSock = accept(serverSock, (struct sockaddr *) &changeClntAddr, &clntLen);

	/* Extract the account name from the packet, store in nameBuf */
	/* Look up account balance, store in balance */
	/*	FILL IN	    */
  recv(clientSock, nameBuf, BUFSIZE, 0); //message is "accountName requestType [amount]"
  int timestamp = time(NULL);
  char *accountName = strtok(nameBuf, " ");
  char *requestType = strtok(NULL, " ");
  char *status = "FNF"; //file not found
  int amount;
  int *currentBal;
  if (strcmp(accountName, sav) == 0) {
    currentBal = &savBal;
  } else if (strcmp(accountName, chk) == 0) {
    currentBal = &chkBal;
  } else if (strcmp(accountName, rtr) == 0) {
    currentBal = &rtrBal;
  } else if (strcmp(accountName, cll) == 0) {
    currentBal = &cllBal;
  }

  if (strcmp(requestType, "BAL") == 0) {
    //do nothing, currentBal points to balance
  } else if (strcmp(requestType, "WITHDRAW") == 0) {
    amount = atoi(strtok(NULL, " "));
    if (amount > *currentBal) {
      status = "FAILURE";
      //failure
    } else { //enough money for withdrawal
      *currentBal = *currentBal - amount;
      status = "SUCCESS";
    }
  } else {
    //something bad happened
    fprintf(stderr, "if else tree failed\n");
  }

	/* Return account balance to client */
	/*	FILL IN	    */
  memset(&nameBuf, 0, BUFSIZE);
  sprintf(nameBuf, "%d %s", *currentBal, status); //return something that looks like "amount status", where amount is relevant in BAL requests, and status is relevant in WITHDRAW request
  send(clientSock, nameBuf, BUFSIZE, 0);

    }

}

void push(int (*arr)[3], int *val) {
  (*arr)[0] = (*arr)[1];
  (*arr)[1] = (*arr)[2];
  (*arr)[2] = *val;
}
