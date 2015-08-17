/****************************************************************************************/
// Header & Namespace & Macro

# include<iostream>   // in & out (stream)
# include<fstream>    // file operation (stream)
# include<vector>     // dynamic array
//# include<cstring>  // deal with string array
//# include<string>   // string
//# include<map>      // =Python dictionary

using namespace std;  // studio -> C++ standard library
# define MAX 200      // # of vertices in Graph

/****************************************************************************************/
// Data Structure

// unDirected Graph
struct vertice
{
    int label;
    bool visited;

	// self -> next_vertice[5] = edge_length[5]
    vector<int> next_vertice;   // self -> next_vertice
	vector<int> edge_length;    // length of edge from self -> next_vertice
};

/****************************************************************************************/
// Function Declaration

void initGraph();
void readGraph(char *);

/****************************************************************************************/
// Global Variable

vertice Graph[MAX];

/****************************************************************************************/
// Function Definition

void initGraph()
{
	for(int i = 0; i < MAX; i++)
	{
		Graph[i].label = i + 1; // label from 1 to 200, but index from 0 to 199
		Graph[i].visited = false;
	}
}

void readGraph(char *filename) // must use *char, string class cannot be used...?!
{
	ifstream ifile; // input file object = ifile
	ifile.open(filename, ios::in); // open input file
	if(! ifile)
	{
		cout<<"File Open Failed!"<<'\n';  
        return;
	}
	else ifile.seekg(0, ios::beg); //set pointer to beginning of file
	ifile.unsetf(ios::skipws); // do not skip any ' ' & '\t' & '\n'
	// direct load int -> should skip ' ' & '\t' & '\n'!!!

	int temp_int, label;
	char temp_char;
	while(true)
	{
		/* 
		// hard to deal with different line... -> use another method instead!!!
			// can automatically laod an integer, separated by ' ' or '\t' -> reason listed below
			// skip any non-int element, such as char(' ' & '\t' & '\n')
			// cannot read int with ','???!!!
			ifile>>label; // the 1st -> self_label
			cout<<label<<'\n';
			while(true)
			{
				ifile>>temp_int>>temp_char; // temp_char will be ','
				cout<<temp_int<<'\t';
				cout<<temp_char<<'\t';
				//Graph[label].next_vertice = temp_int;
				ifile>>temp_int;
				//Graph[label].edge_length = temp_int;
				cout<<temp_int<<'\n';
				do
				{
					ifile.get(temp_char); //get() method will not skip ' ' & '\t' & '\n'...
				}while(temp_char != '\t' && temp_char != '\n');
				if(temp_char == '\n') break; // line read end -> next vertice
			}
			if(ifile.eof() == true) break; // if the end of file, ifile.eof() = true
		*/
		if(ifile>>label>>temp_char) // if exist sth to read to temp_int & temp_char (prevent end of file to run extra loop :-)~)
		{
			// temp_char will be '\t'; label will be the 1st i.e. -> self_label
			//cout<<"***"<<label<<'\n';
			label--; // label from 1 to 200, but index from 0 to 199
			while(true) // if exist sth to read to temp_int & temp_char
			{
				ifile>>temp_int>>temp_char; // temp_char will be ',' or '\t'
				//cout<<temp_int<<' ';
				//cout<<temp_char<<'.'<<'\n';
				if(temp_char == ',') Graph[label].next_vertice.push_back(temp_int); // should not use ",", it's array!!! -> use ',' instead!!! (different with Python)
				if(temp_char == '\t') Graph[label].edge_length.push_back(temp_int);
				
				// do a check (test) -> whether a line is over!!!
				ifile>>temp_char;
				if(temp_char == '\t' || temp_char == '\n') break;
				else ifile.seekg(-1, ios::cur); //!!!set pointer to the previous one!!!
			}
		}
		if(ifile.eof() == true) break; // if the end of file, ifile.eof() = true
	}
	ifile.close();
}

/****************************************************************************************/
// Main

int main()
{
	initGraph();
	readGraph("dijkstraData.txt");
	
	for(int i = 0; i < MAX; i++)
	{
		cout<<Graph[i].label<<"  ";
		for(unsigned int j = 0; j < Graph[i].next_vertice.size(); j++) cout<<Graph[i].next_vertice[j]<<','<<Graph[i].edge_length[j]<<"  ";
		cout<<'\n';
	}

	return 0;
}