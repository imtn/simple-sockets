/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:	Niandong Xu
* PROJECT:	CS 3251 Project 1 - Professor Jun Xu
* DESCRIPTION:	Network Client Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>		    /* for printf() and fprintf() */
#include <sys/socket.h>		    /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>		    /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Constants */
#define RCVBUFSIZE 512		    /* The receive buffer size */
#define SNDBUFSIZE 512		    /* The send buffer size */
#define REPLYLEN 32

/* The main function */
int main(int argc, char *argv[])
{

    int clientSock;		    /* socket descriptor */
    struct sockaddr_in serv_addr;   /* server address structure */

    char *accountName;		    /* Account Name: mySavings, myChecking, myRetirement, myCollege  */
    char *servIP;		    /* Server IP address  */
    unsigned short servPort;	    /* Server Port number */


    char sndBuf[SNDBUFSIZE];	    /* Send Buffer */
    char rcvBuf[RCVBUFSIZE];	    /* Receive Buffer */

    int balance;		    /* Account balance */
    char *requestType;
    char *withdrawAmount;

    /* Get the Account Name from the command line */
    if (argc != 5 && argc != 6)
    {
    	printf("Incorrect number of arguments. The correct format is:\n\taccountName serverIP serverPort requestType [amount]");
    	exit(1);
    }
    accountName = argv[1];
    requestType = argv[4];

    memset(&sndBuf, 0, SNDBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Fill send buffer with account name */
    if (strcmp(requestType, "WITHDRAW") == 0) {
      withdrawAmount = argv[5];
      sprintf(sndBuf, "%s %s %s", accountName, requestType, withdrawAmount);
    } else {
      sprintf(sndBuf, "%s %s", accountName, requestType);
    }

    /* Get the addditional parameters from the command line */
    /*	    FILL IN	*/
    servIP = argv[2];
    servPort = (unsigned short)(strtol(argv[3], NULL, 10));

    /* Create a new TCP socket*/
    /*	    FILL IN	*/
    clientSock = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct the server address structure */
    /*	    FILL IN	 */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(servPort);
    serv_addr.sin_addr.s_addr = inet_addr(servIP);

    /* Establish connecction to the server */
    /*	    FILL IN	 */
    connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    /* Send the string to the server */
    /*	    FILL IN	 */
    send(clientSock, sndBuf, SNDBUFSIZE, 0);


    /* Receive and print response from the server */
    /*	    FILL IN	 */
    recv(clientSock, rcvBuf, RCVBUFSIZE, 0); //receive amount status
    balance = atoi(strtok(rcvBuf, " "));
    char *status = strtok(NULL, " ");

    if (strcmp(requestType, "BAL") == 0) {
      printf("%s\n", accountName);
      printf("Balance is: %i\n", balance);
    } else if (strcmp(requestType, "WITHDRAW") == 0) {
      if (strcmp(status, "SUCCESS") == 0) {
        printf("Withdrawal Successful\n");
      } else if (strcmp(status, "FAILURE") == 0) {
        printf("Withdrawal Not Successful");
      } else {
        fprintf(stderr, "Unable to decipher withdrawal status");
        exit(1);
      }
    } else {
      fprintf(stderr, "Unable to detect request type");
      exit(1);
    }


    close(clientSock);
    return 0;
}
