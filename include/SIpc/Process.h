#ifndef SIPC_PROCESS_H
#define SIPC_PROCESS_H

#include "Common.h"

#include <sys/shm.h>
#include <sys/stat.h>
#include <string>

namespace SIpc
{
    class Process
    {
    public:
    public:
        Process()
        {
        }

        virtual ~Process() {}

        virtual void initialize();
        virtual void terminate();

        virtual bool execute(const char *path, char *const *args);
    };
};

#endif // SIPC_PROCESS_H
