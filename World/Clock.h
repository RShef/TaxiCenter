//
// Created by othaller on 29/12/16.
//

#ifndef PART_2_CLOCK_H
#define PART_2_CLOCK_H


class Clock {

private:
    int time;

public:
    /**
    * instantiates a clock.
    * sets time to 0.
    */
    Clock();

    /**
    * Returns the current time.
    */
    int getTime();

    /**
    * advances time by 1.
    */
    void advance();
};

#endif //PART_2_CLOCK_H
