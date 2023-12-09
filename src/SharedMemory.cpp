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

            size_t size = mSize + sizeof(int);

            mSegmentId = shmget(mKey, size, 0644 | IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
            if (mSegmentId == -1)
            {
                std::cerr << "Failed to acquire segment" << std::endl;
                return;
            }
            mHead = shmat(mSegmentId, 0, 0);
            mDataHead = (char *)mHead + sizeof(int);
            memcpy(mHead, &mSize, sizeof(int));
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
            mDataHead = (char *)mHead + sizeof(int);
            memcpy(&mSize, mHead, sizeof(int));
        }
    }

    void SharedMemory::terminate()
    {
        if (mIsMaster)
        {
            if (isAttached())
            {
                shmdt(mHead);
                shmctl(mSegmentId, IPC_RMID, NULL);
            }
        }
        else
        {
            if (isAttached())
                shmdt(mHead);
        }
        mHead = NULL;
        mDataHead = NULL;

        std::filesystem::remove(mFilePath.c_str());
    }

    bool SharedMemory::write(int offset, size_t size, const void *buf)
    {
        if (!isAttached())
            return false;
        memcpy((char *)mDataHead + offset, buf, size);
        return true;
    }

    bool SharedMemory::read(int offset, size_t size, void *buf)
    {
        if (!isAttached())
            return false;
        memcpy(buf, (char *)mDataHead + offset, size);
        return true;
    }

}; // namespace SIpc