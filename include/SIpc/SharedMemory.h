#ifndef SIPC_SHAREDMEMORY_H
#define SIPC_SHAREDMEMORY_H

#include "Common.h"

#include <sys/shm.h>
#include <sys/stat.h>
#include <string>

namespace SIpc
{
	class SharedMemory
	{
	public:
		SharedMemory(const char *filepath, int projId, size_t size)
			: mIsMaster(true),
			  mFilePath(filepath),
			  mProjectId(projId),
			  mSize(size),
			  mHead(NULL),
			  mSegmentId(0)
		{
		}

		SharedMemory(const char *filepath, int projId)
			: mIsMaster(false),
			  mFilePath(filepath),
			  mProjectId(projId),
			  mSize(0),
			  mHead(NULL),
			  mSegmentId(0)
		{
		}

		virtual void initialize();
		virtual void terminate();

		bool write(int offset, size_t size, const void *buf);
		bool read(int offset, size_t size, void *buf);

		bool isAttached() { return mHead != NULL; }

		void *getDataHead() { return mDataHead; }

		size_t getSize() { return mSize; }

	protected:
		void *mHead;
		void *mDataHead;
		std::string mFilePath;
		int mProjectId;
		size_t mSize;

		key_t mKey;
		int mSegmentId;

		bool mIsMaster;
	};
};

#endif // SIPC_SHAREDMEMORY_H
