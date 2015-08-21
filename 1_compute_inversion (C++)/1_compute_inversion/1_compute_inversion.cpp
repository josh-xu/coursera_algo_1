/****************************************************************************************/
// Header & Namespace & Macro

# include<iostream>
# include<fstream>

using namespace std;

# define MAX 100000

/****************************************************************************************/
// Function Declaration

void readArray(char *);
int *merge(int *, int *, int, int);
int *mergeSort(int *, int);

/****************************************************************************************/
// Global Variable

int Array[MAX];

/****************************************************************************************/
// Function Definition

void readArray(char *filename)
{
	ifstream ifile;
	ifile.open(filename, ios::in);
	if(! ifile)
	{
		cout<<"File Open Failed!"<<'\n';
		return;
	}
	else ifile.seekg(0, ios::beg);
	
	int i = 0, temp_int;
	while(true)
	{
		if(ifile>>temp_int)
		{
			Array[i] = temp_int;
			i++;
		}
		if(ifile.eof()) break;
	}

	ifile.close();
}

int *merge(int *left, int *right, int len_l, int len_r)
{
	int i = 0, j = 0;
	// the length of temp_array (len_l + len_r) is dynamic!!! must use new!!!
	int *temp_array = new int[len_l + len_r]; // create a new array, will not be automatically deleted! -> this recursion algo is not memory efficient!
	while(i + j < len_l + len_r) // when i + j = len_l + len_r to break!!!
	{
		if(i == len_l) {temp_array[i + j] = right[j]; j++;} // i = len_l - 1, and i++ to be len_l!
		else if(j == len_r) {temp_array[i + j] = left[i]; i++;} // j = len_r - 1, and j++ to be len_r!
		else
		{
			if(left[i] < right[j]) {temp_array[i + j] = left[i]; i++;}
			else {temp_array[i + j] = right[j]; j++;}
		}
	}
	return temp_array;
}

int *mergeSort(int *entire_array, int len)
{
	if(len == 1) return entire_array; //base case...

	int *left = entire_array;
	int *right = entire_array + len / 2; // int/2 -> get int! "+" be operation of pointer!!!
	// if even -> equal divide; if odd -> # left < # right
	// n = 4, n / 2 = 2 -> (0, 1; 2, 3); n = 5, n / 2 = 2 -> (0, 1; 2, 3, 4)!
	int len_l = len / 2;
	int len_r = len - len_l;

	int *left_sorted = mergeSort(left, len_l);
	int *right_sorted = mergeSort(right, len_r);

	return merge(left_sorted, right_sorted, len_l, len_r);
}

/****************************************************************************************/
// Main Function

int main()
{
	readArray("IntegerArray.txt");

	/*
	for(int i = 0; i < MAX; i += 100) cout<<i<<"  "<<Array[i]<<'\n';
	if(Array[21112] = 32601) cout<<"true"<<'\n';
	*/

	/*
	int a[6] = {1, 3, 5, 7, 9, 14};
	int b[4] = {0, 4, 6, 10};
	int *c;
	c = merge(a, b, 6, 4);
	for(int i = 0; i < 10; i++) cout<<c[i]<<" ";
	cout<<endl;
	*/

	int a[9] = {3, 2, 5, 9, 14, 0, 16, 4, -1};
	int *b;
	b = mergeSort(a, 9);
	for(int i = 0; i < 9; i++) cout<<b[i]<<" ";
	cout<<'\n';
	b = mergeSort(Array, MAX);
	for(int i = 0; i < MAX; i += 100) cout<<i<<"  "<<b[i]<<'\n';
	cout<<"99999"<<"  "<<b[99999]<<'\n';

	return 0;
}