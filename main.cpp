
#include "RA_DISC.H"

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