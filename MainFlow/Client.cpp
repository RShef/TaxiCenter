//
// Created by Roy Shefi on 17/01/2017.
//

#include "Client.h"
#include "../Logging/easylogging++.h"

Client::Client(char *ip, int port) {
    this->ip = ip;
    this->port = port;
    this->client_socket = -1;
    this->connected = false;
    this->clock = new Clock();

}

int Client::Connect() {
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client_socket < 0) {
        //return an error represent error at this method
        perror("ERROR_SOCKET - in initialize()\n");
        return 0;
    }

    // Memset the connection details
    memset(&this->connection_details, 0, sizeof(this->connection_details));
    this->connection_details.sin_family = AF_INET;
    this->connection_details.sin_addr.s_addr = inet_addr(this->ip);
    this->connection_details.sin_port = htons(this->port);
    // Connect to a server
    if (connect(this->client_socket,
                (struct sockaddr*)&this->connection_details, sizeof(this->connection_details)) < 0) {
        perror("ERROR_CONNECT - in initialize()\n");
        return 0;
    } else {
        this->connected = true;
    }
    return 0;
}

int Client::sendData(string data) {
    size_t data_len = data.length();
    const char * datas = data.c_str();
    try {
        ssize_t sent_bytes = send(this->client_socket, datas, data_len, 0);
        if (sent_bytes < 0) {
            //return an error represent error at this method
            perror("ERROR_SEND - in sendData() on Client");
        }
        //return correct if there were no problem
        return (int)sent_bytes;
    }
    catch (...) {
        cout << ">> Error." << endl;
        return 0;
    }
}

int Client::receiveData() {
    try {
        memset(this->buffer, 0, sizeof(this->buffer));
        ssize_t read_bytes = recv(this->client_socket, this->buffer, sizeof(buffer), 0);
        //checking the errors
        if (read_bytes == 0) {
            //perror("CONNECTION_CLOSED - in receiveData() on Client\n");
            return 0;
        } else if (read_bytes < 0) {
            //return an error represent error at this method
            perror("ERROR_RECEIVE - in receiveData() on Client\n");
            exit(1);
        }
    }
    catch (...) {
        cout << ">> Error - No server" << endl;
    }
    return 0;
}

Client::~Client() {
    close(this->client_socket);
}

void Client::sendDriver(int id, int age, int status, int exp, int cabId) {
    //send Driver to server
    Driver* driver = new Driver (id, age, (Driver::Status) status, exp, cabId);
    this->driver = driver;
    stringstream ds;
    boost::archive::text_oarchive doa(ds);
    doa << driver;
    string buffer2 = ds.str();
    this->sendData(buffer2);
    LOG(INFO) << "Driver with id " << driver->getId() << " created and sent to server";
}

void Client::ListenToServer() {
    stringstream cs;

    if (this->receiveData() == 0) {
        if (strcmp(this->buffer, "cab") == 0) {
            this->receiveData();
            cs << this->buffer;
            boost::archive::text_iarchive cia(cs);
            Cab *cab;
            cia >> cab;
            this->driver->addCab(cab);
            LOG(INFO) << "Cab with ID " << cab->getId() << " received";
            return;
        }
        if (strcmp(this->buffer, "map") == 0) {
            this->receiveData();
            stringstream ms;
            ms << this->buffer;
            boost::archive::text_iarchive ia(ms);
            Grid *m;
            ia >> m;
            driver->addMap(m);
            LOG(INFO) << "Map received";
            return;
        }
        if (strcmp(this->buffer, "trip") == 0) {
            this->receiveData();
            //receive trip from server and assign to driver
            stringstream ts;
            ts << this->buffer;
            boost::archive::text_iarchive tia(ts);
            Trip *trip;
            tia >> trip;
            LOG(INFO) << "Trip with ID " << trip->getId() << " received";
            driver->getCab()->addTrip(trip);
            driver->setRoute();
            return;
        }
        if (strcmp(this->buffer, "go") == 0) {
            driver->moveOneStep();
            //driver->printLoc();
            this->clock->advance();
            return;
        }
        if (strcmp(this->buffer, "quit") == 0) {
            this->connected = false;
            return;
        }
    }
}