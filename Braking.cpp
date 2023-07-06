#include <stdlib.h> 
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[])
{   
	
    int v;
	int x;
	int a:
	int t;
	v = atoi(argv[1]);
	x = atoi(argv[2]); 
	a = -(v*v)/(x*2);
	t = -v/a;
	
	cout<<"Initial car velocity: "<< x <<"m/s"<<endl;
	cout<<"Distance to obstacle: "<< v <<"m"<<endl;
    cout<<"Minimum deceleration: "<< a <<"m/s/s"<<endl;
	cout<<"Maxiimum stopping time: "<< t <<"s"<<endl;
	
	
	
    return 0;
}

