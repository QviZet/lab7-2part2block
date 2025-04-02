#pragma once
#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>


extern std::condition_variable conMain;

void sortPart(std::string name, double* arr, int len);

void sortArr(std::string name, double* arr, double* frstPart, double* scndPart, int num);