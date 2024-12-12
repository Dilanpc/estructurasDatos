#pragma once

#include <iostream>
#include <chrono>
#include "StaticArray.hpp"

static const size_t nValues[] = { 100, 316, 1'000, 3'162, 10'000, 31'623, 100'000, 316'228, 1'000'000 };

static void testPushFront(StaticArray<size_t>& lista)
{
	std::cout << "Push front test:\n";

	std::chrono::high_resolution_clock::time_point start, finish;

	for (const size_t n : nValues) {

		start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < n; ++i) {
			lista.pushFront(i);
		}
		finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = finish - start; // Time in milliseconds

		std::cout << n << " Tiempo: " << timeElapsed.count() << " ms\n";
		lista.empty();
	}
}

static void testPushBack(StaticArray<size_t>& lista)
{
	std::cout << "Push back test:\n";

	std::chrono::high_resolution_clock::time_point start, finish;

	for (const size_t n : nValues) {

		start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < n; ++i) {
			lista.pushBack(i);
		}
		finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = finish - start; // Time in milliseconds

		std::cout << n << " Tiempo: " << timeElapsed.count() << " ms\n";
		lista.empty();
	}
}

static void testPopFront(StaticArray<size_t>& lista)
{
	std::cout << "Pop front test:\n";

	std::chrono::high_resolution_clock::time_point start, finish;

	for (const size_t n : nValues) {

		// Llenar la lista
		for (size_t i = 0; i < n; ++i) {
			lista.pushFront(i);
		}

		start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < n; ++i) {
			lista.popFront();
		}
		finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = finish - start; // Time in milliseconds

		std::cout << n << " Tiempo: " << timeElapsed.count() << " ms\n";

	}
}

static void testPopBack(StaticArray<size_t>& lista)
{
	std::cout << "Pop back test:\n";

	std::chrono::high_resolution_clock::time_point start, finish;

	for (const size_t n : nValues) {

		// llenar lista
		for (size_t i = 0; i < n; ++i) {
			lista.pushFront(i);
		}

		start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < n; ++i) {
			lista.popBack();
		}
		finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = finish - start; // Time in milliseconds

		std::cout << n << " Tiempo: " << timeElapsed.count() << " ms\n";
		lista.empty();
	}
}

static void testFind(StaticArray<size_t>& lista)
{
	std::cout << "Find test:\n";

	std::chrono::high_resolution_clock::time_point start, finish;

	for (const size_t n : nValues) {

		// llenar lista
		for (size_t i = 0; i < n; ++i) {
			lista.pushFront(i);
		}

		start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < n; ++i) {
			lista.find(i / 10);
		}
		finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = finish - start; // Time in milliseconds

		std::cout << n << " Tiempo: " << timeElapsed.count() << " ms\n";
	}
}

template <typename T>
static void readData()
{
	int input;
	std::cin >> input;
	T lista(input); // size
	while (true) {
		std::cin >> input;
		if (std::cin.fail()) {
			break;
		}
		try {
			if (input == 1) {
				lista.print();
			}
			else if (input == 2) { // pushBack
				std::cin >> input; // get de value
				lista.pushBack(input);
			}
			else if (input == 3) { // popBack
				lista.popBack();
			}
			else if (input == 4) { // pushFront
				std::cin >> input;
				lista.pushFront(input);
			}
			else if (input == 5) { // popFront
				lista.popFront();
			}
			else if (input == 6) {
				std::cout << "Size: " << lista.size() << std::endl;
			}
			else if (input == 7) {
				std::cout << "Capacity: " << lista.capacity() << std::endl;
			}
			else if (input == 8) {
				lista.empty();
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}
