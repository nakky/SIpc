

#include "SIpc/SIpc.h"

#include <errno.h>

using namespace SIpc;

int main(void)
{
    SharedMemory *slave = new SharedMemory(false, "./test", 100, 10);
    slave->initialize();

    printf("%s\n", slave->getHead());
    printf("errno=%d: %s\n", errno, strerror(errno));

    slave->terminate();
    SAFE_DELETE(slave);

    return 0;
}
