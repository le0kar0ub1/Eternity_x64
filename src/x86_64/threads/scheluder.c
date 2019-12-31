#include "scheluder.h"
#include "processus.h"

struct threadDescriptor *threadRunning = NULL;
struct threadDescriptor *threadPrev = NULL;

list_t *threadList;

struct context *savedContext;

void createFirstThread(void)
{
    
}

void threadScheluder(void)
{
    if (!list_size(threadList))
        return;
    if (!threadRunning) {
        createFirstThread();
        return;
    }
}