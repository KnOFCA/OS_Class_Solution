#include "Solution.h"
#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <random>
#include <exception>
#include <format>
#include <chrono>

std::binary_semaphore empty{ 1 };
std::binary_semaphore fs{ 0 };//son
std::binary_semaphore fd{ 0 };//daughter
std::mutex mute;

int p = 0;
int cnt = 0;
int cnt_s = 0;
int cnt_d = 0;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 2);

static void Father()
{
	while (1)
	{
		empty.acquire();
		mute.lock();
		if (cnt == 100)
		{
			fs.release();
			fd.release();
			mute.unlock();
			cnt++;
			break;
		}
		else cnt++;
		if (p != 0) {
			std::cout << "ERROR: Plate is not empty." <<std::endl;
			throw std::exception("UNEXCEPT_NOT_EMPTY");
		}
		p = distrib(gen) - 1 ? orange : apple;
		std::cout << std::format("Father puts {}.", p == orange ? "orange" : "apple") << std::endl;
		if (p == orange) fs.release();
		else fd.release();
		mute.unlock();

	}
}

static void Son()
{
	while (1)
	{
		fs.acquire();
		mute.lock();
		if (cnt == 101)
		{
			mute.unlock();
			break;
		}
		if (p == 0)
		{
			std::cout << "ERROR: Son gets nothing." << std::endl;
			throw std::exception("UNEXCEPT_EMPTY");
		}
		p = 0;
		std::cout << "Son gets orange." << std::endl;
		cnt_s++;
		empty.release();
		mute.unlock();
		//eating
	}
}

static void Daughter()
{
	while (1)
	{
		fd.acquire();
		mute.lock();
		if (cnt == 101)
		{
			mute.unlock();
			break;
		}
		if (p == 0)
		{
			std::cout << "ERROR: Daughter gets nothing." << std::endl;
			throw std::exception("UNEXCEPT_EMPTY");
		}
		p = 0;
		std::cout << "Daughter gets apple." << std::endl;
		cnt_d++;
		empty.release();
		mute.unlock();
		//eating
	}
}

int main()
{
	std::set_terminate([]()
		{
			try
			{
				std::exception_ptr eptr{ std::current_exception() };
				if (eptr)
				{
					std::rethrow_exception(eptr);
				}
				else
				{
					std::cerr << "no exception\n";
				}
			}
			catch (const std::exception& ex)
			{
				std::cerr << "exception:" << ex.what() << '\n';
			}
			catch (...)
			{
				std::cerr << "unknown exception\n";
			}
			std::exit(EXIT_FAILURE);
		});

	std::thread father(Father);
	std::thread son(Son);
	std::thread daughter(Daughter);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	father.join();
	son.join();
	daughter.join();

	std::cout << std::format("Father puts {}, son gets {}, daughter gets {}.", cnt - 1, cnt_s, cnt_d);
}
