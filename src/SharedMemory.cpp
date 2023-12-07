#include "SIpc/SharedMemory.h"

#include <iostream>
#include <filesystem>

#include <string.h>

namespace SIpc
{
    void SharedMemory::initialize()
    {
        if (mIsMaster)
        {
            FILE *fp;
            fp = fopen(mFilePath.c_str(), "w");
            fclose(fp);

            if (!std::filesystem::exists(mFilePath.c_str()))
                return;

            mKey = ftok(mFilePath.c_str(), mProjectId);
            if (mKey == -1)
            {
                std::cerr << "Failed to acquire key" << std::endl;
                return;
            }

            // std::cout << "Key:" << mKey << std::endl;

            mSegmentId = shmget(mKey, mSize, 0644 | IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
            if (mSegmentId == -1)
            {
                std::cerr << "Failed to acquire segment" << std::endl;
                return;
            }
            mHead = shmat(mSegmentId, 0, 0);
        }
        else
        {
            mKey = ftok(mFilePath.c_str(), mProjectId);
            if (mKey == -1)
            {
                std::cerr << "Failed to acquire key" << std::endl;
                return;
            }

            // std::cout << "Key:" << mKey << std::endl;

            mSegmentId = shmget(mKey, 0, 0);
            if (mSegmentId == -1)
            {
                std::cerr << "Failed to acquire segment" << std::endl;
                return;
            }
            mHead = shmat(mSegmentId, 0, 0);
        }
    }

    void SharedMemory::terminate()
    {
        if (mIsMaster)
        {
            shmdt(mHead);
            mHead = NULL;
            shmctl(mSegmentId, IPC_RMID, NULL);
        }
        else
        {
            shmdt(mHead);
            mHead = NULL;
        }
    }

    bool SharedMemory::write(int offset, size_t size, const void *buf)
    {
        if (!isAttached())
            return false;
        memcpy((char *)mHead + offset, buf, size);
        return true;
    }

    bool SharedMemory::read(int offset, size_t size, void *buf)
    {
        if (!isAttached())
            return false;
        memcpy(buf, (char *)mHead + offset, size);
        return true;
    }

}; // namespace SIpc