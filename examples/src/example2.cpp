

#include "SIpc/SIpc.h"

#include <errno.h>

using namespace SIpc;

int main(void)
{
    SharedMemory *slave = new SharedMemory("./test", 100);
    slave->initialize();

    printf("%s\n", slave->getDataHead());
    printf("size:%d\n", slave->getSize());
    printf("errno=%d: %s\n", errno, strerror(errno));

    slave->terminate();
    SAFE_DELETE(slave);

    return 0;
}
