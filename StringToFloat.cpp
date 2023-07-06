//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#include <math.h>

using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

bool stringToFloat(const char input[], float& value) {
	float result_for_normal = 0;
	float result_for_decimal = 0;
	unsigned int result_for_exponent = 0;
	unsigned int index = 0;
	char i = input[0];

	int counter = 1;
	
	bool positive = (i=='+');
	bool negative = (i=='-');
	if (positive || negative){
		index = 1;
		i = input[1];
	}	
	
	while(i != '\0'){
		unsigned int currDigitIntValue;
			
		while (i != '.' && i !='e' && i != 'E'){
			
			if (i>='0' && i<='9'){
			result_for_normal *= 10;

			}	
			
			else{
				return false;
			}
			
			currDigitIntValue = i - '0';
			result_for_normal += currDigitIntValue;
			index++;
			i = input[index];
			return true;
		}	
		
		cout<< "value is " << value <<endl;
		
		if (i == '.'){
			index++;
			i = input[index];
			
			if (positive || negative){
				return false;
			}	
			
			while ( i != 'e' && i != 'E'){				
				if(i>='0' && i<='9'){
					currDigitIntValue = i - '0';
					currDigitIntValue /= pow(10,counter);
				}		
				else{
					return false;
				}
				result_for_decimal += currDigitIntValue;
				index++;
				i = input[index];
				return true;
			}	

			
			value += result_for_decimal;		

			cout<< "value is" << value <<endl;
		}
		
		if (i == 'e' || i == 'E'){
			index ++;
			i = input[index];
			
			if (positive || negative){
				index += 1;
				i = input[index];
			}	
			
			while (i != '\0'){
				
				if(i>='0' && i<='9'){
					result_for_exponent *= 10;
				}	
				
				else{
					return false;
				}
				currDigitIntValue = i - '0';			
				result_for_exponent += currDigitIntValue;	
				index++;
				i = input[index];
				return true;
			}

			value = negative?(value*pow(10,-result_for_exponent)) : value*pow(10,result_for_exponent);		
		}
		
		else{
			return value;
		}
	}
	
	value = negative?(-value) : value;
	return true;
}


//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const argv[]){
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
