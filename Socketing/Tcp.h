//
// Created by Roy Shefi on 13/01/2017.
//

/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef TCP_H_
#define TCP_H_

#include "Socket.h"
#include <vector>

class Tcp: public Socket {
 private:
    int descriptorCommunicateClient;
 public:
    struct ClientData
    {
      int client_socket;
      int client;
      unsigned int client_size;
      bool online;
      Tcp * tcp;
      char buffer[800000];
      void* th;
    };
    vector<char[]> *buff;

    pthread_mutex_t connection_locker;
    pthread_mutex_t list_locker;
    /***********************************************************************
    * function name: Tcp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Tcp						       *
    ***********************************************************************/
    Tcp(bool isServers, int port_num);
    //Tcp(bool isServers, int port_num, int ip);

    /***********************************************************************
    * function name: ~Tcp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~Tcp();
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
    * who connect to this socket. 										   *
    ***********************************************************************/
    int sendData(string data) { return  0;};
    /***********************************************************************
    * function name: recive	`											   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    int reciveData(char* buffer, int size) { return  0;};

    int receiveData(char *buffer, int size, int clientDescriptor, void* d);
    int sendData(string data, int clientDescriptor);
    void acceptOneClient(ClientData* d);
    static void* threadRecive(void* data);
};

#endif /* TCP_H_ */
