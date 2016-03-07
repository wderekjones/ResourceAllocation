
#include "RA_DISC.H"

int main()
{
	Agent a;
	a.generateValueDist(10);
	
	Agent b;
	b.generateValueDist(10);
	
	Protocol p;

	p.cut_and_choose(a,b);

	return 0;

};
