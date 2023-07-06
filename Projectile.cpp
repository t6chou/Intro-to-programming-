//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m, const float theta, const float d, const float t, const float b, const float w,float& destX, float& destY) 
{
	float radian = (theta*M_PI)/180;
	float horizontal_v = cos(radian)*v;
	float vertical_v = sin(radian)*v;
	float threshold_d = b+w;
	float delta_d;
	if(h>t)
	{
		delta_d = h-t;
	}
	else
	{
		delta_d = t-h;
	}	
	const float g = 9.8;
	float vf1 = sqrt(pow(vertical_v,2)+2*g*(delta_d));
	float vf2 = sqrt(pow(vertical_v,2)+2*g*(h));
	float t1 = fabs((vf1+vertical_v)/g); //projectile hits the building
	float t2 = fabs((vf2+vertical_v)/g);   //hits the ground
	float t3 = fabs(b/horizontal_v);
	//destX = horizontal_v*t;
	/* Three cases should be considered :
	1. Ball hits the ground (either after or before the building) 
	2. Ball hits the top of the building 
	3. Ball hits the building body 
	PS. t can be negative.*/
	
if (m<=0 || h<=0 || b<=0 || w<=0 || v<0 || theta<=0)
	{
		return false;
	}
	
	if (theta == 90 || v == 0)
	{
		destX = 0;
		destY = h;
		
		return true;
	}
	
	
	if (t1*horizontal_v <= threshold_d && t1*horizontal_v >= b)//hits the building
	{
		if ( theta < 90 && theta > 0)
		{
			destY = t;
			destX = horizontal_v*t1;
		}
			
		if ( theta > 90 && theta < 180)
		{
			destY = t;
			destX = -(horizontal_v*t1);
		}
		return true;
	}	
	if (t2*horizontal_v < b || t1*horizontal_v > threshold_d)//hits the ground
	{
		if ( theta < 90 && theta > 0)
		{
			destY = 0;
			destX = horizontal_v*t2;
		}
			
		if ( theta > 90 && theta < 180)
		{
			destY = 0;
			destX = -(horizontal_v*t2);
		}
		return true;
	}
	if (t1*horizontal_v < b && t2*horizontal_v > b)//hits the wall
	{
		if ( theta < 90 && theta > 0)
		{
			destY = t3*vertical_v - 0.5*g*pow(t3,2)+h;
			destX = b;
		}
			
		if ( theta > 90 && theta < 180)
		{
			destY = 0;
			destX = -(horizontal_v*t2);
		}
	
		return true;
	}
}


	
	/*if (t=0)
	{
		destY = 0;
		destX = horizontal_v*t2;
	}
	
	
	if (t<0)
	{
		
		if (t1*horizontal_v <= threshold_d && t2*horizontal_v > b)//hits the building
		{
			destY = t3*vertical_v;
			destX = horizontal_v*t1;
		}	
		if (t2*horizontal_v < b || t2*horizontal_v > threshold_d)//hits the ground
		{
			destY = 0;
			horizontal_v*t2;
		}
		if (t2*horizontal_v < threshold_d && t2*horizontal_v > b)//hits the wall
		{
			destY = t3* ;
			destX = b;	
		}
		else
		{
			return false;
		}
	*/
	
	

	   //angle cases

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....

  float h = 10;
  float v = 10;
  float m = 10;
  float theta = 45;        // Angle in degrees; will need to be converted by function
  float d = 100;
  float t = 5;
  float b = 97;
  float w = 5;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
