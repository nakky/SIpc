
#include "SIpc/Process.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace SIpc
{
    void Process::initialize()
    {
    }

    void Process::terminate()
    {
    }

    bool Process::execute(const char *path, char *const *args)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            return false;
        }
        else if (pid == 0)
        {
            pid = fork();
            if (pid < 0)
            {
                exit(1);
            }
            else if (pid == 0)
            {
                execvp(path, args);
                exit(1);
            }
            exit(1);
        }

        if (waitpid(pid, NULL, 0) < 0)
        {
            return false;
        }

        return true;
    }

}; // namespace SIpc