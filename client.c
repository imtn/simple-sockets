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

    /* Get the Account Name from the command line */
    if (argc != 4)
    {
    	printf("Incorrect number of arguments. The correct format is:\n\taccountName serverIP serverPort");
    	exit(1);
    }
    accountName = argv[1];
    memset(&sndBuf, 0, SNDBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Fill send buffer with account name */
    sprintf(sndBuf, accountName);

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
    serv_addr.sin_addr = inet_addr(servIP);

    /* Establish connecction to the server */
    /*	    FILL IN	 */
    connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    /* Send the string to the server */
    /*	    FILL IN	 */
    send(clientSock, sndBuf, SNDBUFSIZE, 0);


    /* Receive and print response from the server */
    /*	    FILL IN	 */
    recv(clientSock, rcvBuf, RCVBUFSIZE, 0);
    balance = atoi(rcvBuf);

    printf("%s\n", accountName);
    printf("Balance is: %i\n", balance);

    close(clientSock);
    return 0;
}
