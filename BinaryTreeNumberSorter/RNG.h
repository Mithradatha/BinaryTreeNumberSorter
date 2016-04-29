#ifndef RNG_H
#define RNG_H

#include <random>
#include <chrono>
#include <ctime>

using namespace std;

/*
* RNG is a helper class to generate random integers between a given range
*/

class RNG {

	public:

	// generator = system time (for pseudorandom seed), distribution = [min, max]
	RNG(int min, int max) : generator((unsigned int)chrono::system_clock::now().time_since_epoch().count()), distribution(min, max) {}

	// return a randomly generated integer between the give distribution range
	int nextInt() { return distribution(generator); }
	
	private:

	default_random_engine generator;
	uniform_int_distribution<int> distribution;
};

#endif