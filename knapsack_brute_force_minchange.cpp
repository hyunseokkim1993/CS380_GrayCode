/*
 *Kevin Kim
 *CS330
 */

#include "knapsack_brute_force_minchange.h"
#include <iostream>
#include <math.h>

GreyCode::GreyCode(int s) : Size(s), permutationCount(1), countdown(1), iterLimit(0), prev(), change()
{
	iterLimit = static_cast<int>(pow(2,Size));
	prev.push_back(0);
	change.push_back(0);
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next()
{
	int pos = 0;// which position is modified 
	bool add = false;// is true if new value is 1 (add item), false otherwise 
	bool last = false;// is this the last permutation 

	permutationCount++;
	if (permutationCount == iterLimit)
	{
		last = true;
	}
	
	if (countdown == 0)
	{
		pos = prev.size();

		if(prev.size()==1)
		{
			prev.push_back(true);

			if (prev[pos] == true)
			{
				add = true;
			}

			countdown = permutationCount - 2;
			return std::make_pair(!last, std::make_pair(add, pos));
		}
		
		change.push_back(prev.size() - 1);
		change.insert(change.end(), change.begin(), change.end() - 1);

		prev.push_back(true);

		if (prev[pos] == true)
		{
			add = true;
		}

		countdown = permutationCount - 2;
		return std::make_pair(!last, std::make_pair(add, pos));
	}

	pos = change[countdown - 1];
	if (prev[pos] == true)
	{
		add = false;
		prev[pos] = false;
	}
	else
	{
		add = true;
		prev[pos] = true;
	}

	countdown--;
	return std::make_pair(!last, std::make_pair(add, pos));
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force( std::vector<Item> const& items, Weight const& W )
{
	int s = items.size();
	std::vector<bool> bag(s, false);
	std::vector<bool> best(s, false);

	GreyCode gc(s);
	bool go = true;
	int Value = 0;
	int Maximum = 0;
	Weight Weight;

	while (go) 
	{
		std::pair< bool, std::pair< bool, int > > r = gc.Next();
		go = r.first;
		bool add = r.second.first;
		int  pos = r.second.second;
		if (add) 
		{
			bag[pos] = true;
			Value += items[pos].GetValue();
			Weight += items[pos].GetWeight();
		}
		else 
		{
			bag[pos] = false;
			Value -= items[pos].GetValue();
			Weight -= items[pos].GetWeight();
		}
		if (Weight <= W && Value > Maximum) 
		{
			Maximum = Value;
			best = bag;
		}
	}
	return best;
}
