#pragma once
#include <chrono>

class CircleHit
{
public:

	std::chrono::high_resolution_clock::time_point time;
	bool katsu;

	CircleHit(std::chrono::high_resolution_clock::time_point time_, bool katsu_);
	virtual ~CircleHit();
};

