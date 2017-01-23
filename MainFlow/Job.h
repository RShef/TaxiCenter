//
// Created by Roy Shefi on 22/01/2017.
//

#ifndef PART_2_JOB_H
#define PART_2_JOB_H

class Job {
 private:
    void *arg;
    void * (*func)(void *arg);

 public:
    Job(void * (*func)(void *arg), void* arg);
    void execute();
    virtual ~Job();
};
#endif //PART_2_JOB_H
