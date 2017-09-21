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

#define RCVBUFSIZE 512		/* The receive buffer size */
#define SNDBUFSIZE 512		/* The send buffer size */
#define BUFSIZE 40		/* Your name can be as many as 40 chars*/

/* The main function */
int main(int argc, char *argv[]) //called like ./server ipAddr port
{

    int serverSock;				/* Server Socket */
    int clientSock;				/* Client Socket */
    struct sockaddr_in changeServAddr;		/* Local address */
    struct sockaddr_in changeClntAddr;		/* Client address */
    unsigned short changeServPort;		/* Server port */
    unsigned int clntLen = sizeof(changeClntAddr);			/* Length of address data struct */

    char nameBuf[BUFSIZE];			/* Buff to store account name from client */
    int  balance;				/* Place to record account balance result */

    /* Account Name: mySavings, myChecking, myRetirement, myCollege  */
    char sav[] = "mySavings";
    char chk[] = "myChecking";
    char rtr[] = "myRetirement";
    char cll[] = "myCollege";

    if (argc != 3)
    {
    	printf("Incorrect number of arguments. The correct format is:\n serverIP serverPort");
    	exit(1);
    }
    //servIP = argv[2];
    changeServPort = (unsigned short)(strtol(argv[2], NULL, 10));


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
  recv(clientSock, nameBuf, BUFSIZE, 0);
  if (strcmp(nameBuf, sav) == 0) {
    balance = 10;
  } else if (strcmp(nameBuf, chk) == 0) {
    balance = 20;
  } else if (strcmp(nameBuf, rtr) == 0) {
    balance = 30;
  } else if (strcmp(nameBuf, cll) == 0) {
    balance = 40;
  } else {
    //something bad happened
  }

	/* Return account balance to client */
	/*	FILL IN	    */
  memset(&nameBuf, 0, BUFSIZE);
  sprintf(nameBuf, "%d", balance);
  send(clientSock, nameBuf, BUFSIZE, 0);

    }

}
