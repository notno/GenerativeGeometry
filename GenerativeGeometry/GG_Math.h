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

		template<typename T>
		static double Distance(const T& p1, const T& p2) {
			double aSquared = pow(p2.X - p1.X, 2.0);
			double bSquared = pow(p2.Y - p1.Y, 2.0);
			double cSquared = pow(p2.Z - p1.Z, 2.0);
			return sqrt(aSquared + bSquared + cSquared);
		}
	};

} // GenerativeGeometry namespace