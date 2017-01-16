//
// Created by Oded Thaller on 11/12/2016.
//

#include <iostream>

#include "Server.h"
using namespace std;





int main(int argc, char *argv[]) {
    // input variables
    int gridX, gridY, numOfObstacles;
    int task;
    Server* server = new Server(atoi(argv[1]));
    // construct the grid (our WORLD).
    cin >> gridX >> gridY >> numOfObstacles;
    server->setMap(gridX,gridY,numOfObstacles);
    // run tasks loop
    cin >> task;
    while (task != 0) {

        switch (task) {

            case 1: //receive drivers from clients
            {
                server->one();
                break;

            }

            case 2: // insert new trip
            {
                server->two();
                break;

            }

            case 3: // insert new vehicle
            {
               server->three();
                break;
            }

            case 4: // request driver location bt id and print it.
            {
               server->four();
                break;
            }

            case 9: // send trips and move one step
            {
                server->nine();
                break;

            }

            case 7: // clean up and exit
            {
                server->seven();
                break;

            }
            default: {
                break;
            }
        }

        cin >> task;
    }
}