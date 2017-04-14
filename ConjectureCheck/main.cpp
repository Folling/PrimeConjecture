#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <conio.h>

std::vector<int> findAllPrimesUntilX(int x);
bool checkPrime(int x);
int sumDeca(int x);
//enter the amount of numbers to check
const int upToXthPrimes = 10000000;
std::vector<int> primes = findAllPrimesUntilX(upToXthPrimes);
int decaCount = 0;
int primeCount , threeCount, valIntervCount;
static int prevPrime = 0;

int main() {	
	//checks whether we've reached the intervals as large as the numbers we checked primes for
	while (decaCount * 10 <= upToXthPrimes) {
		if (decaCount % 50 == 0) std::cout << "Checked the first " << decaCount << " Intervals!" <<std::endl;
		for (int i = prevPrime; i < primes.size(); i++) {
			if (primes[i] > (decaCount + 1) * 10)
			{
				prevPrime = i;
				break;
			}
			else if (primes[i] <= decaCount)continue;
			else primeCount++;
		}
		if (primeCount == 3) threeCount++;
		if (sumDeca(decaCount) % 3) valIntervCount++;
		if (primeCount != 0) {
			if (sumDeca(decaCount) % primeCount == 0) {
				decaCount++;
				primeCount = 0;
			}
			else {
				std::cout << "Found a disproof in the interval of: " << decaCount * 10+1 << " and " << (decaCount+1) * 10 << std::endl;
				_getch();
				exit(1);
			}
		}
		else {
			decaCount++;
		}
	}	
	std::cout << "No disproof found!\n";
	std::cout << "Intervals checked: " << decaCount-1 << std::endl;
	std::cout << "Primes used: " << primes.size() << std::endl;
	std::cout << "Numbers checked: " << upToXthPrimes << std::endl;
	std::cout << "Intervals with three primes: " << threeCount << std::endl;
	std::cout << "Intervals which aren't divisible by 3: " << valIntervCount << std::endl;
	_getch();
}

//returns all primes until x in a vector
std::vector<int> findAllPrimesUntilX(int x) {
	std::vector <int> result;
	for (int i = 1; i <= x; i++) {
		if (i % 500 == 0) std::cout << "The first " << i << " numbers have been checked for whether they're prime.\n";
		if (checkPrime(i)) result.push_back(i);
	}
	std::cout << "All primes have been calculated!\n";
	return result;
}

//checks whether a number is prime
bool checkPrime(int n) {
	if (n == 2) return true;
	if (n < 2 || n % 2 == 0) return false;

	for (int i = 3; i<=sqrt(n); i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

//takes an input and sums it up until it reaches the next 10th e.g. 10+11+12+..+19
int sumDeca(int x) {
	int sum = 0;
	for (int current = (x * 10)+1; current <= (x+1) * 10; current++) {
		sum += current;
	}
	return sum+1;
}

//I apologise if the commenting on this code is not ideal, if you have any questions feel free to ask