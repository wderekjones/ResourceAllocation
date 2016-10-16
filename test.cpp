#include<iostream>
#include<random>


using namespace std;


int main()
{
	for(int i = 0; i < 10; i++)
	{

		int r = rand() % 2;
		cout<<r<<endl;
	}


	return 0;
}
