//
// Created by Roy Shefi on 22/01/2017.
//

#include "Job.h"

Job::Job(void *(*func)(void *arg), void *arg): func(func), arg(arg) {
    // TODO Auto-generated constructor stub

}

void Job::execute() {
    func(arg);
}

Job::~Job() {
    // TODO Auto-generated destructor stub
}