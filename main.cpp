
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
	a.generateValueDist(10);
	
	Agent b;
	b.generateValueDist(10);

	std::vector<int> abc;

	abc = a.cut(.5);
	
	Protocol p;

	p.cut_and_choose(a,b);

	return 0;

};