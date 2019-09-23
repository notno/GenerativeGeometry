#pragma once
#include <random>

namespace GenerativeGeometry {

	class Math {

	public:
		static int RandRangeInt(int a, int b)
		{
			// Obtain a random number from hardware
			std::random_device rd;
			// A Mersenne Twister pseudo-random generator of 32 bit #s
			std::mt19937 generator(rd());
			// Inclusive range between a and b
			std::uniform_int_distribution<> distr(a, b);
			return distr(generator);
		};

		static double RandRangeReal(double a, double b)
		{
			// Obtain a random number from hardware
			std::random_device rd;
			// A Mersenne Twister pseudo-random generator of 32 bit #s
			std::mt19937 generator(rd());
			// Inclusive range between a and b
			std::uniform_real_distribution<double> distr(a, b);
			return distr(generator);
		};

		static double RandNormalized() {
			return RandRangeReal(0, 1);
		}
	};

} // GenerativeGeometry namespace