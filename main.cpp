
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
	//a.dumpValueDist();

	std::vector<int> abc;

	std::vector<int> pI;


	abc = a.cut(.5);



	//for(int i = 0 ; i <abc.size(); i++)
	//{
	//	std::cout<<abc[i]<<" ";
	//}
	//std::cout<<std::endl;

	//pI = a.identify_piece(abc);

	//pI = remove_duplicate(pI);

	
	double s = 0;
	
	std::vector<double> v = a.get_value_dist();

	/*for (int i = 0; i< abc.size(); i++)
	{
		std::cout << "The agent chooses piece " << abc[i] << " of value: " << v[abc[i]] <<" "<<std::endl;
		s += v[abc[i]];
	}
	std::cout<<"sum(value): "<<s<<std::endl;
	*/
	Protocol p;

	Agent b;
	b.generateValueDist(6);
	//b.dumpValueDist();

	p.cut_and_choose(a,b);

	return 0;

};