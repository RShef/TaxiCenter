//
// Created by Roy Shefi on 15/01/2017.
//

#ifndef PART_2_SERVER_H
#define PART_2_SERVER_H

#include <iostream>
#include <vector>
#include "../Socketing/Socket.h"
#include <tcl.h>

using namespace std;

class Server : public Socket {
private:
    struct ClientData {
      int client_socket;
      int client;
      unsigned int client_size;
      bool online;
      char buffer[800000];
      Server* thisServer;
      int driverIdC;
    };

    char buffer[6000];
    bool online;



 public:

    pthread_mutex_t connection_locker;
    pthread_mutex_t list_locker;
    Server();
    vector<ClientData*> clientDis;
    Server(int po);

    void receiveMessages(int numDrivers);


    static void* threadFunction(void* elm);



    int initialize(){};

    int sendData(string data,int clientDescriptor);

    void acceptOneClient(ClientData* data);

    int receiveData(ClientData* data);
    void quit();
    
    ClientData* findClientById(int id);

};

#endif //PART_2_SERVER_H
