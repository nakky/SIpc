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
		SharedMemory(bool isMaster, const char *filepath, int projId, size_t size)
			: mIsMaster(isMaster),
			  mFilePath(filepath),
			  mProjectId(projId),
			  mSize(size),
			  mHead(NULL),
			  mSegmentId(0)
		{
		}

		virtual void initialize();
		virtual void terminate();

		bool write(int offset, size_t size, const void *buf);
		bool read(int offset, size_t size, void *buf);

		bool isAttached() { return mHead != NULL; }

		void *getHead() { return mHead; }

	protected:
		void *mHead;
		std::string mFilePath;
		int mProjectId;
		size_t mSize;

		key_t mKey;
		int mSegmentId;

		bool mIsMaster;
	};
};

#endif // SIPC_SHAREDMEMORY_H
