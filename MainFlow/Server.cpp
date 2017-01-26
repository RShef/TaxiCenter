//
// Created by Roy Shefi on 15/01/2017.
//

#include "Server.h"
#include "../Logging/easylogging++.h"


Server::Server() {}

Server::Server(int port) {
    this->port_number = port;
    this->online = true;

    pthread_mutex_init(&this->connection_locker, 0);
    pthread_mutex_init(&this->list_locker, 0);
    //getting a socket descriptor and check if legal
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); // (IPv4 , TCP, flags) --> Socket Descriptor
    if (this->socketDescriptor < 0) {
        //return an error represent error at this method
        perror("ERROR_SOCKET - in initialize()\n");
    }
    //initialize the struct
    struct sockaddr_in sin;                     // ipv4 socket address structure
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;                   // IPv4 version
    sin.sin_addr.s_addr = INADDR_ANY;           // binds to all ip address of the host
    sin.sin_port = htons(this->port_number);    // pass Server Post number
    //bind
    if (::bind(this->socketDescriptor, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        //return an error represent error at this method
        perror("ERROR_BIND - in initialize()\n");
    }
    //listen
    if (listen(this->socketDescriptor, this->backLog) < 0) {
        //return an error represent error at this method
        perror("ERROR_LISTEN - in initialize()\n");
    }

}



void* Server::threadFunction(void* elm) {
    ClientData * data = (ClientData*) elm;
    memset(data->buffer, 0, sizeof(data->buffer));
    data->thisServer->receiveData(data);
}

void Server::receiveMessages(int numDrivers) {
    // receive message from client
    for (int i = 0; i < numDrivers; i++) {
        pthread_t thread;
        ClientData *data = new ClientData();
        this->acceptOneClient(data);
        memset(data->buffer, 0, sizeof(buffer));
        data->thisServer = this;
        pthread_create(&thread, NULL, threadFunction, (void *) data);
    }
}

int Server::sendData(string data, int clientDescriptor) {
    size_t data_len = data.length();
    const char *datas = data.c_str();
    ssize_t sent_bytes = send(clientDescriptor, datas, data_len, 0);
    if (sent_bytes < 0) {
        string host = "ERROR_SEND - in sendData() on Server";
        //return an error represent error at this method
        perror(host.c_str());
    }
    //return correct if there were no problem
    return (int) sent_bytes;
}

int Server::receiveData(ClientData *data) {
    ssize_t read_bytes = 0;
    pthread_mutex_lock(&list_locker);
    clientDis.push_back(data);
    pthread_mutex_unlock(&list_locker);
    while (data->thisServer->online && data->online) {
         read_bytes = recv(data->client, data->buffer, sizeof(data->buffer), 0);
        //checking the errors
        if (read_bytes <= 0) {
            if (read_bytes == 0) {
                string host = "CONNECTION_CLOSED - in receiveData() on Server";
                perror(host.c_str());
                exit(1);
            }
        }
        if (strcmp(data->buffer, "quit")) {
            data->online = false;
            for (int i =0; i<clientDis.size(); i++) {
                pthread_mutex_lock(&list_locker);
                if (clientDis[i]->client == data->client) {
                   clientDis.erase(clientDis.begin() +i);
                }
                pthread_mutex_unlock(&list_locker);

            }
        }
    }


    //return correct if there were no problem
    return (int) read_bytes;
}

void Server::acceptOneClient(ClientData *data) {
    int clientDescriptor = 0;
    int client_sin = 0;
    unsigned int addr_len = sizeof(client_sin);
    while (clientDescriptor <= 0) {
        clientDescriptor = accept(this->socketDescriptor,
                                  (struct sockaddr *) &client_sin, &addr_len);
    }
    data->client = clientDescriptor;
    data->client_socket = client_sin;
    data->client_size = addr_len;
    data->online = true;
    data->thisServer = this;

    if (clientDescriptor < 0) {
        //return an error represent error at this method
        perror("ERROR_CONNECT - in acceptOneClient()\n");
        exit(1);
    }
}
Server::ClientData* Server::findClientById(int id){
    for (int i = 0; i < this->clientDis.size(); i++) {
        if ( id == clientDis.at(i)->driverIdC){
            return clientDis.at(i);
        }
    }
};
void Server::quit() {
    this->online = false;
    for(int i =0; i<clientDis.size(); i++){
        sendData("quit", clientDis[i]->client);
        delete(clientDis[i]);
    }
    //clientDis.erase(clientDis.begin(), clientDis.end());

}
