#include "LoopedThread.h"

namespace uc
{

	LoopedThread::~LoopedThread()
	{
		stop();
	}

	void LoopedThread::request_stop()
	{
		running = false;
	}

	void LoopedThread::stop()
	{
		running = false;
		wait_until_finished();
	}


	void LoopedThread::wait_until_finished()
	{
		if (_thread.joinable()) _thread.join();
	}

}