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

	std::vector<int> diminish_cut(std::vector<int> C, double alpha, double epsilon)
	{
		//double min_dim_fitness = Agent::eval_piece(copy_C[0]);
		//std::cout<<min_dim_fitness<<std::endl; 

		if(C.size() > 1 )
		{
			std::sort(C.begin(), C.end());
			if(Agent::eval_share(C) > alpha)
			{
				//std::cout<<"The player values the piece as "<<Agent::eval_share(copy_C)<<", which is more than alpha = "<<alpha<<std::endl;
				double diminshed_value = 0;
				diminshed_value = Agent::eval_share(C);
		
				int i = 0;
			}

				while(i < C.size() && !C.empty())
				{

					C.erase(C.begin(), C.begin() + 1);
					diminshed_value = Agent::eval_share(C);
					std::cout<<"Value after "<< (i+1)<<" cuts = "<<Agent::eval_share(C)<<std::endl;
					if(std::abs(diminshed_value - alpha) <= epsilon)
					{
						return C;
					}
					i++;
				}
			}
		}
		else
		{
			//std::cout<<"The player values this piece as = "<<Agent::eval_share(C)<<", less than or equal to alpha = "<<alpha<<std::endl;
			return C;
		}



		//return C;

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
		std::vector<int> cake;

		cake.resize(a->get_value_dist().size());

		std::vector<double> a_value = a->get_value_dist();
		std::vector<double> b_value = b->get_value_dist();

		std::vector<int> cuts;
		std::vector<int> bcuts;

		cuts = a->cut(alpha); //find a set of pieces that sum up to equal alpha, here player 1 makes their cuts;

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
		std::vector<int> cake;

		for (int i = 0; i < players[0]->get_value_dist().size(); i++)
		{
			cake.push_back(i);
		}

		int session_n = 0;
		double alpha = double(1.0/players.size());

		std::vector<int> cuts;
		//cuts = players[0]->cut(alpha);

		std::cout<<"initial cake.size() = "<<cake.size()<<std::endl;

		while(players.size() > 2)
		{

			// player 1 makes a cut that they feel has a value of 1 / n
			cuts = players[0] ->cut(alpha);

			//if n = 1 other players, then apply cut and choose protocol
			if(players.size() == 2)
			{
					cut_and_choose(players[0],players[1],0.5);
					players.pop_back();
					players.pop_back();
			}
			//else if n > 1 other players, then:
			else
			{
				// for each remaining player j (not the player at the front of the line) 
				for(int j = 1; j <players.size(); j ++ )
				{

					// evaluate the cut for round i, which is then passes to the next remaining player j + 1, until
					// there are no other players left to pass to. The player[j] with the cut at the end of the line
					// takes their share and drops out

					std::cout<<"player ["<<j<<"]: "<<players[j]->eval_share(cuts)<<std::endl;
				}
			}
		}



























			/*std::sort(cuts.begin(),cuts.end());
			auto last = std::unique(cuts.begin(),cuts.end());
			cuts.erase(last,cuts.end());

			std::cout<<"cuts["<<session_n<<"].size() = "<<cuts.size()<<std::endl;;
			

			for(int i = 0; i < players.size() - 1; i++)
			{
				std::vector<int> new_cuts;
				if( i > 0 && (i < players.size() - 2))
				{
					std::cout<<"player "<<i<<" values player"<<(i-1)<<"'s cut = "<<players[i]->eval_share(cuts)<<std::endl;
					new_cuts = players[i]->diminish_cut(cuts,alpha,0.05);
					cuts = new_cuts;
				}

			}

			if(players.size() == 2){
				std::cout<<"2 players remain, Now executing Cut and Choose Protocol: "<<std::endl;;
				cut_and_choose(players[0],players[1], alpha);
				std::cout<<"Player "<<0<<" share value: "<<players[0]->get_shareValue()<<"       ";
				std::cout<<"Player "<<1<<" share value: "<<players[1]->get_shareValue()<<std::endl;
				std::cout<<"Player "<<0<<" shareSize:   "<<((double)players[0]->get_shareSize()/players[0]->get_value_dist().size())<<"        ";
				std::cout<<"Player "<<1<<" shareSize    "<<(double)players[1]->get_shareSize()/players[1]->get_value_dist().size()<<std::endl;
				players.pop_back();
				players.pop_back();
				exit(1);
				
			}

			//int last_p_i = players.back();

			take_turn(players.back(),cuts.size(),players.back()->eval_share(cuts));
			players.pop_back();

			for (int i = 0; i < cuts.size(); ++i)
			{
				for(int j = 0; j < cake.size(); ++j)
				{
				
					if(cuts[i] == cake[j])
					{
						cake.erase(cake.begin(),cake.begin()+j);
					}
				}
				std::cout<<std::endl;
			}
		
			n++;*/

}