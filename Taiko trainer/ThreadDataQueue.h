#pragma once
#include <memory>
#include <mutex>
#include <queue>

namespace uc
{

	// use this queue to safely send data between threads
	template <class _Type> class ThreadDataQueue
	{

		std::queue<_Type> _queue;
		std::mutex _queue_mutex;

	public:

		unsigned max_size;


		ThreadDataQueue(unsigned max_size_) : max_size(max_size_) {}
		virtual ~ThreadDataQueue() {}


		void clear()
		{

			std::queue<_Type> empty;
			std::lock_guard<std::mutex> lock(_queue_mutex);

			_queue = empty;

		}

		// returns false if queue is full
		bool try_push(const _Type & value)
		{

			if (_queue.size() >= max_size) return false;

			std::lock_guard<std::mutex> lock(_queue_mutex);
			_queue.push(value);

			return true;
		}

		// returns false if queue is empty
		bool try_pop()
		{
			std::lock_guard<std::mutex> lock(_queue_mutex);

			if (_queue.size())
			{
				_queue.pop();
				return true;
			}
			else return false;
		}

		// returns false if queue is empty and leaves output_value unchanged
		bool try_pop(_Type & output_value)
		{
			std::lock_guard<std::mutex> lock(_queue_mutex);

			if (_queue.size())
			{
				output_value = _queue.front();
				_queue.pop();
				return true;
			}
			else return false;
		}

		// returns pointer to next element or empty pointer if queue is empty
		std::shared_ptr<_Type> try_pop_ptr()
		{
			std::lock_guard<std::mutex> lock(_queue_mutex);

			if (_queue.size())
			{
				std::shared_ptr<_Type> ret = std::make_shared<_Type>(_queue.front());
				_queue.pop();
				return ret;
			}
			else return std::shared_ptr<_Type>();
		}

		// access first element
		_Type & front()
		{
			std::lock_guard<std::mutex> lock(_queue_mutex);

			return _queue.front();
		}


		bool empty() const
		{
			return _queue.empty();
		}


		unsigned size() const
		{
			return _queue.size();
		}


		bool full() const
		{
			return size() >= max_size;
		}
	};

}