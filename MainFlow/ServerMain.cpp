//
// Created by Oded Thaller on 11/12/2016.
//

#define _ELPP_THREAD_SAFE

#include <iostream>
#include "TaxiWorld.h"
#include "../Logging/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

/**
* parses input string by a delimiter into a vector
* @return - a vector of the input values
*/
vector<int> parse(string str, char delim, int cab) {
    vector<string> temp;
    vector<int> vec;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delim)) {
        temp.push_back(tok);
    }

    for (int i = 0; i < temp.size(); i++) {
        if (cab && (i == 2 || i == 3)) {
            vec.push_back((int &&) (temp.at(i).c_str())[0]);
        } else {
            vec.push_back(atoi(temp.at(i).c_str()));
        }
    }

    return vec;
}

/**
* Find the type of car by Char given.
* @param carInput - Char input.
* @return - the int value that the char represents.
*/
int findCar(char carInput) {
    if (carInput == 72) {
        return 0;
    } else if (carInput == 83) {
        return 1;
    } else if (carInput == 84) {
        return 2;
    } else if (carInput == 70) {
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
    if (colorInput == 82) {
        return 0;
    } else if (colorInput == 66) {
        return 1;
    } else if (colorInput == 71) {
        return 2;
    } else if (colorInput == 80) {
        return 3;
    } else if (colorInput == 87) {
        return 4;
    } else {
        return -1;
    }
}

/**
* Check validity of map input.
* @return - 0 if input is valid, -1 otherwise.
*/
int validateObstacles(int x, int y, vector <GridPoint*> obstacles) {
    for (int i = 0; i < obstacles.size(); ++i) {
        int obsX = obstacles.at(i)->x;
        int obsY = obstacles.at(i)->y;
        if (obsX < 0 || obsX >= x || obsY < 0 || obsY >= y) {
            return -1;
        }
    }
    return 0;
}

/**
* Check validity of cab input.
* @return - 0 if input is valid, -1 otherwise.
*/
int validateCab(vector<int> vec) {
    if (vec.size() != 4 || vec.at(0) < 0 || vec.at(1) < 1 || vec.at(1) > 2 || vec.at(2) == -1 || vec.at(3) == -1) {
        return -1;
    }
    return 0;
}

/**
* Check validity of trip input.
* @return - 0 if input is valid, -1 otherwise.
*/
int validateTrip(vector<int> vec, int mapX, int mapY, vector<GridPoint*> obs) {
    if (vec.size() != 8 || vec.at(0) < 0 || vec.at(1) < 0 || vec.at(1) > mapX || vec.at(2) < 0 || vec.at(2) > mapY
        || vec.at(3) < 0 || vec.at(3) > mapX || vec.at(4) < 0 || vec.at(4) > mapY || vec.at(5) < 1 || vec.at(6) <= 0
        || vec.at(7) <= 0) {
        return -1;
    }
    for (int i = 0; i < obs.size(); ++i) {
        if ((vec.at(1) == obs.at(i)->x && vec.at(2) == obs.at(i)->y)
            || (vec.at(3) == obs.at(i)->x && vec.at(4) == obs.at(i)->y)) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    easyloggingpp::Configurations confFromFile("Logging/Server_Config");
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile);
    LOG(INFO) << "Server starting";

    // input variables
    int gridX, gridY;
    //int numOfObstacles;
    int numOfObstacles;
    int task;
    char comma = 0;
    int input1;
    string input;
    vector<int> vec;
    vector<GridPoint *> obstacles;

    Server *server = new Server(atoi(argv[1]));
    TaxiWorld* taxiWorld = new TaxiWorld(server);

    while (true) {
        // construct the grid (our WORLD).
        getline(cin, input);
        vec = parse(input, ' ', 0);
        if (vec.at(0) <= 0 || vec.at(1) <= 0) {
            LOG(ERROR) << "Map input incorrect. please try again.";
            cout << "-1" << endl;
            vec.clear();
            continue;
        }
        gridX = vec.at(0);
        gridY = vec.at(1);
        vec.clear();
        getline(cin, input);
        stringstream ns(input);
        if (ns >> numOfObstacles) {
            if (numOfObstacles > 0) {
                for (int i = 0; i < numOfObstacles; ++i) {
                    getline(cin, input);
                    vec = parse(input, ',', 0);
                    obstacles.push_back(new GridPoint(vec.at(0), vec.at(1)));
                    vec.clear();
                }
            }
        } else {
            LOG(ERROR) << "number od obstacles incorrect. please try again.";
            cout << "-1" << endl;
            continue;
        }
        if (validateObstacles(gridX, gridY, obstacles) == 0) {
            taxiWorld->setUp(gridX, gridY, obstacles);
            vec.clear();
            break;
        } else {
            LOG(ERROR) << "obstacles input incorrect. please try again.";
            cout << "-1" << endl;
            obstacles.clear();
            vec.clear();
        }
    }

    // run tasks loop
    cin >> task;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        // for the bfs check of the route.
        if (!taxiWorld->trips.empty()) {
            for (int i = 0; i < taxiWorld->trips.size(); i++) {
                if (taxiWorld->trips[i]->wrong) {
                    taxiWorld->trips.erase(taxiWorld->trips.begin() + i);
                }
            }
        }
        switch (task) {

            case 1: //receive drivers from clients
            {
                cin >> input1;
                taxiWorld->getDriversFromClients(input1);
                break;
            }

            case 2: // insert new trip
            {
                // get input line, delimited by ',' and parse into vector
                getline(cin, input);
                vec = parse(input, ',', 0);
                if (validateTrip(vec, taxiWorld->getMap()->getX(), taxiWorld->getMap()->getY(), obstacles) == 0) {
                    taxiWorld->addTrip(vec.at(0), vec.at(1), vec.at(2), vec.at(3), vec.at(4), vec.at(5), vec.at(6), vec.at(7));
                } else {
                    LOG(ERROR) << "Invalid trip input. Please try again";
                    cout << "-1" << endl;
                }
                vec.clear();
                break;
            }

            case 3: // insert new vehicle
            {
                getline(cin, input);
                vec = parse(input, ',', 1);
                int car = findCar((char) vec.at(2));
                int color = findColor((char) vec.at(3));
                if (validateCab(vec) == 0) {
                    taxiWorld->addCab(vec.at(0), vec.at(1), car, color);
                } else {
                    LOG(ERROR) << "Invalid cab input. Please try again";
                    cout << "-1" << endl;
                }
                vec.clear();
                break;
            }

            case 4: // request driver location by id and print it.
            {
                cin >> input1;
                taxiWorld->printDriver(input1);
                break;
            }

            case 7: // clean up and exit
            {
                taxiWorld->close();
                LOG(INFO) << "Server exiting... Goodbye";
                return 0;
            }

            case 9: // send trips and move one step
            {
                taxiWorld->moveOnce();
                break;
            }

            default: {
                LOG(ERROR) << "Invalid task number. please try again.";
                cout << "-1" << endl;
                break;
            }
        }
        cin >> task;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
