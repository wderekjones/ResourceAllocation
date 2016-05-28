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
	/*std::vector<int> GeneticAlgorithm(std::vector<double> ancestor, double fitness, double epsilon)
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

				std::vector<int> mother = random_selection(population,ancestor,fitness); //randomly select a member of the population
				std::vector<int> father = random_selection(population,ancestor,fitness);
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

		return apopulation;

	}


	std::vector<int> random_selection(std::vector<std::vector<int>> population, std::vector<double> ancestor, double alpha)
	{

		std::vector<int> neo;

		std::vector<double> pop_fitness;

		double fit_sum = 0.0;

		for(int i = 0 ; i < population.size(); i++)
		{
			pop_fitness.push_back(fitnessFunction(population[i],ancestor,alpha));
			fit_sum+=pop_fitness[i];
		}

		std::vector<double> prop_pop_fitness;

		for (int i = 0; i < pop_fitness.size(); ++i)
		{
			prop_pop_fitness.push_back(pop_fitness[i]/fit_sum);
		}

		int selectedI = 0;

		selectedI = rand() % population.size();

		double cutoff = 0;

		cutoff = prop_pop_fitness[selectedI];

		int tries = 0;
		while(tries < 1000)
		{
			selectedI = rand() % population.size();

			if(prop_pop_fitness[selectedI] >= cutoff)
			{
				neo = population[selectedI];
				return neo;
			}

			tries++;
		}

		selectedI = 0;
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
	}*/

	std::vector<double> doubleGeneticAlgorithm(std::vector<double> ancestor, double fitness, double epsilon)
	{
		int runs = 0;

		int selectedI = 0;

		std::vector<std::vector<double>> population = doublegeneratePopulation(1000, ancestor);

		double min_fitness = 1.0;


		do{

			std::vector<std::vector<double>> new_population;
			for (int i = 0; i < population.size(); i++)
			{

				int p1 = 0;
				int p2 = 0;

				p1 = rand() % population.size();
				p2 = rand() % population.size();

				std::vector<double> mother = doublerandom_selection(population,ancestor,fitness); //randomly select a member of the population
				std::vector<double> father = doublerandom_selection(population,ancestor,fitness);
				std::vector<double> child = doublereproduce(mother,father,ancestor);

				// randomly determine whether or not to mutate the child
				if( p1 > p2 )
				{
					child = doublemutate(child);
				}
				new_population.push_back(child);


				if (doublefitnessFunction(population[i] ,fitness) < min_fitness)
				{
					min_fitness = doublefitnessFunction(population[i], fitness);
				}
			}
			population = new_population;

			runs++;

		}while((min_fitness) > epsilon);

		for(int i = 0; i < population.size(); i++)
		{
			double cand_fitness = doublefitnessFunction(population[i],fitness);
			if(cand_fitness <= min_fitness)
			{
				min_fitness = cand_fitness;
				selectedI = i;

			}
		}

		return population[selectedI];
	}

	std::vector<std::vector<double>> doublegeneratePopulation(int size,std::vector<double> ancestor)
	{

		std::vector<std::vector<double>> apopulation;

		for (int i = 0; i < size; i++)
		{
			int rLength = 0;
			rLength = rand() % ancestor.size();
			std::vector<double> dVec;


			for(int j = 0; j < rLength; j++)
			{
				double r;
				r = rand() % (ancestor.size());
				//dVec.push_back(r);
			}

			//apopulation.push_back(dVec);
			std::cout<<dVec.size()<<std::endl;
		}

		return apopulation;

	}


	std::vector<double> doublerandom_selection(std::vector<std::vector<double>> population, std::vector<double> ancestor, double alpha)
	{

		std::vector<double> neo;




		std::vector<double> pop_fitness;

		double fit_sum = 0.0;

		for(int i = 0 ; i < population.size(); i++)
		{
			pop_fitness.push_back(doublefitnessFunction(population[i],alpha));
			fit_sum+=pop_fitness[i];
		}

		std::vector<double> prop_pop_fitness;

		for (int i = 0; i < pop_fitness.size(); ++i)
		{
			prop_pop_fitness.push_back(pop_fitness[i]/fit_sum);
		}

		int selectedI = 0;

		//selectedI = rand() % population.size();

		double cutoff = 0;

		cutoff = prop_pop_fitness[selectedI];

		int tries = 0;
		while(tries < 1000)
		{
			selectedI = rand() % population.size();

			if(prop_pop_fitness[selectedI] >= cutoff)
			{
				neo = population[selectedI];
				return neo;
			}

			tries++;
		}

		selectedI = 0;
		neo = population[selectedI];
		return neo;

	}

	std::vector<double> doublemutate(std::vector<double> member)
	{
		std::vector<double> mutant;
		mutant.resize(member.size());

		for(int i =0 ; i < member.size() ; i++)
		{
			int r_i = 0;
			r_i = rand() % (member.size());
			mutant[i] = member[r_i];
		}

		return mutant;
	}

	std::vector<double> doublereproduce(std::vector<double> mother, std::vector<double> father, std::vector<double> ancestor)
	{
		int c;

		std::vector<double> child;

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


		return child;

	}


	double doublefitnessFunction(std::vector<double> candidate, double alpha)
	{

		double fitness = 1;
		double sum = 0.0;

		for (int i = 0; i <candidate.size(); i++)
		{
			sum += candidate[i];
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
		double sum = 0;

		if(S.size() == 1 )
		{
			sum = eval_piece(S[0]);
		}
		else if (S.size() == 0)
		{
			sum = 0;
		}
		else
		{
			for(int i = 0; i < S.size(); i ++)
			{
				sum += valueDist[S[i]];
			}
		}

		return sum;
	}

	std::vector<double> doublecut(std::vector<double> piece, double alpha)
	{

		std::vector<double> cuts;

		Utils alg;

		cuts = alg.doubleGeneticAlgorithm(piece, alpha, 0.5); //generate a sequence of cuts for an agent such that the fitness is equal to alpha

		return cuts;
	}




	/*std::vector<double> doublediminish_cut(std::vector<double> C, double alpha, double epsilon)
	{

		std::vector<double> dim_C;
		double min_value = 1.0;
		int min_value_index = 0;

		for(int i = 0; i< C.size(); i++)
		{
			if(Agent::eval_piece(C[i]) <= min_value)
			{
				min_value = Agent::eval_piece(C[i]);
				min_value_index = i;
			}
		}
		dim_C = C;
		if(C.size()>2)
		{
			dim_C.erase(dim_C.begin()+min_value_index);
		}
		return dim_C;
	}*/

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
		std::vector<double> cake;



		std::vector<double> a_value = a->get_value_dist();
		std::vector<double> b_value = b->get_value_dist();

		std::vector<double> cuts;
		std::vector<double> bcuts;

		cuts = a->doublecut(a->get_value_dist(),alpha); //find a set of pieces that sum up to equal alpha, here player 1 makes their cuts;

		std::sort(cuts.begin(),cuts.end());
		auto last = std::unique(cuts.begin(),cuts.end());
		cuts.erase(last,cuts.end());

		bcuts.resize(b_value.size() - cuts.size());


		double asum = 0;
		double bsum = 0;

		for(int i = 0; i <cuts.size(); i++)
		{
			asum += a_value[cuts[i]];
			bsum += b_value[cuts[i]];

		}

		/*
			Player 1 makes the cut, now Player 2 chooses
		*/
		if( (1-bsum) > bsum)
		{
			/*
				Player 2 has chosen piece 2, Player 1 is left with piece 1
			*/
			take_turn(a,asum,cuts.size());
			take_turn(b,(1-bsum),bcuts.size());
		}
		else if( (1-bsum) < bsum)
		{
			/*
				Player 2 has chosen piece 1, Player 2 is left with piece 2
			*/
			take_turn(a,(1-asum),bcuts.size());
			take_turn(b,(bsum),cuts.size());
		}
		else{
			/*
				Player 2 values piece 1 and piece 2 equally, so due to indecisiveness of Player 2, Player 1
				must make the decision
			*/
			if( asum > (1-asum))
			{
				take_turn(a,asum,cuts.size());
				take_turn(b,(1-bsum),bcuts.size());
			}
			else if( asum <= (1-asum))
			{
				take_turn(a,(1-asum),bcuts.size());
				take_turn(b,bsum,cuts.size());
			}
		}
	}

	void last_diminisher(std::vector<Agent*> players)
	{


		double alpha = double(1.0/players.size());
		std::cout<<"alpha = "<<alpha<<std::endl;


		std::vector<double> cuts;
		cuts = players[0]->get_value_dist();

		//cuts.pop_back();
		// STEP 1: player p[0] cuts piece S0 such that V_0(S_0) = alpha

		cuts = players[0]->doublecut(cuts,alpha); // heres the floating point exception bug

		std::cout<<"size of cuts = "<<cuts.size();

		/*std::sort(cuts.begin(),cuts.end());
		auto last = std::unique(cuts.begin(),cuts.end());
		cuts.erase(last,cuts.end());*/


		for(int i = 0 ; i < cuts.size(); i++)
		{
			std::cout<<" "<<cuts[i]<<" ";
		}



		/*for(int i = 0; i < cuts.size(); i++)
		{
			std::cout<<cuts[i]<<" ";
		}*/



		//std::vector<double> v_dist = players[0]->get_value_dist();

		//for(int i = 0 ; i < v_dist.size(); i ++)
		//{
			//std::cout<<v_dist[i]<<" |";
		//}


		//std::cout<<std::endl;


		//std::vector<double> d_v_dist;

		//d_v_dist = players[0]->doublediminish_cut(players[0]->get_value_dist(),alpha,0);
		//v_dist.pop_back();

		//d_v_dist = cuts;

		/*for(int i = 0 ; i < d_v_dist.size(); i ++)
		{
			std::cout<<d_v_dist[i]<<" |";
		}*/



	}



};
