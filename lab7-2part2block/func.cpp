#include "header.h"

std::mutex mut, mut3;
std::condition_variable con3;
bool flag = false;
std::atomic<int> intCon;

void sortPart(std::string name, double* arr, int len) {
	double min = 1001;
	int minNum = 0;
	auto beginSort = std::chrono::steady_clock::now();
	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++) {
			if (arr[j] < min) {
				min = arr[j];
				minNum = j;
			}
		}
		min = arr[i];
		arr[i] = arr[minNum];
		arr[minNum] = min;
		min = 1001;
	}
	for (int i = 0; i < len; i++)
	{
		{
			std::lock_guard <std::mutex> lock(mut);
			std::cout << name << "\t";
			std::cout << arr[i] << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	{
		std::lock_guard <std::mutex> lock(mut3);
		std::cout << "\n" << name << "\tcompleted...\n\n";
	}

	intCon.fetch_add(1);
	con3.notify_one();
}

std::string sortArr(std::string name, double* arr, double* frstPart, double* scndPart, int len) {
	std::unique_lock<std::mutex> lock(mut3);
	while (intCon!=2) con3.wait(lock);

	int frst = 0, scnd = 0, k = 0;
	while ((frst != len / 2) && (scnd != len / 2)) {
		if (frstPart[frst] < scndPart[scnd]) {
			arr[k] = frstPart[frst];
			k++;
			frst++;
		}
		else {
			arr[k] = scndPart[scnd];
			k++;
			scnd++;
		}
	}
	while (frst != len / 2) {
		arr[k] = frstPart[frst];
		k++;
		frst++;
	}
	while (scnd != len / 2) {
		arr[k] = scndPart[scnd];
		k++;
		scnd++;
	}
	for (int i = 0; i < len; i++)
	{
		std::cout << name << "\t";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::cout << arr[i] << std::endl;
	}

	return name;
}