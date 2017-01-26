/************************************************************
* File description: Socket class header file. 				*
* contains socket properties as members, declaration on 	*
* methods, and const numbers using by all classes which		*
* inherit from Socket class									*
************************************************************/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

//return values to each function if error happened
#define CORRECT 0
#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_LISTEN 3
#define ERROR_CONNECT 4
#define ERROR_SEND 5
#define ERROR_RECIVE 6
#define ERROR_ACCEPT 7
#define CONNECTION_CLOSED 8

#define IP "127.0.0.1"

class Socket {
 public:
	//true is the socket is for a server, false if for a client
	bool isServer;
	//the socket descriptor return from sock()
	int socketDescriptor;
	//ip address
	int backLog;
	//port number
	int port_number;

public:
	string ip_address = IP;
	bool on;

	/***********************************************************************
	* function name: Socket												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: creating new Socket object			       *
	***********************************************************************/
	Socket();
	/***********************************************************************
	* function name: ~Socket											   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: default destructor					       *
	***********************************************************************/
	virtual ~Socket(){};
	/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor. pure virtual method							   *
	***********************************************************************/
	virtual int initialize(){};
	/***********************************************************************
	* function name: sendData											   *
	* The Input: string representing the data to send		               *
	* The output: int number representing the return status		           *
	* The Function operation: sending the input data to the socket         *
	* who connect to this socket. pure virtual method					   *
	***********************************************************************/
	virtual int sendData(string data, int a){};
	/***********************************************************************
	* function name: receiveData 										   *
	* The Input: none										               *
	* The output: int number representing the return status	               *
	* The Function operation: getting data from the other socket and print *
	* the data															   *
	***********************************************************************/
	friend class Server;
	 virtual int receiveData(){};


};

#endif /* SOCKET_H_ */
