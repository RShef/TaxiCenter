//
// Created by Oded Thaller on 11/12/2016.
//

#define _ELPP_THREAD_SAFE

#include <iostream>
#include "Server.h"
#include "../Logging/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

/**
* Find the type of car by Char given.
* @param carInput - Char input.
* @return - the int value that the char represents.
*/
int findCar(char carInput) {
    if (carInput == 'H') {
        return 0;
    } else if (carInput == 'S') {
        return 1;
    } else if (carInput == 'T') {
        return 2;
    } else if (carInput == 'F') {
        return 3;
    } else {
        return -1;
    }
}

/**
* Find the type of color of the car by Char given.
* @param carInput - Char input.
* @return - the int value that the char represents.
*/
int findColor(char colorInput) {
    if (colorInput == 'R') {
        return 0;
    } else if (colorInput == 'B') {
        return 1;
    } else if (colorInput == 'G') {
        return 2;
    } else if (colorInput == 'P') {
        return 3;
    } else if (colorInput == 'W') {
        return 4;
    } else {
        return -1;
    }
}

/**
* Check validity of map input.
* @return - 0 if input is valid, -1 otherwise.
*/
int validateMap(int x, int y, vector <GridPoint*> obstacles, char comma) {
    if (x <= 0 || y <= 0) {
        return -1;
    }
    for (int i = 0; i < obstacles.size(); ++i) {
        int obsX = obstacles.at(i)->x;
        int obsY = obstacles.at(i)->y;
        if (obsX <= 0 || obsX >= x || obsY <= 0 || obsY >= y || comma != ',') {
            return -1;
        }
    }
    return 0;
}

/**
* Check validity of cab input.
* @return - 0 if input is valid, -1 otherwise.
*/
int validateCab(int id, int type, int car, int color, char comma[]) {
    if (id < 0 || type < 1 || type > 2 || car == -1 || color == -1) {
        return -1;
    }
    for (int i = 0; i < 7; ++i) {
        if (comma[i] != ',') {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    easyloggingpp::Configurations confFromFile("../Logging/Server_Config");
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile);
    LOG(INFO) << "Server starting";

    // input variables
    int gridX, gridY, numOfObstacles;
    int task;
    int obsX, obsY;
    char comma[] = {',',',',',',',',',',',',','};
    int input1, input2, input3, input4, input5, input6, input7;
    char input8, input9;
    double input10;
    vector <GridPoint*> obstacles;

    Server* server = new Server(atoi(argv[1]));

    while(true) {
        // construct the grid (our WORLD).
        cin >> gridX >> gridY >> numOfObstacles;
        if (numOfObstacles > 0) {
            for (int i = 0; i < numOfObstacles; ++i) {
                // Get input from user.
                cin >> obsX >> comma[0] >> obsY;
                obstacles.push_back(new GridPoint(obsX, obsY));
            }
        }
        if (validateMap(gridX, gridY, obstacles, comma[0]) == 0) {
            server->setUp(gridX, gridY, obstacles);
            break;
        } else {
            LOG(ERROR) << "Map input incorrect. please try again.";
            cout << "-1" << endl;
            obstacles.clear();
        }
    }

    // run tasks loop
    cin >> task;
    while (true) {

        switch (task) {

            case 1: //receive drivers from clients
            {
                cin >> input1;
                server->one(input1);
                break;
            }

            case 2: // insert new trip
            {
                cin >> input1 >> comma[0] >> input2 >> comma[1] >> input3 >> comma[2] >> input4
                    >> comma[3] >> input5 >> comma[4] >> input6 >> comma[5] >> input10 >> comma[6] >> input7;
                server->two(input1, input2, input3, input4, input5, input6, input10, input7);
                break;
            }

            case 3: // insert new vehicle
            {
                while (true) {
                    cin >> input1 >> comma[0] >> input2 >> comma[1] >> input8 >> comma[2] >> input9;
                    int car = findCar(input8);
                    int color = findColor(input9);
                    if (validateCab(input1, input2, car, color, comma) == 0) {
                        server->three(input1, input2, car, color);
                        break;
                    } else {
                        LOG(ERROR) << "Invalid cab input. Please try again";
                        cout << "-1" << endl;
                        memset(comma, ',', sizeof(comma));
                    }
                }
                break;
            }

            case 4: // request driver location bt id and print it.
            {
                cin >> input1;
                server->four(input1);
                break;
            }

            case 7: // clean up and exit
            {
                server->seven();
                LOG(INFO) << "Server exiting... Goodbye";
                return 0;
            }

            case 9: // send trips and move one step
            {
                server->nine();
                break;
            }


            default: {
                LOG(ERROR) << "Invalid task number. please try again.";
                cout << "-1" << endl;
                break;
            }
        }
        cin >> task;
    }
}