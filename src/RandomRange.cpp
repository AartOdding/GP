#include "RandomRange.h"

#include <chrono>

#include <ofRectangle.h>


std::mt19937 RandomRange::generator{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };


int RandomRange::uniform(int min, int max) {
	return std::uniform_int_distribution<int>{min, max}(generator);
}


float RandomRange::uniform(float min, float max) {
	return std::uniform_real_distribution<float>{min, max}(generator);
}


float::RandomRange::normal(float mean, float std_dev) {
	return std::normal_distribution<float>{mean, std_dev}(generator);
}


std::pair<int, int> RandomRange::normal_point(const ofRectangle& rectangle) {
	while (true) {
		int x = rectangle.x + RandomRange::normal(rectangle.width / 2, rectangle.width / 4);
		int y = rectangle.y + RandomRange::normal(rectangle.height / 2, rectangle.height / 4);
		if (rectangle.inside(x, y)) return{ x, y };
	}
}
