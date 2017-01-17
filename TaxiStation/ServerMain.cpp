//
// Created by Oded Thaller on 11/12/2016.
//

#include <iostream>
#include "Server.h"

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
    } else {
        return 3;
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
    } else {
        return 4;
    }
}

int main(int argc, char *argv[]) {
    // input variables
    int gridX, gridY, numOfObstacles;
    int task;
    int obsX, obsY;
    char comma[7];
    int input1, input2, input3, input4, input5, input6, input7;
    char input8, input9;
    double input10;
    vector <GridPoint*> obstacles;

    Server* server = new Server(atoi(argv[1]));
    
    // construct the grid (our WORLD).
    cin >> gridX >> gridY >> numOfObstacles;
    if (numOfObstacles > 0) {
        for (int i = 0; i < numOfObstacles; ++i) {
            // Get input from user.
            cin >> obsX >> comma[0] >> obsY;
            obstacles.push_back(new GridPoint(obsX, obsY));
        }
    }
    server->setUp(gridX, gridY, obstacles);
    
    // run tasks loop
    cin >> task;
    while (task != 0) {

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
                cin >> input1 >> comma[0] >> input2 >> comma[1] >> input8 >> comma[2] >> input9;
                int car = findCar(input8);
                int color = findColor(input9);
                server->three(input1, input2, car, color);
                break;
            }

            case 4: // request driver location bt id and print it.
            {
                cin >> input1;
                server->four(input1);
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