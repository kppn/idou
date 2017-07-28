#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>

using namespace std;

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);
const int iterations = 20;
const int producer_thread_count = 4;
const int consumer_thread_count = 4;
boost::lockfree::queue<int> queue(128);


void producer(void)
{
	for (int i = 0; i != iterations; ++i) {
		int value = ++producer_count;
		while (1) {
			bool push_success;

			push_success = queue.push(value);
			if (push_success) {
				std::cout << "PRODUCER queued succeed " << boost::this_thread::get_id() << std::endl;
				std::cout << std::flush;
				break;
			}
			else {
				std::cout << "PRODUCER queue failed " << boost::this_thread::get_id() << std::endl;
				std::cout << std::flush;
			}
			
		}
	}
}


boost::atomic<bool> done (false);

void consumer(void)
{
	int value;
	while (!done) {
		std::cout << "CONSUMER: wait" << std::endl;
		while (queue.pop(value)) {
			std::cout << "CONSUMER: queue poped " << boost::this_thread::get_id() << std::endl;
			std::cout << std::flush;
			++consumer_count;
		}
	}

	while (queue.pop(value))
		++consumer_count;
}




int main(int argc, char* argv[])
{
	cout << "boost::lockfree::queue is ";

	if (!queue.is_lock_free())
		cout << "not ";
	cout << "lockfree" << endl;

	boost::thread_group producer_threads;
	boost::thread_group consumer_threads;

	for (int i = 0; i != producer_thread_count; ++i)
		producer_threads.create_thread(producer);

	for (int i = 0; i != consumer_thread_count; ++i)
		consumer_threads.create_thread(consumer);

	producer_threads.join_all();
	done = true;

	consumer_threads.join_all();

	cout << "produced " << producer_count << " objects." << endl;
	cout << "consumed " << consumer_count << " objects." << endl;

	return 0;
}

