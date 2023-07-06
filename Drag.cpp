//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <math.h>


//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);
			  
float dx(const float h, const float m, const float theta, const float d, const float step, const float k, const float t, const float b, const float w, const float v);

float BisectionHelper(float left, float right, const float precision, const float h, const float m, const float theta, const float d, const float step, const float k, const float t, const float b, const float w);	
//////////////////////////////////////////////////////////////
//
// Your code here ...
//  


float dx(const float h, const float m, const float theta, const float d, const float step, const float k, const float t, const float b, const float w, float v){ 
//return dx given v
	float radian = (theta*M_PI)/180;
	const float g = 9.8;
	float x = 0; 
	float y = h;
	float force_gravity = m*g;
	float vx;
	float vy;
	float ay;
	float ax;
	float force_drag_x;
	float force_drag_y;
	if (h < t){
		while (y < t && vy > 0){
			vx = v*cos(radian);
			vy = v*sin(radian);
			force_drag_x = -k*vx*v;
			force_drag_y = -k*vy*v;
			ay = ((-1*force_gravity + force_drag_y))/m;
			ax = force_drag_x/m;
			vy += ay*step;
			vx += ax*step;
			y += vy*step;
			x += vx*step; 
			v = sqrt(pow(vx,2)+pow(vy,2));
		}	
		if (vy < 0){
			return d-1;
		}	
	}
	while (y > t){
		vx = v*cos(radian);
		vy = v*sin(radian);
		force_drag_x = -k*vx*v;
		force_drag_y = -k*vy*v;
		force_gravity = m*g;
		ay = ((-1*force_gravity + force_drag_y))/m;
		ax = force_drag_x/m;
		vy += ay*step;
		vx += ax*step;
		y += vy*step;
		x += vx*step; 
		v = sqrt(pow(vx,2)+pow(vy,2));
	//cout << " dx equals to " << x << endl;
	}	
	return x;
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, const float d, const float step, const float k, const float t, const float b, const float w, float& v){		
	const float g = 9.8;
	float radian = (theta*M_PI)/180;
	float dy = t-h;	
	float theo_v = fabs((d/cos(radian))*(sqrt(g/(2*tan(radian)*d-2*dy))));	
	float v_min = theo_v/5; 
	float v_max = theo_v*5;
	if (v_min <= 0){
		return false;
	}
	if(h<=0 || m<=0 || d <=0 || step <=0 || k<0 || b<=0 || w<=0){
		return false;
	}
	else if(theta <= -90 || theta >= 180){
		return false;
	}	
	float left = v_min;
	float right = v_max;
	float mid = (left+right)/2;
	float precision = 0.01;
	if(left >= right){
		return false;
	}
	
	if (dx(h, m, theta, d, step, k, t, b, w, mid)>d){
		while(dx(h, m, theta, d, step, k, t, b, w, mid)>d  || mid >= precision){
			right = mid;
			mid = (left+right)/2;
		}
	}
	else if (dx(h, m, theta, d, step, k, t, b, w, mid)<d){
		while(dx(h, m, theta, d, step, k, t, b, w, mid)<d || mid >= precision){
			left = mid;
			mid = (left+right)/2;
		}
	}
	else{
		v = mid;
	}
	return true;
}

#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 30;
  float w = 30;
  float m = 1;
  float step = 0.01;
  float k = 0.5;
  float theta = 45; // Angle in degrees;
  float v = 25;	

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }
    
  return 0;
}
#endif
