Call Client with
  ./client accountName serverIP serverPort requestType [amount]
where:
  accountName is either mySavings, myChecking, myRetirement, or myCollege
  serverIP is the IP address of the server
  serverPort is the Port number of the server to use
  requestType is either BAL or WITHDRAW
  amount is an integer number representing the amount to withdraw. It is required when performing a WITHDRAW request.

Call Server with
  ./server serverPort
where:
  serverPort is the port number of the server to use

Improper arguments result in undefined behavior.

Example call of server:
  ./server 5000

Example calls of client:
  ./client mySavings 127.0.0.1 5000 BAL
  ./client mySavings 127.0.0.1 5000 WITHDRAW 100
