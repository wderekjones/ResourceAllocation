#pragma once

#ifndef RA_DISC
#define RA_DISC


#include <stdio.h>
#include <vector>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <algorithm>

class Agent;

class Utils
{
public:
	std::vector<int> GeneticAlgorithm(std::vector<double> ancestor, double fitness)
	{
		int max_runs = pow(2, ancestor.size());
		int run = 0;

		std::vector<int> c;
		c.resize(ancestor.size());

		int selectedI = 0;

		std::vector<std::vector<int>> population = generatePopulation(100, ancestor.size());

		double min_fitness = 1.0;

		for (int i = 0; i < population.size(); i++)
		{
			if (fitnessFunction(population[i],ancestor, fitness) < min_fitness)
			{
				min_fitness = fitnessFunction(population[i],ancestor, fitness);
				selectedI = i;
			}
		}


		return population[selectedI];
		//return c;
	}

	std::vector<std::vector<int>> generatePopulation(int size, int row_size)
	{
		std::vector<std::vector<int>> apopulation;

		std::vector<int> iVec;

		for(int i = 0; i < row_size; i++)
		{
			iVec.push_back(i);
		}

		for (int i = 0; i < size; i++)
		{
			apopulation.push_back(random_selection(iVec));
		}

		return apopulation;

	}

	std::vector<int> random_selection(std::vector<int> population)
	{
		std::vector<int> copy = population;

		std::vector<int> neo;

		int rLength = rand() % (population.size() + 1);

		for (int i = 0; i <rLength; i++)
		{
			int rI = rand() % copy.size();
			neo.push_back(copy[rI]);
			copy.erase(copy.begin() + rI);
		}

		return neo;

	}

	/*std::vector<double> reproduce(std::vector<double> mother, std::vector<double> father)
	{
		int c;

		if (mother.size() > father.size())
		{
			c = rand() % father.size();
		}
		else {
			c = rand() % mother.size();
		}

		std::vector<double> child;

		child.insert(child.begin(), mother.begin(), mother.end() - c);
		child.insert(child.end(), father.end() - c, father.end());

		return child;

	}*/


	double fitnessFunction(std::vector<int> formula,std::vector<double> ancestor, double alpha)
	{

		double fitness = 1;
		double sum = 0;


		for (int i = 0; i <formula.size(); i++)
		{
			sum += ancestor[formula[i]];
			//std::cout<<ancestor[formula[i]]<<" ";
			//std::cout<<formula[i]<<" ";
		}
		//std::cout<<std::endl;

		if (sum >= 0)
		{
			fitness = std::abs(sum - alpha);
		}
		//std::cout<<"fitness = "<<fitness<<std::endl;

		return fitness;
	}

	/*std::vector<double> mutate(std::vector<double> member)
	{
		std::vector<double> current = member;
		int c = rand() % 2;
		int rIndex = rand() % current.size();

		current[rIndex] = c;

		return current;
	}*/

};

class Agent
{
private:
	std::vector<double> valueDist;
	std::vector<int> cuts;
public:

	std::vector<int> identify_piece(std::vector<double> alpha)
	{
		std::vector<int> p_index;
		for(int i = 0; i <valueDist.size(); i++)
		{
			for(int j = 0; j< alpha.size(); j++)
			{
				if(valueDist[i] == alpha[j])
				{
					p_index.push_back(i);
				}
			}
		}
		return p_index;
	}

	void generateValueDist(int rSize)
	{
		//valueDist.clear();

		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_int_distribution<int> intDist(6, 12);

		std::vector<int> nums;
		int sum = 0;

		for (int i = 0; i < rSize; i++)
		{
			int rInt = intDist(mt);
			nums.push_back(rInt);
			sum += rInt;
		}

		for (int i = 0; i < rSize; i++)
		{
			double entry;
			entry = nums[i] / (double)sum;
			valueDist.push_back(entry);
		}

	}

	void dumpValueDist()
	{
		for (int i = 0; i < valueDist.size(); i++)
		{
			std::cout << valueDist[i] << " ";
		}
		std::cout << std::endl;
	}

	std::vector<double> get_value_dist()
	{
		return valueDist;
	}

	double eval(int S)
	{
		return valueDist[S];
	};

	std::vector<int> cut(double alpha)
	{

		int start = 0;
		int end = 0;

		/* 0 <= alpha <= 1
		require player_i either to return the value x \in S = [s_1,s_2] such that vi([s1,x]) = alpha
		(that is, the protocol asks p_i to cut - or make a marking - at a point x to produce (or mark)
		a subpiece of value alpha), or to announce that this is impossible because no such x exists in S.
		*/
		/*
		Solution idea: write a recursive function that enumerates all subsets of the value_distribution for
		an agent and greedily try all of them. If no subsets of size k exist to solve the problem, call the function
		again and find all subsets of size k = k + 1 as long as k < n else we have exhausted all possibilities.

		Maybe use a genetic algorithm or A* search in the future?
		*/

		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_real_distribution<double> intDist(0, valueDist.size());

		std::vector<int> cuts;

		Utils alg;

		cuts = alg.GeneticAlgorithm(valueDist, alpha); //generate a sequence of cuts for an agent such that the fitness is equal to alpha 

		return cuts;
	}

};


class Protocol
{

public:
	void cut_and_choose(Agent a, Agent b)
	{
		std::vector<int> cake;

		cake.resize(a.get_value_dist().size());

		std::vector<double> a_value = a.get_value_dist();
		std::vector<double> b_value = b.get_value_dist();

		std::vector<int> cuts;

		cuts = a.cut(.5); //find a set of pieces that sum up to equal alpha, here player 1 makes their cuts;

		double asum = 0;
		double bsum = 0;

		for(int i = 0; i <cuts.size(); i++)
		{
			asum += a_value[cuts[i]];
			bsum += b_value[cuts[i]];
		}

		std::cout<<"Player 1 values piece 1 as = "<<asum<<std::endl;

		if( (1-bsum) > bsum)
		{
			std::cout<<"Player 2 chooses piece 2 , value = "<< (1-bsum)<<std::endl;
			std::cout<<"Player 1 is left with piece 1, value = "<<(asum)<<std::endl; 
		}
		else if( (1-bsum) < bsum)
		{
			std::cout<<"Player 2 chooses piece 1, value = "<<bsum<<std::endl;
			std::cout<<"Player 1 is left with piece 2, value ="<<(1 - asum)<<std::endl;
		}
		else{
			//std::cout<<"Player 2 values piece 1 and piece 2 equally, chooses piece 1, value = "<<bsum<<std::endl;
			//std::cout<<"Player 1 is left with piece 2, value = "<<asum<<std::endl;
			std::cout<<"Player 2 values each piece equally "<<bsum<<std::endl;
			std::cout<<"Player 1 values piece 1 as "<<asum<<", and piece 2 as "<<(1-asum)<<std::endl;
		}





	}

};








#endif