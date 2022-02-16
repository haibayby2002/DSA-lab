#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <string>

using namespace std;
int binarySearch(int arr[], int left, int right, int x)
{
	if (left > right) {
		return -1;
	}
	int i = (left + right) / 2;
	cout << "We traverse on index: " << i << endl;
	if (arr[i] == x) {
		return i;
	}
	else if (arr[i] < x) {
		return binarySearch(arr, i + 1, right, x);
	}
	else {
		
		return binarySearch(arr, left, i - 1, x);
	}
}

int interpolationSearch(int arr[], int left, int right, int x)
{
	if (left <= right && x >= arr[left] && x <= arr[right]) {
		int i = left + ((double)(right - left) / (arr[right] - arr[left]) * (x - arr[left]));

		cout << "We traverse on index: " << i << endl;
		if (arr[i] == x) {
			return i;
		}
		else if (arr[i] < x) {
			return interpolationSearch(arr, i + 1, right, x);
		}
		else {
			return interpolationSearch(arr, left, i - 1, x);
		}
	}
	
	return -1;
}

bool findPairs(int arr[], int n, pair<int, int>& pair1, pair<int, int>& pair2)
{
	map<int, pair<int, int>> m;
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int sum = arr[i] + arr[j];
			if (m.find(sum) == m.end()) {	//Chua co
				pair<int, int> p;
				p.first = i;
				p.second = j;
				m[sum] = p;
			}
			else {
				pair1.first = arr[m[sum].first];
				pair1.second = arr[m[sum].second];

				pair2.first = arr[i];
				pair2.second = arr[j];
				
				return true;
			}
		}
	}
	return false;
}

bool checkAnswer(int arr[], int n, pair<int, int> pair1, pair<int, int> pair2) {
	return pair1.first + pair1.second == pair2.first + pair2.second;
}

//True answer
/*
int jumpSearch(int arr[], int x, int n) {
	// TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
		cout << 0 << " ";
	if (x==arr[0])
		return 0;
	int step = sqrt(n);

	int prev = 0;
	while (arr[min(step, n)] < x)
	{
		if (step>=n)
			break;
		prev = step;
		cout << step << " ";
		step += sqrt(n);
		if (prev >= n)
			return -1;
	}
	if (arr[prev]==x)
		return prev;
	else
	{
		if (step<n)
			cout << step << " ";
		if (arr[step]==x)
			return step;
	}
	while (arr[prev] < x)
	{

		prev++;
		cout << prev << " ";
		if (arr[prev] == x)
			return prev;
		if (prev == min(step-1, n))
			return -1;
	}

	if (arr[prev] == x)
		return prev;
	return -1;
}
*/

int jumpSearch(int arr[], int x, int n)
{
	// Finding block size to be jumped
	int step = sqrt(n);

	// Finding the block where element is
	// present (if it is present)
	int prev = 0;
	
	while (arr[min(step, n) - 1] <= x)
	{
		cout << prev << " ";
		prev = step;
		step += sqrt(n);
		if (prev >= n) {
			break;
		}
			
		if (arr[prev] == x) {
			cout << prev << " ";
			return prev;
		}
	}

	cout << prev << " ";
	if (step < n) {
		cout << step << " ";
	}
	

	// Doing a linear search for x in block
	// beginning with prev.
	while (arr[prev] < x)
	{

		
		prev++;
		cout << prev << " ";
		// If we reached next block or end of
		// array, element is not present.
		if (prev == min(step, n))
			return -1;
	}
	// If element is found
	if (arr[prev] == x) {
		//cout << prev << " ";

		return prev;
	}

	return -1;
}

int foldShift(long long key, int addressSize)
{
	string s = to_string(key);
	int sum = 0;
	
	int n = s.length();
	int i = 0;
	//160010
	while (i < n) {
		string temp = s.substr(i, addressSize);
		sum+= atol(temp.c_str());
		i += addressSize;
	}
	return sum;
}

/*True answer
int foldShift(long long key, int addressSize)
{
	string s = to_string(key);
	int sum = 0;

	int n = s.length();
	int i = 0;
	while (i < n) {
		string temp = s.substr(i, addressSize);
		sum+= atol(temp.c_str());
		i += addressSize;
	}
	string tmp=to_string(sum);
	if (tmp.length()>(unsigned int)addressSize)
		tmp=tmp.substr(tmp.length()-addressSize,addressSize);
	sum=atol(tmp.c_str());
	return sum;
}
*/

int rotation(long long key, int addressSize)
{
	// Rotate
	string s = to_string(key);
	s = s[s.length() - 1] + s;
	s = s.substr(0, s.length() - 1);
	key = atol(s.c_str());
	return foldShift(key, addressSize);
}

long int midSquare(long int seed)
{
	long long int n = (seed * seed);
	string s = to_string(n);
	s = s.substr(0, s.length() - 2);
	if (s.length() > 4) {
		s = s.substr(s.length() - 4, 4);
	}
	return atol(s.c_str());
}
long int moduloDivision(long int seed, long int mod)
{
	return seed % mod;
}
long int digitExtraction(long int seed, int* extractDigits, int size)
{
	string s = to_string(seed);
	int n = s.length();
	string temp = "";
	for (int i = 0; i < size; i++) {
		if (extractDigits[i] < n) {
			temp += s[extractDigits[i]];
		}
	}
	return atol(temp.c_str());
}

int main() {
	cout << rotation(6001014, 3);

	return 0;
}