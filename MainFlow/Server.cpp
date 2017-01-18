//
// Created by Roy Shefi on 15/01/2017.
//

#include "Server.h"
#include "../Logging/easylogging++.h"

static int threadNum =0;
static int back =0;

Server::Server() {}

Server::Server(int po) {
    this->port_number = po;
    this->isServer = true;
    this->clock = new Clock();
    this->counter = 0;
    pthread_mutex_init(&this->connection_locker, 0);
    pthread_mutex_init(&this->list_locker, 0);
    //getting a socket descriptor and check if legal
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); // (IPv4 , TCP, flags) --> Socket Descriptor
    if (this->socketDescriptor < 0) {
        //return an error represent error at this method
        perror("ERROR_SOCKET - in initialize()\n");
    }
    //if server
    if (this->isServer) {
        //initialize the struct
        struct sockaddr_in sin;                     // ipv4 socket address structure
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;                   // IPv4 version
        sin.sin_addr.s_addr = INADDR_ANY;           // binds to all ip address of the host
        sin.sin_port = htons(this->port_number);    // pass Server Post number
        //bind
        if (::bind(this->socketDescriptor,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
            //return an error represent error at this method
            perror("ERROR_BIND - in initialize()\n");
        }
        //listen
        if (listen(this->socketDescriptor, this->backLog) < 0) {
            //return an error represent error at this method
            perror("ERROR_LISTEN - in initialize()\n");
        }
        // start to accept first client (get 0 if failed)

        //if client
    } else {
        struct sockaddr_in sin;                                          // ipv4 socket address structure
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;                                        // IPv4 version
        sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());     // get IP address from DEFINE IP number
        sin.sin_port = htons(this->port_number);                         // pass port number
        if (connect(this->socketDescriptor,
                    (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            //return an error represent error at this method
            perror("ERROR_CONNECT - in initialize()\n");
        }
    }
}

void Server::setUp(int x, int y, vector <GridPoint*> obstacles){
    this->m = new Grid(x, y);
    LOG(INFO) << "Grid of " << x  << "X" << y << " created";
    this->tc = new TaxiCenter();
    this->buff1 = new vector<char *>;
    this->obstacles = obstacles;
    LOG(INFO) << obstacles.size() << " obstacles created";
}

void* Server::threadFunction(void* elm) {
    ClientData * d = (ClientData*) elm;
    memset(d->buffer, 0, sizeof(d->buffer));
    d->th->receiveData(d->buffer, sizeof(d->buffer), d->client, d);
}

void Server::one(int numDrivers) {
    Driver *d;
    void* st;

    for (int i = 0; i< numDrivers; i++) {
        pthread_t thread;
        ClientData* data = new ClientData();

        this->acceptOneClient(data);

        memset(data->buffer, 0, sizeof(buffer));
        data->th = this;
        pthread_create(&thread, NULL,threadFunction, (void*) data);
    }
    // receive driver from client
    while (clientDis.size() < numDrivers) {}

    int i;
    for(i = 0; i < numDrivers; i++) {
        stringstream ds;
        ds << clientDis.at(i)->buffer;
        boost::archive::text_iarchive ia(ds);
        ia >> d;
        drivers.push_back(d);
        LOG(INFO) << "Driver with ID " << d->getId() << " received";
        tc->addDriver(d);
        d->addCab(tc->getCabById(d->getCabId()));
        tc->getDriverById(d->getId())->addMap(m);
        clientDis.at(i)->driverIdC = d->getId();

        //send cabs to drivers
        this->clientDis.at(i)->th->sendData("cab", this->clientDis.at(i)->client);
        usleep(500000);
        stringstream cs;
        boost::archive::text_oarchive coa(cs);
        coa << cabs.at(i);
        buffer2 = cs.str();
        this->clientDis.at(i)->th->sendData(buffer2, this->clientDis.at(i)->client);
        LOG(INFO) << "Cab " << cabs.at(i)->getId() << " sent to driver " << drivers.at(i)->getId();
        usleep(500000);

        //send map to clients
        this->clientDis.at(i)->th->sendData("map", this->clientDis.at(i)->client);
        usleep(500000);
        stringstream ms;
        boost::archive::text_oarchive oa(ms);
        oa << m;
        buffer2 = ms.str();
        this->clientDis.at(i)->th->sendData(buffer2, this->clientDis.at(i)->client);
        usleep(500000);
        LOG(INFO) << "Map sent to driver " << drivers.at(i)->getId();
        d->addMap(m);
    }
}

void Server::two(int id, int startX, int startY, int endX, int endY, int numPass, double tariff, int startTime) {
    GridPoint *start = new GridPoint (startX, startY);
    GridPoint *end = new GridPoint(endX, endY);
    vector<Passenger*> pass;
    // Create passengers.
    for (int i = 0; i < numPass; ++i) {
        pass.push_back(new Passenger(*start, *end));
    }

    Trip *trip = new Trip(id, start, end, numPass, tariff, pass, startTime);
    LOG(INFO) << "New Trip with ID " << id << " created";
    trip->setMap(this->m);

    pthread_create(&thread[threadNum], NULL,Trip::calRoute, (void*) trip);
    threadNum++;

    // Add trip to the taxi center.
    tc->addTrip(trip);
    trips.push_back(trip);
    counter++;
}

void Server::three(int id, int type, int car, int color) {
    // Checking which type of cab it is.
    if (type == 1) {
        Cab *sc = new StandardCab(id, (Cab::Car) car, (Cab::Colors) color);
        LOG(INFO) << "New Standard cab with ID " << id << " created";
        // Add cab to taxi center.
        tc->addCab(sc);
        cabs.push_back(sc);
    } else {
        Cab *lc = new LuxuryCab(id, (Cab::Car) car, (Cab::Colors) color);
        LOG(INFO) << "New Luxury cab with ID " << id << " created";
        tc->addCab(lc);
        cabs.push_back(lc);
    }
}

void Server::four(int id) {
    tc->printDriverLocById(id);
}

void Server::seven() {
    for (int i = 0; i < drivers.size(); ++i) {
        //clients.at(i)->sendData("quit",0);
        ClientData *cl = this->findClientById(drivers.at(i)->getId());
        cl->th->sendData("quit", cl->client);
    }
    delete(tc);
    delete(m);
    drivers.clear();
    cabs.clear();
    trips.clear();
    obstacles.clear();
    clients.clear();
}

void Server::nine() {
    for (int i = 0; i < trips.size(); ++i) {
        // If the trip has not been assigned.
        if (clock->getTime() == trips.at(i)->getStartTime() - 1) {
            if (!trips.at(i)->isAssigned()) {
                // wait for trip.
                LOG(DEBUG) << "Starting trip calculation";
                pthread_join(thread[i],NULL);
                LOG(DEBUG) << "Trip calculation done";
                // Get closest driver.
                Driver *temp = tc->whoIsClose(trips.at(i));
                temp->getCab()->addTrip(trips.at(i));
                temp->setRoute();
                //prepare client to receive trip
                ClientData *cl = this->findClientById(temp->getId());
                cl->th->sendData("trip", cl->client);
                usleep(500000);
                //send trip to client
                stringstream ts;
                boost::archive::text_oarchive toa(ts);
                Trip *tt = trips.at(i);
                toa << tt;
                buffer2 = ts.str();
                cl->th->sendData(buffer2, cl->client);
                usleep(500000);
                LOG(INFO) << "Trip " << tt->getId() << " sent to driver " << temp->getId();
                // set trip as assigned
                trips.at(i)->assign();
            }
        }
    }
    for (int i = 0; i < this->drivers.size(); ++i) {
        Driver *temp = this->drivers.at(i);
        if (temp->getCab()->getTrip() != NULL && !temp->getCab()->getTrip()->isDone()) {
            if (temp->getCab()->getTrip()->getStartTime() <= clock->getTime()) {
                ClientData *cl = this->findClientById(temp->getId());
                tc->sendTaxi(temp);
                cl->th->sendData("go", cl->client);
                usleep(500000);
            }
        }
    }
    clock->advance();
}

void Server::PreWork() {

    // construct obstacles

}

int Server::sendData(string data, int clientDescriptor) {
    size_t data_len = data.length();
    const char * datas = data.c_str();
    ssize_t sent_bytes = send(this->isServer ? clientDescriptor : this->socketDescriptor, datas, data_len, 0);
    if (sent_bytes < 0) {
        string host = "";
        if (isServer) {
            host = "Server\n";
        } else {
            host = "Client\n";
        }
        host = "ERROR_SEND - in sendData() on " + host;
        //return an error represent error at this method
        perror(host.c_str());
    }
    //return correct if there were no problem
    return (int)sent_bytes;
}

int Server::receiveData(char* buffer, int size, int clientDescriptor, void* d) {
    ssize_t read_bytes = recv(this->isServer ? clientDescriptor : this->socketDescriptor, buffer, size, 0);
    //checking the errors
    if (read_bytes <= 0) {
        string host = "";
        if (isServer) {
            host = "Server\n";
        } else {
            host = "Client\n";
        }
        if (read_bytes == 0) {
            host = "CONNECTION_CLOSED - in receiveData() on " + host;
            perror(host.c_str());
            exit(1);
        } else {
            host = "ERROR_RECEIVE - in receiveData() on " + host;
            //return an error represent error at this method
            perror(host.c_str());
            exit(1);
        }
    }
    if (d != NULL) {
        ClientData *ddd = (ClientData *) d;
        pthread_mutex_lock(&list_locker);
        this->clientDis.push_back(ddd);
        pthread_mutex_unlock(&list_locker);
        pthread_exit(NULL);
    }
    //return correct if there were no problem
    return (int)read_bytes;
}

void Server::acceptOneClient(ClientData* data){
    int clientDescriptor = 0;
    int client_sin;
    unsigned int addr_len = sizeof(client_sin);
    while (clientDescriptor <= 0) {
        clientDescriptor = accept(this->socketDescriptor,
                                  (struct sockaddr *) &client_sin, &addr_len);
    }
    data->client = clientDescriptor;
    data->client_socket = client_sin;
    data->client_size = addr_len;
    data->online = true;
    data->th = this;

    if (clientDescriptor < 0) {
        //return an error represent error at this method
        perror("ERROR_CONNECT - in acceptOneClient()\n");
        exit(1);
    }
}