#ifndef CUSTOMRANDOM
#define CUSTOMRANDOM
#include <random>
#include <cmath>

template <typename T>

class customRandom {
	private:
	long long seed;
	long long* garbage;
	long long* garbageCadangan;
	unsigned int counter;
	static constexpr unsigned int bitwise = static_cast<unsigned int>((sizeof(T) * 8)/1.5);
#ifdef STABLEDISTRIBUTION
	T bias = 0;
#endif
	T maxT = pow(2, sizeof(T) * 8) - 1;
	T lastNumber;
	std::random_device rd;

	public:
	customRandom(unsigned int seeed) {
		seed = seeed;
		lastNumber = (T)(seeed ^ 0x9E3779B97F4A7C15ULL);  
		counter = 0;
		garbage = &seed;
		garbage -= 11;
		garbageCadangan = garbage;
	}
	T gen() {
		counter++;
		if (counter >= maxT) {
			seed = rd();
			counter = 1;
		}
		long long noise1 = (long long)garbage;
		long long noise2 = (long long)*garbage;
		long long noise3 = (long long)&noise1 * (long long)&noise2 * (long long)&noise3;
		T n = lastNumber;
		n ^= (n << 13);
		n ^= noise1;

		n ^= (n >> 7);
		n ^= noise2;

		n ^= (n << 17);
		n ^= noise3;

		n += (counter & 63) - 16;

#ifdef STABLEDISTRIBUTION

		n -= (bias - n) >> bitwise; // Make the number doesn't in bias (getting away from mean)
		bias = bias + (n - bias)/(counter + 1); // Incremental mean
#endif

		lastNumber = n;
		garbage += ((int)lastNumber & 31) + 1 - 17;
		if(*garbage == 0) garbage = garbageCadangan;
		return lastNumber;
	}
};
#endif
