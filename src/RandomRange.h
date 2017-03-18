#pragma once

#include <random>
#include <utility>



class ofRectangle;

class RandomRange { 

public:

	RandomRange() {}

	static int uniform(int, int);
	static float uniform(float, float);
	static float normal(float, float);

	static std::pair<int, int> normal_point(const ofRectangle&);

private:

	static std::mt19937 generator;
	
};