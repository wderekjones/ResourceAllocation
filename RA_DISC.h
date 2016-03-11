#pragma once

#ifndef RA_DISC
#define RA_DISC


#include <vector>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <algorithm>

#include <time.h>




class Agent;

class Utils
{
public:
	std::vector<int> GeneticAlgorithm(std::vector<double> ancestor, double fitness, double epsilon)
	{
		int runs = 0;

		int selectedI = 0;

		

		std::vector<std::vector<int>> population = generatePopulation(1000, ancestor.size());
		
		double min_fitness = 1.0;


		do{

			std::vector<std::vector<int>> new_population;
			for (int i = 0; i < population.size(); i++)
			{

				int p1 = 0;
				int p2 = 0;

				p1 = rand() % population.size();
				p2 = rand() % population.size();

				std::vector<int> mother = random_selection(population); //randomly select a member of the population
				std::vector<int> father = random_selection(population); 
				std::vector<int> child = reproduce(mother,father,ancestor);

				// randomly determine whether or not to mutate the child
				if( p1 > p2 )
				{
					child = mutate(child);
				}
				new_population.push_back(child);

				
				if (fitnessFunction(population[i],ancestor, fitness) < min_fitness)
				{
					min_fitness = fitnessFunction(population[i],ancestor, fitness);
				}
			}
			population = new_population;

			runs++;
			
		}while((min_fitness) > epsilon);
		
		for(int i = 0; i < population.size(); i++)
		{
			double cand_fitness = fitnessFunction(population[i],ancestor,fitness);
			if(cand_fitness <= min_fitness)
			{
				min_fitness = cand_fitness;
				selectedI = i;

			}
		}

		return population[selectedI];
	}

	std::vector<std::vector<int>> generatePopulation(int size, int row_size)
	{
		std::vector<std::vector<int>> apopulation;

		for (int i = 0; i < size; i++)
		{
			int rLength = 0;
			rLength = rand() % row_size;
			std::vector<int> iVec;

			for(int j = 0; j < rLength; j++)
			{
				int r;
				r = rand() % (row_size);
				iVec.push_back(r);
			}
			
			apopulation.push_back(iVec);
		}

		std::sort(apopulation.begin(),apopulation.end());
		auto last = std::unique(apopulation.begin(),apopulation.end());
		apopulation.erase(last,apopulation.end());

		return apopulation;

	}


	std::vector<int> random_selection(std::vector<std::vector<int>> population)
	{

		std::vector<int> neo;

		int selectedI = 0;

		selectedI = rand() % population.size();

		neo = population[selectedI];

		return neo;

	}

	std::vector<int> mutate(std::vector<int> member)
	{
		std::vector<int> mutant;
		mutant.resize(member.size());

		for(int i =0 ; i < member.size() ; i++)
		{
			int r_i = 0; 
			r_i = rand() % (member.size());
			mutant[i] = member[r_i];
		}

		return mutant;
	}

	std::vector<int> reproduce(std::vector<int> mother, std::vector<int> father, std::vector<double> ancestor)
	{
		int c;

		std::vector<int> child;

		if(mother.size() == 0)
		{
			return child;
		}
		if(father.size() == 0)
		{
			return child;
		}
	
		if (mother.size() > father.size())
		{
			c = rand() % father.size();
		}
		else {
			c = rand() % mother.size();
		}


		child.insert(child.end(),mother.begin(),(mother.end() -c));
		child.insert(child.end(),father.begin() + c, father.end());
		

		/* the last 3 lines order the pieces in the resulting child 
			and remove copies in order to ensure that each of the pieces
			making up the child are distinct
		*/
		std::sort(child.begin(),child.end());
		auto last = std::unique(child.begin(),child.end());
		child.erase(last,child.end());
		
		return child;

	}


	double fitnessFunction(std::vector<int> formula,std::vector<double> ancestor, double alpha)
	{

		double fitness = 1;
		double sum = 0;

		for (int i = 0; i <formula.size(); i++)
		{
			sum += (ancestor[formula[i]]);
		}
		fitness = std::abs(sum - alpha);
		if(fitness > 1)
		{
			fitness = 1;
		}

		return (fitness);
	}


};

class Agent
{
private:
	std::vector<double> valueDist;
	std::vector<int> cuts;
	int shareSize;
	double shareValue;
public:

	void generateValueDist(int rSize)
	{
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

	void set_cuts(std::vector<int> c)
	{
		cuts = c;
	}

	std::vector<int> get_cuts()
	{
		return cuts;
	}

	void set_shareSize(int s)
	{
		shareSize = s;
	}

	int get_shareSize()
	{
		return shareSize;
	}

	void set_shareValue(double v)
	{
		shareValue = v;
	}

	double get_shareValue()
	{
		return shareValue;
	}


	double eval(int S)
	{
		return valueDist[S];
	};

	std::vector<int> cut(double alpha)
	{
		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_real_distribution<double> intDist(0, valueDist.size());

		std::vector<int> cuts;

		Utils alg;

		cuts = alg.GeneticAlgorithm(valueDist, alpha, 0.5); //generate a sequence of cuts for an agent such that the fitness is equal to alpha 

		return cuts;
	}

};


class Protocol
{

public:
	void cut_and_choose(Agent* a, Agent* b, double alpha)
	{
		std::vector<int> cake;

		cake.resize(a->get_value_dist().size());

		std::vector<double> a_value = a->get_value_dist();
		std::vector<double> b_value = b->get_value_dist();

		std::vector<int> cuts;


		cuts = a->cut(alpha); //find a set of pieces that sum up to equal alpha, here player 1 makes their cuts;



		std::sort(cuts.begin(),cuts.end());
		auto last = std::unique(cuts.begin(),cuts.end());
		cuts.erase(last,cuts.end());

		std::vector<int> bcuts;



		double asum = 0;
		double bsum = 0;

		for(int i = 0; i <cuts.size(); i++)
		{
			asum += a_value[cuts[i]];
			bsum += b_value[cuts[i]];

		}
		

		bcuts.resize(b_value.size() - cuts.size());
		//std::cout<<"size of player 2's share: "<<bcuts.size()<<std::endl;

		
		//std::cout<<"Player 1 values piece 1 as = "<<asum<<std::endl;

		if( (1-bsum) > bsum)
		{
			//std::cout<<"Player 2 chooses piece 2 , value = "<< (1-bsum)<<std::endl;
			//std::cout<<"Player 1 is left with piece 1, value = "<<(asum)<<std::endl; 

			a->set_shareValue(asum);
			a->set_shareSize(cuts.size());

			b->set_shareValue(1-bsum);
			b->set_shareSize(bcuts.size());

		}
		else if( (1-bsum) < bsum)
		{
			//std::cout<<"Player 2 chooses piece 1, value = "<<bsum<<std::endl;
			//std::cout<<"Player 1 is left with piece 2, value ="<<(1 - asum)<<std::endl;

			a->set_shareValue(1-asum);
			a->set_shareSize(bcuts.size());

			b->set_shareValue(bsum);
			b->set_shareSize(cuts.size());
		}
		else{
			//std::cout<<"Player 2 values each piece equally "<<bsum<<std::endl;
			//std::cout<<"Player 1 values piece 1 as "<<asum<<", and piece 2 as "<<(1-asum)<<std::endl;

			if( asum > (1-asum))
			{
				a->set_shareValue(asum);
				a->set_shareSize(cuts.size());

				b->set_shareValue(1-bsum);
				b->set_shareSize(bcuts.size());
			}
			else if( asum < (1-asum))
			{
				a->set_shareValue((1-asum));
				a->set_shareSize(bcuts.size());

				b->set_shareValue(bsum);
				b->set_shareSize(cuts.size());
			}
		}



		

	}

};








#endif
