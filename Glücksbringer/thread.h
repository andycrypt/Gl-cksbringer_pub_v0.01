#pragma once
#include <thread>
#include <vector>
class thread_g {
	std::vector<std::jthread> _v;
public:
	//void add(std::jthread t) { _v.emplace_back(t); }
	void exit() {
		for (auto& x : _v) {
			x.join();
		}
	}
};

