#pragma once
#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>

void sortPart(std::string name, double* arr, int len);

std::string sortArr(std::string name, double* arr, double* frstPart, double* scndPart, int num);