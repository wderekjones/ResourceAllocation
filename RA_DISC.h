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



class Utils
{
public:
	std::vector<double> GeneticAlgorithm(std::vector<double> ancestor, double fitness)
	{
		int max_runs = pow(2, ancestor.size());
		int run = 0;

		int selectedI = 0;

		std::vector<std::vector<double>> population = generatePopulation(100, ancestor);

		double min_fitness = 1.0;

		for (int i = 0; i < population.size(); i++)
		{
			if (fitnessFunction(population[i], fitness) < min_fitness)
			{
				min_fitness = fitnessFunction(population[i], fitness);
				selectedI = i;
			}
		}


		return population[selectedI];
	}

	std::vector<std::vector<double>> generatePopulation(int size, std::vector<double> ancestor)
	{
		std::vector<std::vector<double>> apopulation;
		for (int i = 0; i < size; i++)
		{
			apopulation.push_back(random_selection(ancestor));
		}

		return apopulation;

	}

	std::vector<double> random_selection(std::vector<double> population)
	{
		std::vector<double> copy = population;

		std::vector<double> neo;

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


	double fitnessFunction(std::vector<double> formula, double alpha)
	{

		double fitness = 1;
		double sum = 0;


		for (int i = 0; i <formula.size(); i++)
		{
			sum += formula[i];
		}

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

	std::vector<double> cut(double alpha)
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

		std::vector<double> cuts;

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
		std::vector<double> cuts;

		cuts = a.cut(.5);

	}

};








#endif