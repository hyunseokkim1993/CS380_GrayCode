/*
 *Kevin Kim
 *CS330
 */
#ifndef KNAPSACK_BRUTE_FORCE_MINCHANGE
#define KNAPSACK_BRUTE_FORCE_MINCHANGE
#include <utility>   // std::pair
#include <vector>
#include <bitset>
#include "definitions.h"

class GreyCode {
public:
	GreyCode(int s);
	std::pair< bool, std::pair< bool, int > > Next();
private:
	const int Size;
	int permutationCount;
	int countdown; //countdown to increase in prefix

	int iterLimit;
	
	std::vector<bool> prev;
	std::vector<int> change;
};
std::vector<bool> knapsack_brute_force(std::vector<Item> const& items, Weight const& W);
#endif
