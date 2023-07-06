//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <fstream>
using namespace std;


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

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);
			  
			  
int histogram(const char filename[], int histogram[10], const int minAcceptableID, const int maxAcceptableID,int*& rejects)
{	
	if(minAcceptableID > maxAcceptableID || histogram  == NULL)
	{
		return -1;
	}
	int index = 0;
	int rejectLineNumber = 0;
	rejects = new int[100];
	const int maxLineLength = 100;
	char line[maxLineLength];
	ifstream infile;
	infile.open(filename);
	for (int i = 0; i < 10; i++)
	{
		histogram[i] =0;
	}
	
	if (!infile.is_open())
	{
		return -1;
	}
	
	bool done = false;
	int fileLineNumber = 0;
	
	while (!done)
	{
		++ fileLineNumber;
		
		if (!infile.getline(line,maxLineLength))
		{
			if(infile.eof())
			{
				done = true;
			}
			else 
			{
				return -1;
			}
		}

		int id = 0;
		int i = 0;
	
		if (!done)
		{
		
			while (line[i] != ',')
			{
				if(line[i] >= '0' || line[i]<= '9')
				{
				id = id*10 +line[i] - '0';
				}
		
				else if (line[i] != ' ' || line[i] != '\t')
				{
					return -1;
				}
				i++;
			}
	
			int grade = 0;
			int sign = 1;
			while (line[1])
			{
				if(line[i] >= '0' || line[i]<= '9')
				{
					grade = grade*10 +line[i] - '0';
				}	
				else if (line[i] = '-')
				{
					sign = -1*sign;
				}
			
				else if (line[i] != ' ' || line[i] != '\t')
				{
					return -1;
				}
			
				i++;
			}
		
			if (id > maxAcceptableID || id < minAcceptableID || grade > 100 || grade < 0)
			{
				rejects[index] = fileLineNumber;
				index++;
				rejectLineNumber++;
			}
			
			else if(grade = 100)
			{
				histogram[9] += 1;
			}
			else 
			{
				histogram[grade/10] += 1;	
			}
		}
	}
	
	return rejectLineNumber;
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int  buckets[numBuckets];
  int* rejectedRecords;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      else
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
	cout << " " << rejectedRecords[i];
      cout << endl;
      delete[] rejectedRecords;
    }
  }

  return 0;
}

#endif
