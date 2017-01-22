//
// Created by Roy Shefi on 17/01/2017.
//

#ifndef PART_2_CLIENT_H
#define PART_2_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../TaxiStation/Driver.h"
#include "../TaxiStation/Vehicles/Cab.h"
#include "../World/Grid.h"
#include "../World/Clock.h"
#include "../TaxiStation/Vehicles/StandardCab.h"
#include "../TaxiStation/Vehicles/LuxuryCab.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

class Client {
 public:
    Client(char* ip, int port);
    void sendDriver(int id, int age, int stat, int exp, int cabId);
    void ListenToServer();
    int sendData(string data);
    int receiveData();
    int Connect ();
    virtual ~Client();
    char buffer[800000];
    bool connected;
    Driver * driver;
    Clock *clock;

 private:
    char* ip;
    int port;
    int client_socket;
    struct sockaddr_in connection_details;
    string name;
};

#endif //PART_2_CLIENT_H
