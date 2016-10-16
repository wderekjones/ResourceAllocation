#pragma once

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
	std::vector<int> GeneticAlgorithm(std::vector<int> ancestor, std::vector<double> value_dist, double fitness)
	{
		int selectedI = 0;

		std::vector<std::vector<int>> population = generatePopulation(1000, ancestor.size());

		double min_fitness = 1.0;

		for(int r = 0 ; r < 10; r++)
		{

			std::vector<std::vector<int>> new_population;
			for (int i = 0; i < population.size(); i++)
			{

				int p1 = 0;
				int p2 = 0;

				p1 = (rand() +1) % population.size();
				p2 = (rand() +1) % population.size();

				//randomly select a member of the population

				std::vector<int> mother = random_selection(population,value_dist,fitness);

				std::vector<int> father = random_selection(population,value_dist,fitness);

				std::vector<int> child = reproduce(mother,father,ancestor);

				// randomly determine whether or not to mutate the child
				if( p1 > p2 )
				{
					child = mutate(child);
				}
				new_population.push_back(child);


				if (fitnessFunction(population[i],value_dist, fitness) < min_fitness)
				{
					min_fitness = fitnessFunction(population[i],value_dist, fitness);
				}
			}
			population = new_population;

			}

			for(int i = 0; i < population.size(); i++)
			{
				double cand_fitness = fitnessFunction(population[i],value_dist,fitness);
				if(cand_fitness < min_fitness)
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

		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_int_distribution<int> intDist(0, 1);

		for (int i = 0; i < size; i++)
		{
			std::vector<int> iVec;

			for(int j = 0; j < row_size; j++)
			{
				int r;
				r = intDist(mt);
				iVec.push_back(r);
			}

			apopulation.push_back(iVec);
		}


		return apopulation;

	}


	std::vector<int> random_selection(std::vector<std::vector<int>> population, std::vector<double> value_d, double alpha)
	{

		/*

				1: randomly select an index

				2: evaluate fitness of selection
					if fitness is < minimum fitness so far -> selected i = current i


		*/
		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_int_distribution<int> indexDist(0, population.size());


		std::vector<int> neo;

		int selectedI = 0;

		double bestfitness = 1.0;
		for(int i = 0; i < population.size(); i++ )
		{
			double curFitness = fitnessFunction(population[i], value_d, alpha);
			if(curFitness < bestfitness)
			{
				selectedI = i;
				bestfitness = curFitness;

			}
		}

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

	std::vector<int> reproduce(std::vector<int> mother, std::vector<int> father, std::vector<int> ancestor)
	{


		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);

		int c;

		std::vector<int> child;


		if (mother.size() > father.size())
		{
			std::uniform_int_distribution<int> intDist(1, father.size());

			c = intDist(mt);

			child.insert(child.end(),mother.begin(),(mother.end() -c));
			child.insert(child.end(),father.end()-c, father.end());
		}
		else if (father.size() > mother.size())
		{
			std::uniform_int_distribution<int> intDist(1, mother.size());

			c = intDist(mt);

			child.insert(child.begin(),father.begin(),(father.end() -c));
			child.insert(child.end(),mother.end() - c, mother.end());
		}
		else
		{
			std::uniform_int_distribution<int> intDist(1, father.size());

			c = intDist(mt);


			child.insert(child.begin(),mother.begin(),(mother.end() -c));
			child.insert(child.end(),father.end() - c, father.end());
		}

		return child;

	}


	double fitnessFunction(std::vector<int> candidate,std::vector<double> value_d, double alpha)
	{

			double fitness = 0;
			double sum = 0;

			for (int i = 0; i <candidate.size(); i++)
			{
				sum += (value_d[i]*(double)candidate[i]);
			}
			fitness = std::abs(sum - alpha);

		return fitness;
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

		std::vector<double> nums;
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

	void set_value_dist(std::vector<double> new_val_dist)
	{
		valueDist = new_val_dist;
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


	double eval_piece(int S)
	{
		return valueDist[S];
	};

	double eval_share(std::vector<int> S)
	{
		double sum = 0.0;


		for(int i = 0 ; i < S.size(); i++)
		{
				sum+=valueDist[S[i]];

		}
		return sum;
	}

	std::vector<int> cut(std::vector<int> piece , double alpha)
	{
		std::vector<int> cuts;

		Utils alg;

		cuts = alg.GeneticAlgorithm(piece,Agent::valueDist,alpha);

		return cuts;
	}

};






class Protocol
{

public:

	void take_turn(Agent* p, double sValue, int sSize)
	{
		p->set_shareValue(sValue);
		p->set_shareSize(sSize);

	}


	void cut_and_choose(Agent* a, Agent* b, double alpha)
	{
		std::vector<int> a_cake;
		std::vector<int> b_cake;



		std::vector<double> a_value = a->get_value_dist();
		std::vector<double> b_value = b->get_value_dist();

		for(int i = 0 ; i < a_value.size(); i++)
		{
			a_cake.push_back(i);
			b_cake.push_back(i);
		}

		std::vector<int> acuts;
		std::vector<int> bcuts;

		acuts = a->cut(a_cake, alpha); //find a set of pieces that sum up to equal alpha, here player 1 makes their cuts;


		double sum = 0.0;

		for(int i = 0; i < acuts.size(); i++)
		{
			sum+=(acuts[i]*a_value[i]);
		}

		for(int i = 0; i < acuts.size(); i ++)
		{
				if(acuts[i] == 0)
				{
					a_cake[i] =0;
				}
		}

		for( int i = 0 ; i < a_cake.size(); i++)
		{
			if(a_cake[i] == 0)
			{
				a_cake.erase(a_cake.begin()+i);
				i = 0;
			}
		}

		for(int i = 0; i < a_cake.size(); i++)
		{
			for(int j = 0; j < b_cake.size(); j++)
			{
				if(a_cake[i] == b_cake[j])
				{
					b_cake.erase(b_cake.begin()+j);
				}
			}
		}


		if( b->eval_share(a_cake) > b->eval_share(b_cake))
		{
			take_turn(b,b->eval_share(a_cake), a_cake.size());
			take_turn(a,a->eval_share(b_cake), b_cake.size());
		}

		else{
			take_turn(b,b->eval_share(b_cake), b_cake.size());
			take_turn(a,a->eval_share(a_cake), a_cake.size());
		}

		std::cout<<(b->get_shareValue())<<(b->get_shareSize())<<"\n";
		std::cout<<(a->get_shareValue())<<(b->get_shareSize())<<std::endl;

	}

	void last_diminisher(std::vector<Agent*> players)
	{



	}




};
