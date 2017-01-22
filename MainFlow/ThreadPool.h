//
// Created by Roy Shefi on 22/01/2017.
//

#ifndef PART_2_THREADPOOL_H
#define PART_2_THREADPOOL_H


#include "Job.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
 private:
    queue<Job *> jobs_queue;
    int threads_num;
    pthread_t* threads;
    bool stop;
    pthread_mutex_t lock;
 public:
    ThreadPool(int threads_num);
    void doJobs();
    void addJob(Job *job);
    void terminate();
    bool isEmpty();
    virtual ~ThreadPool();
};

#endif //PART_2_THREADPOOL_H
