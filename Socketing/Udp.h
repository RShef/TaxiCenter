/************************************************************
* File description: UDP header file. the class inherit from	*
* socket. methods of udp socket type						*
************************************************************/

#ifndef UDP_H_
#define UDP_H_

#include "Socket.h"


class Udp: public Socket {
public:
	/***********************************************************************
	* function name: Udp												   *
	* The Input: Boolean, true - if server, false if client and port number*
	* The output: none										               *
	* The Function operation: creating new Udp						       *
	***********************************************************************/
	Udp(bool isServers, string udp, int port_num);
    Udp(bool isServers, int port_num);
	/***********************************************************************
	* function name: ~Udp												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: default destructor					       *
	***********************************************************************/
	//virtual ~Udp();
	/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
	int initialize();
	/***********************************************************************
	* function name: sendData											   *
	* The Input: string representing the data to send		               *
	* The output: int number representing the return status		           *
	* The Function operation: sending the input data to the socket         *
	* who connect to this socket.										   *
	***********************************************************************/
	int sendData(string data);
	/***********************************************************************
	* function name: recive	`											   *
	* The Input: none										               *
	* The output: int number representing the return status	               *
	* The Function operation: getting data from the other socket and print *
	* the data															   *
	***********************************************************************/
	int receiveData(char* buffer, int size);
};

#endif /* UDP_H_ */
