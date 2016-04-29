#ifndef RNG_H
#define RNG_H

#include <random>
#include <chrono>
#include <ctime>

using namespace std;

class RNG {

	public:

	RNG(int min, int max) : generator((unsigned int)chrono::system_clock::now().time_since_epoch().count()), distribution(min, max) {}

	int nextInt() { return distribution(generator); }
	
	private:

	default_random_engine generator;
	uniform_int_distribution<int> distribution;
};

#endif