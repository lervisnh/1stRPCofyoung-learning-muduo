#ifndef BASE_ASYNC_LOGGING_H
#define BASE_ASYNC_LOGGING_H

#include <mutex>
#include <string>
#include <vector>
#include <memory>

#include "Thread.h"
#include "LogStream.h"
// #include "ptr_vector.h"
#include "Condition.h"

class AsyncLogging
{
public:
	AsyncLogging(const std::string filePath, off_t rollSize, double flushInterval = 3.0);
	~AsyncLogging();

	void start(){
		m_isRunning = true;
		m_thread.start();
	}

	void stop(){
		m_isRunning = false;
		m_cond.notify();
		m_thread.join();
	}

	void append(const char *logline, int len);

private:
	AsyncLogging(const AsyncLogging&);
	AsyncLogging& operator=(const AsyncLogging&);

	void threadRoutine();

	typedef LogBuffer<kLargeBuffer> Buffer;
	// typedef myself::ptr_vector<Buffer> BufferVector;
	typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
	typedef std::unique_ptr<Buffer> BufferPtr;

	const double m_flushInterval;
	bool m_isRunning;
	off_t m_rollSize;
	std::string m_filePath;
	Thread m_thread;
	std::mutex m_mutex;
	Condition m_cond;

	BufferPtr m_currentBuffer;
	BufferPtr m_nextBuffer;
	BufferVector m_buffers;
};

#endif
