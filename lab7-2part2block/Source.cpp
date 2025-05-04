#include "header.h"

std::mutex mutMain;

int main(int argc, const char* argv[]) {
	const int len = 100;
	double* arr;
	arr = new double[len];
	std::string name;

	for (int i = 0; i < len; i++)
	{
		arr[i] = (rand() % 10000) / 10.;
	}

	double* frstPart;
	frstPart = new double[len / 2];
	double* scndPart;
	scndPart = new double[len / 2];

	for (int i = 0; i < len / 2; i++)
	{
		frstPart[i] = arr[i];
		scndPart[i] = arr[i + (len / 2)];
	}

	std::future <void> thread1(std::async(sortPart, "thread1", frstPart, len / 2));
	std::future <void> thread2(std::async(sortPart, "thread2", scndPart, len / 2));

	std::future <std::string> thread3(std::async(sortArr, "thread3", arr, frstPart, scndPart, len));
	name = thread3.get();

	std::cout << "\n" << name <<  "\tcompleted\n\nSorting completed\n";

	delete[] arr;
	delete[] frstPart;
	delete[] scndPart;
	return 0;
}