#include "Solution.h"
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::binary_semaphore l2r{ 1 };//left to right
std::binary_semaphore r2l{ 1 };//right to left

int place = 0;
int l2r_in = 0;

static void Left2Right(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		l2r.acquire();
		l2r_in++;
		if (l2r_in == 1)
		{
			r2l.acquire();
		}
		l2r.release();
		std::cout << "left to right in." << std::endl;
		l2r.acquire();
		l2r_in--;
		if (l2r_in == 0)
		{
			r2l.release();
		}
		l2r.release();
	}
}

static void Right2Left(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		r2l.acquire();
		std::cout << "right to left in." << std::endl;
		r2l.release();
	}
}

int main()
{
	std::thread right2left(Right2Left,20);
	std::thread left2right(Left2Right,20);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	left2right.join();
	right2left.join();
}
