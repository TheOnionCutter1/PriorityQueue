#include <iostream>
#include <mutex>
#include "PriorityQueue.h"

enum class Option
{
	ADD=1,
	REMOVE,
	DEMONSTRATE,
	EXIT
};

std::mutex queueLock;
std::condition_variable qCondition;

/*
Print the queue, show the menu and take the user's choice.
Output: the user's choice.
*/
Option showMenu(const PriorityQueue<int>& q)
{
	int buf = 0;
	
	std::cout << "\nWelcome!\n";
	std::cout << "Your queue:\n";
	q.print();
	std::cout << '\n';
	std::cout << "1. Push a number\n";
	std::cout << "2. Pop the first number\n";
	std::cout << "3. Show a demonstration of the queue using threads\n";
	std::cout << "4. Exit\n";
	std::cout << "Your choice: ";
	std::cin >> buf;
	std::cin.ignore();
	return Option(buf);
}

/* ask the user for a number and add it to the queue */
void addNumber(PriorityQueue<int>& q)
{
	int num = 0;

	std::cout << "Enter a number: ";
	std::cin >> num;
	std::cin.ignore();
	q.push(num);
}

void pushToQueue(PriorityQueue<int>& q)
{
	const int MAX = 50;
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::lock_guard<std::mutex> lck(queueLock);
			num = rand() % (MAX + 1);
			q.push(num);
			std::cout << "Pushed " << num << " to the queue\n";
			qCondition.notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

void popFromQueue(PriorityQueue<int>& q)
{
	for (int i = 0; i < 20; i++)
	{
		std::unique_lock<std::mutex> lck(queueLock);
		if (q.empty())
		{
			qCondition.wait(lck);
		}
		std::cout << "Popping " << q.top() << " From the queue\n";
		q.pop();
	}
}

/*
Create 2 threads to demonstrate the usage of the queue, one for pushing to the queue
and one for popping from the queue.
Input: the queue.
*/
void demonstrateUsingThread(PriorityQueue<int>& q)
{
	std::thread pusher(pushToQueue, std::ref(q));
	std::thread popper(popFromQueue, std::ref(q));

	std::this_thread::sleep_for(std::chrono::seconds(5));
	pusher.join();
	popper.join();
}

/*
Handle the user's choice.
Input choice: the user's choice.
*/
void handleChoice(PriorityQueue<int>& q, Option choice)
{
	switch (choice)
	{
	case Option::ADD:
		addNumber(q);
		break;
	case Option::REMOVE:
		q.pop();
		break;
	case Option::DEMONSTRATE:
		demonstrateUsingThread(q);
		break;
	case Option::EXIT:
		std::cout << "Bye\n";
		break;
	default:
		std::cout << "Invalid choice...\n";
		break;
	}
}

int main()
{
	PriorityQueue<int> queue;
	Option choice{};

	srand(time(NULL));
	do
	{
		choice = showMenu(queue);
		handleChoice(queue, choice);
	} while (choice != Option::EXIT);
	return 0;
}
