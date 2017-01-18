//
// Created by Oded Thaller on 24/12/2016.
//

#include "Client.h"
#include "../Logging/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

/**
 * Find the status by Char given.
 * @param statusInput - Char input.
 * @return - the int value that the char represents.
 */
int findStatus(char statusInput) {
    if (statusInput == 'S') {
        return 0;
    } else if (statusInput == 'M') {
        return 1;
    } else if (statusInput == 'D') {
        return 2;
    } else {
        return 3;
    }
}

int main(int argc, char *argv[]) {

    easyloggingpp::Configurations confFromFile("../Logging/Client_Config");
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile);
    LOG(INFO) << "Client starting";

    int id, age, exp, cabId;
    char stat;
    char comma[4];
    char buffer1[8000];

    Client* client = new Client(argv[1],atoi(argv[2]));
    client->Connect();

    // Crate a new driver by user input.
    cin >> id >> comma[0] >> age >> comma[1] >> stat >> comma[2] >> exp >> comma[3] >> cabId;
    int status = findStatus(stat);
    client->sendDriver(id, age, (Driver::Status) status, exp, cabId);

    while (client->connected) {
        client->ListenToServer();
    }
    client->~Client();
    LOG(INFO) << "Client exiting... Goodbye";
    return 0;
}