#pragma once
#include "TimeDependent.h"

class TaikoCircle
{
public:

	float speed;
	const bool katsu;
	const bool big;
	const std::chrono::high_resolution_clock::time_point hit_time;

	TaikoCircle(std::chrono::high_resolution_clock::time_point hit_time_, float speed_, bool katsu_, bool big_);
	~TaikoCircle();

	void draw() const;

	float x() const;
};

