#ifndef RA_H
#define RA_H

#include <vector>
#include <random>
#include <chrono>
#include <cmath>


class Agent
{
private:
	double util_coeff;
	int id; //id of 0 denotes an anonomyous agent
	double value_share;
	double share;

public:
	Agent()
	{
		std::mt19937 mt;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);
		std::uniform_real_distribution<double> intDist(1,1);
	

		double randomRealBetweenOneAndTwo = intDist(mt);
		util_coeff = randomRealBetweenOneAndTwo;

		id = 0;
	}

	void set_value_share(double d)
	{
		value_share = d;
	}

	double get_value_share()
	{
		return value_share;
	}

	void setShare(double s)
	{
		share = s;
	}

	double getShare()
	{
		return share;
	}

	double getCoeff()
	{
		return util_coeff;
	}

	void setCoeff(double c)
	{
		util_coeff = c;
	}

	void setID(int id_val)
	{
		id = id_val;
	}

	int getID()
	{
		return id;
	}


	double value(double start, double end)
	{

		double length;
		double width;

		length = end - start;

		width = 1;

		double result = 0;

		result = length;

		return result;
	};

	double cut(double val_constraint)
	{
		double x_opt = (val_constraint)/(util_coeff); // solves the agents value equation for the point where the think the resource is evenly divided
		return x_opt;
	}

};


class Protocol
{
private:

public:

	/*
		Each Protocol will accept a vector of player objects and a Resource object. 

	*/
	//void cut_and_choose(std::vector<Agent> agents, Resource X)
	void cut_and_choose(std::vector<Agent*> Agents, int i, int j)
	{
		/* the classic resource allocation protocol, will either need to implement the n = 2 case or find
		a version that is able to work with n > 2 case to make things interesting
		*/
			Agents[i]->setCoeff(1); // testing purposes
			Agents[j]->setCoeff(1); // testing purposes

			std::cout<<"Coeff(P1): "<<Agents[i]->getCoeff()<<std::endl;
			std::cout<<"Coeff(P2): "<<Agents[j]->getCoeff()<<std::endl;

			double start_pos = 0;
			double cut_pos;
			cut_pos = Agents[i]->cut(.5);

			std::cout<<"The cut was made by player one at point "<<cut_pos<<std::endl;
			std::cout<<"Player one values piece one as "<<Agents[i]->value(0,cut_pos)<<std::endl;
			std::cout<<"Player one values piece two as "<<Agents[i]->value(cut_pos, 1)<<std::endl;
			std::cout<<"Player two values piece one as "<<Agents[j]->value(0,cut_pos)<<std::endl;
			std::cout<<"Player two values piece two as "<<Agents[j]->value(cut_pos,1)<<std::endl;

			if(Agents[j]->value(0, cut_pos) >= (1/2) )
			{
				Agents[j]->setShare(cut_pos);
				Agents[j]->set_value_share(Agents[j]->value(0,cut_pos));

				Agents[i]->setShare((1 - cut_pos));
				Agents[i]->set_value_share(Agents[i]->value(cut_pos,1));
				//std::cout<<"Player two has chosen piece 1 of size "<<Agents[j]->getShare()<<", valued at "<<Agents[j]->get_value_share()<<std::endl;
				//std::cout<<"Player one is left with piece 2 of size "<<Agents[i]->getShare()<<", valued at "<<Agents[i]->get_value_share()<<std::endl;
				
				//std::cout<<"The pieces add up to equal: "<<(Agents[i]->getShare()+Agents[j]->getShare())<<std::endl;

			}

			else
			{
				Agents[i]->setShare(cut_pos);
				Agents[i]->set_value_share(Agents[i]->value(0,cut_pos));

				Agents[j]->setShare((1 - cut_pos));
				Agents[j]->set_value_share(Agents[j]->value(cut_pos,1));

				//std::cout<<"Player two has chosen piece 2 of size "<<Agents[j]->getShare()<<", valued at "<< Agents[j]->get_value_share()<<std::endl;
				//std::cout<<"Player one is left with piece 1 of size "<<Agents[i]->getShare()<<", valued at "<<Agents[i]->get_value_share()<<std::endl;

				//std::cout<<"The pieces add up to equal: "<<(Agents[i]->getShare()+Agents[j]->getShare())<<std::endl;
				
			}

		// maybe return the agents with their pieces in memory in order to evaluate welfare and who won?

	};

	

	void last_diminisher(std::vector<Agent> agents)
	{
		/*
			An extension of the classic cut and choose protocol
		*/

		//double cut_pos;
		//double num_players = 1 / agents.size();
		//agents[0].cut(num_players); // STEP 1: Player 1 cuts piece S1 such that v1(s1) = 1/n




		
	};



};

class Welfare // incorporates a set of functions meant to assess the quality of the division
{

private:

public:

};


#endif