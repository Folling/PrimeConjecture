#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h>

// this code requires you to have openMP optimizations enabled

void findAllPrimesUntilX(int x);
bool checkPrime(int x);
int sumDeca(int x);

//enter the amount of numbers to check
const int upToXthPrimes = 10000000;
std::vector<int> primes;
int primeCount, threeCount, valIntervCount;

int main() {
	findAllPrimesUntilX(upToXthPrimes);
	//checks whether we've reached the intervals as large as the numbers we checked primes for
	int prevPrime = 0;
	int decaCount = 0;
	while (decaCount * 10 <= upToXthPrimes) {
		if (decaCount % 50 == 0) std::cout << "Checked the first " << decaCount << " Intervals!" << std::endl;
		for (int i = prevPrime; i < primes.size(); i++) {
			if (primes[i] >= (decaCount + 1) * 10)
			{
				prevPrime = i;
				break;
			}
			else if (primes[i] < (decaCount * 10) + 1) continue;
			primeCount++;
		}
		if (primeCount == 3) threeCount++;
		if (sumDeca(decaCount) % 3) valIntervCount++;
		if (primeCount != 0) {
			if (sumDeca(decaCount) % primeCount == 0) {
				decaCount++;
				primeCount = 0;
			}
			else {
				std::cout << "Found a disproof in the interval of: " << decaCount * 10 + 1 << " and " << (decaCount + 1) * 10 << std::endl;
				_getch();
				exit(1);
			}
		}
		else {
			decaCount++;
		}
	}
	std::cout << "No disproof found!\n";
	std::cout << "Intervals checked: " << decaCount - 1 << std::endl;
	std::cout << "Primes used: " << primes.size() << std::endl;
	std::cout << "Numbers checked: " << upToXthPrimes << std::endl;
	std::cout << "Intervals with three primes: " << threeCount << std::endl;
	std::cout << "Intervals which aren't divisible by 3: " << valIntervCount << std::endl;
	_getch();
}

//returns all primes until x in a vector
void findAllPrimesUntilX(int x) {
	for (int i = 1; i <= x; i++) {
		if (i % 500 == 0) std::cout << "The first " << i << " numbers have been checked for whether they're prime.\n";
		if (checkPrime(i)) primes.push_back(i);
	}
	std::cout << "All primes have been calculated!\n";
}

//checks whether a number is prime
bool checkPrime(int n) {
	int s = sqrt(n);
	if (n == 2) return true;
	if (n < 2 || n % 2 == 0) return false;
	bool prime = true;

#pragma omp parallel for
	for (int i = 3; i <= s; i += 2) {
		if (n % i == 0) prime = false;
	}

	return prime;
}

//takes an input and sums it up until it reaches the next 10th e.g. 10+11+12+..+19
int sumDeca(int x) {
	int sum = 0;
	for (int current = (x * 10) + 1; current <= (x + 1) * 10; current++) {
		sum += current;
	}
	return sum + 1;
}
