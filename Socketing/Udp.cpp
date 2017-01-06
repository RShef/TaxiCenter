/************************************************************
* File description: UDP implementation.						*
* the class inherit from socket. 							*
* methods of udp socket type								*
************************************************************/


#include "Udp.h"

/***********************************************************************
* function name: Udp												   *
* The Input: Boolean, true - if server, false if client and port number*
* The output: none										               *
* The Function operation: creating new Udp socket					   *
***********************************************************************/
Udp::Udp(bool isServers, string ip, int port_num) {
	this->port_number = port_num;
	this->isServer = isServers;
    this->ip_address = ip;
}
Udp::Udp(bool isServers, int port_num){
    this->port_number = port_num;
    this->isServer = isServers;
    this->ip_address = IP;
}
/***********************************************************************
* function name: ~Udp												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
//Udp::~Udp() {
	//this->~Socket();
//}

/***********************************************************************
* function name: initialize											   *
* The Input: none              										   *
* The output: int number representing the return status		           *
* The Function operation: initialize the Socket object by using 	   *
* socket(), and bind() if server					   				   *
***********************************************************************/
int Udp::initialize() {
	//creating new socket and getting his descriptor
	this->socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
	if (this->socketDescriptor < 0) {
		return ERROR_SOCKET;
	}
	//if server
	if (this->isServer) {
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(this->port_number);
		//bind
         bind(this->socketDescriptor, (struct sockaddr *) &sin, sizeof(sin));
		//if (res < 0) {
		//	return ERROR_BIND;
		//}
	}
	//return correct if there were no problems
	return CORRECT;
}

/***********************************************************************
* function name: sendData											   *
* The Input: string representing the data to send		               *
* The output: int number representing the return status		           *
* The Function operation: sending the input data to the socket         *
* who connect to this socket. check if send successfully				   *
***********************************************************************/
int Udp::sendData(string data) {
	//initialize the struct
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(this->ip_address.c_str());
	sin.sin_port = htons(this->port_number);
	const char * datas = data.c_str();
	int data_len = data.length() + 1;
	//send
	int sent_bytes = sendto(this->socketDescriptor,
			datas, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
	//cout << sent_bytes << endl;
	//check if send successfully
	if (sent_bytes < 0) {
		return ERROR_SEND;
	}
	//return correct if there were no problems
	return CORRECT;
}
/***********************************************************************
* function name: receive											   *
* The Input: none										               *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket check if  *
*  there were no error reciving and print							   *
***********************************************************************/
int Udp::receiveData(char* buffer, int size) {
	struct sockaddr_in to;
	unsigned int to_len = sizeof(struct sockaddr_in);
	//receive
	int bytes = recvfrom(this->socketDescriptor,
			buffer, size, 0, (struct sockaddr *) &to, &to_len);
	//set the port number to the new one which we get with the data
	this->port_number = ntohs(to.sin_port);
	//check if receive successfully

    //cout << bytes << endl;
	if (bytes < 0) {
		return -1;
	}
	//print the data
	//cout<<buffer<<endl;
	//return correct if there were no error
	return bytes;
}
