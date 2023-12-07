

#include "SIpc/SIpc.h"

#include <unistd.h>

#include <errno.h>

using namespace SIpc;

int main(void)
{
    SharedMemory *master = new SharedMemory(true, "./test", 100, 10);
    master->initialize();

    master->write(0, 7, "Hello!\0");
    printf("errno=%d: %s\n", errno, strerror(errno));

    unsigned long time = 0;
    const unsigned long delta = 1000 * 100;

    while (true)
    {
        usleep(delta);
        time += delta;
        if (time > 1000L * 1000L * 5L)
            break;
    }

    master->terminate();
    SAFE_DELETE(master);

    return 0;
}
