#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <sys/time.h>

using namespace std;
void printArray(int *n, int len)
{
	int i;
	for(i = 0; i < len-1; i++)
		printf("%d ",n[i]);
	printf("%d\n",n[i]);
}

void printVector(vector<int> v)
{
	int i;
	for(i = 0; i < v.size()-1; i++)
		printf("%d ",v[i]);
	printf("%d\n",v[i]);
}


vector<int> insertionSort(vector<int> n)
{
	int i;
	int j;
	int len = n.size();
	for(i = 1; i<len; i++)
	{
		int k = 0;
		int value = n[i];
		for(j = i; j >= 1; j--)
		{
			if(n[j]<n[j-1])
			{
				std::swap(n[j],n[j-1]);
			}
			else	
			{	
				break;
			}
		}
	}
	return n;
}

vector<int> concat(vector<int> v1, int pivot, vector<int> v2)
{
	v1.push_back(pivot);
	v1.insert(v1.end(), v2.begin(), v2.end());
	return v1;
}

vector<int> quickSort(vector<int> v)
{
	if(v.size() == 1 || v.size() == 0)
	{
		return v;
	}
	srand(time(NULL));
	int pivotPoint = rand() % v.size();
	int pivotVal = v[pivotPoint];
	int i = 0;
	vector<int> less;
	vector<int> greater;
	for(i = 0; i < v.size(); i++)
	{
		if(i == pivotPoint)
			continue;

		if(v[i] <= pivotVal)
		{
			less.push_back(v[i]);
		}
		else if(v[i] > pivotVal)
		{
			greater.push_back(v[i]);
		}	
	}
	
	return concat(quickSort(less), pivotVal,quickSort(greater));
}

vector<int> merge(vector<int> l, vector<int> r)
{
	vector<int> out;
	while(l.size() > 0 || r.size() > 0)
	{
		if(l.size() > 0 && r.size() > 0)
		{
			if(l[0] < r[0])
			{
				out.push_back(l[0]);
				l.erase(l.begin());
			}
			else
			{
				out.push_back(r[0]);
				r.erase(r.begin());
			}

		}
		else if(l.size() > 0)
		{
			out.insert(out.end(),l.begin(),l.end());
			l.erase(l.begin(),l.end());
		}
		else if(r.size()>0)
		{
			out.insert(out.end(),r.begin(),r.end());
			r.erase(r.begin(),r.end());
		}
	
	}
	return out;
}
vector<int> mergeSort(vector<int> v)
{
	if(v.size() == 0 || v.size() == 1)
		return v;

	vector<int> left;
	vector<int> right;
	int i = 0;
	int middle = v.size()/2;
	for(i = 0; i <v.size(); i++)
	{
		if(i < middle)
		{
			left.push_back(v[i]);
		}
		else
			right.push_back(v[i]);
	}
	left = mergeSort(left);
	right = mergeSort(right);

	return merge(left,right);

}
int main(int argc, char *argv[])
{
	vector<int> v;
	if(argc != 2)
		return 0;
	int testSize = (int)atoi(argv[1]);
	printf("Test Size: %d\n",testSize);
	int z;
	for(z = 0; z< testSize; z++)
	{
		v.push_back(rand() % testSize);
	}

	int arraySize = v.size();
	int numArray1[arraySize];
	int numArray2[arraySize];
	int numArray3[arraySize];
	int j;
	float timingNumber[3];
	struct timeval start, end;
	long secs, usecs;
	//Insertion
	gettimeofday(&start, NULL);
	vector<int> sorted0 = insertionSort(v);
	gettimeofday(&end, NULL);
        secs  = end.tv_sec  - start.tv_sec;
        usecs = end.tv_usec - start.tv_usec;
	timingNumber[0] = ((secs)*1000 + usecs/1000.0);
	printf("Insertion Sort Time:%f\n",timingNumber[0]);
	gettimeofday(&start, NULL);
	vector<int> sorted1 = mergeSort(v);
	gettimeofday(&end, NULL);
	secs = end.tv_sec - start.tv_sec;
	usecs = end.tv_usec - start.tv_usec;
	timingNumber[1] = ((secs)*1000 + usecs/1000.0);

	printf("Merge Sort Time:%f\n",timingNumber[1]);
	
	gettimeofday(&start, NULL);	
	vector<int> sorted2 = quickSort(v);
	gettimeofday(&end, NULL);
        secs = end.tv_sec - start.tv_sec;
        usecs = end.tv_usec - start.tv_usec;
        timingNumber[2] = ((secs)*1000 + usecs/1000.0);

	printf("Quick Sort Time:%f\n",timingNumber[2]);

	return 0;
}

