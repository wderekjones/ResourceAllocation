
#include "RA_DISC.H"


template <typename T>
std::vector<T> remove_duplicate(std::vector<T> vec)
{
	std::sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	return vec;
}


int main()
{
	Agent a;

	a.generateValueDist(6);
	a.dumpValueDist();

	std::vector<double> abc;

	std::vector<int> pI;


	abc = a.cut(.5);

	pI = a.identify_piece(abc);

	pI = remove_duplicate(pI);

	for(int i =0; i< pI.size(); i++)
	{
		std::cout<<pI[i]<<std::endl;
	}

	std::cout << "solution size: " << abc.size() <<" " << pI.size()<< std::endl;

	double s = 0;


	for (int i = 0; i< abc.size(); i++)
	{
		std::cout << "The agent chooses piece " << " of value: " << abc[i] <<" "<<std::endl;
		s += abc[i];
	}
	std::cout << "sum of the value is: " << s << std::endl;

	abc.clear();

	std::vector<double> bc;
	bc = a.get_value_dist();

	/*for(int i =0; i < abc.size(); i++)
	{
		std::cout<<abc[i]<<std::endl;
	}*/

	/*
		Need to figure out which piece is which in order to identify and  remove those pieces from the resource

	*/

	return 0;

};