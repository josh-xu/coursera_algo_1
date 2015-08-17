/*****Using Naive Implementaion*******/

/****************************************************************************************/
// Header & Namespace & Macro

# include<iostream>   // in & out (stream)
# include<fstream>    // file operation (stream)
# include<vector>     // dynamic array
//# include<cstring>  // deal with string array
//# include<string>   // string
//# include<map>      // =Python dictionary

using namespace std;   // studio -> C++ standard library
//# define MAX 200       // # of vertices in Graph
# define MAX 4
# define MAX_DISTANCE 1000000 // maximum distance (will bring concenience!!!)

/****************************************************************************************/
// Data Structure

// unDirected Graph
struct node
{
    int label;
    bool visited;

	// self -> next_node[5] = edge_length[5]
    vector<int> next_node;    // self -> next_node (undirected)
	vector<int> edge_length;  // length of edge from self -> next_node
};

/****************************************************************************************/
// Function Declaration

void initGraph();
void readGraph(char *);
void delete_in_Vector(int, vector<int> &);
bool is_in_Vector(int, vector<int> &);

/****************************************************************************************/
// Global Variable

node Graph[MAX];
vector<int> X;       // vertices processed so far
vector<int> V_X;     // vertices which haven't been processed yet
int A[MAX];          // computed shortest path distances

/****************************************************************************************/
// Function Definition

void initGraph()
{
	for(int i = 0; i < MAX; i++)
	{
		Graph[i].label = i + 1; // label from 1 to 200, but index from 0 to 199
		Graph[i].visited = false;
		V_X.push_back(i + 1);   //1 to 200
	}
	X.push_back(1); //using 1 (the first vertex) as the source vertex
	//V_X.erase(V_X.begin()); // delete source vertex -> begin() return a iterator -> a pointer (position)
	delete_in_Vector(1, V_X);
	A[0] = 0; //A[1] = 0!!! index will -1...
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
				//Graph[label].next_node = temp_int;
				ifile>>temp_int;
				//Graph[label].edge_length = temp_int;
				cout<<temp_int<<'\n';
				do
				{
					ifile.get(temp_char); //get() method will not skip ' ' & '\t' & '\n'...
				}while(temp_char != '\t' && temp_char != '\n');
				if(temp_char == '\n') break; // line read end -> next node
			}
			if(ifile.eof() == true) break; // if the end of file, eof() = true
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
				if(temp_char == ',') Graph[label].next_node.push_back(temp_int); // should not use ",", it's array!!! -> use ',' instead!!! (different with Python)
				if(temp_char == '\t') Graph[label].edge_length.push_back(temp_int);
				
				// do a check (test) -> whether a line is over!!!
				ifile>>temp_char;
				if(temp_char == '\t' || temp_char == '\n') break;
				else ifile.seekg(-1, ios::cur); //!!!set pointer to the previous one!!!
			}
		}
		if(ifile.eof() == true) break; // if the end of file, eof() = true
	}
	ifile.close();
}

void delete_in_Vector(int label, vector<int> &V)
{
	/*
	// using iterator is not so convenient!!!
		vector<int>::iterator iter;
		// use iterator to traverse!!!
		for(iter = V.begin(); iter != V.end(); iter++)
		{
			if(*iter == label)
			{
				iter = V.erase(iter); // !!!use erase will disable all the iterator -> should re assign!!!
				break;
			}
		}
	*/
	for(unsigned int i = 0; i < V.size(); i++)
	{
		if(V[i] == label)
		{
			V.erase(V.begin() + i ); // V.begin() is a pointer
			break; // assume no duplicate label
		}
	}
}

bool is_in_Vector(int label, vector<int> &V)
{
	/*
	// using iterator is not so convenient!!!
		vector<int>::iterator iter;
		for(iter = V.begin(); iter != V.end(); iter++)
		{
			if(*iter == label) return true;
		}
		return false;
	*/
	for(unsigned int i = 0; i < V.size(); i++)
	{
		if(V[i] == label) return true;
	}
	return false;
}

/****************************************************************************************/
// Main Function

int main()
{
	initGraph();
	readGraph("dijkstraData_test.txt");
	
	/*
	// check case for reading Graph! - v1.0
	for(int i = 0; i < MAX; i++)
	{
		cout<<Graph[i].label<<"  ";
		//size() return unsigned int...
		for(unsigned int j = 0; j < Graph[i].next_node.size(); j++) cout<<Graph[i].next_node[j]<<','<<Graph[i].edge_length[j]<<"  ";
		cout<<'\n';
	}
	*/

	/*
	// Graph[MAX] & A[MAX] -> have problem with index and label
	while(! V_X.empty())
	{
		min_length = MAX_DISTANCE; // init min
		for(iter_i = X.begin(); iter_i != X.end(); iter_i++)
		{
			index_Graph_X = *iter_i - 1; // label from 1 to 200, but index from 0 to 199
			next_node = Graph[index_Graph_X].next_node; // a vector

			for(iter_j = next_node.begin(); iter_j != next_node.end(); iter_j++)
			{
				next_node_label = 
				if(is_in_Vector(*iter_j, V_X)) // check whether in V-X
				{
					// check if minimum
					//*******************************************************
					// if use iterator, then edge_length is hard to build relationship with next_node!!!
					// have to use a third iterator then... (*_*)
					if(Graph[index_Graph_X].edge_length < min_length)
					{
						min_length = Graph[index_Graph_X].edge_length;
						min_next_node = 
					}
					//*******************************************************
				}
			}
		}
		X.push_back(min_next_node);
		delete_in_Vector(min_next_node, V_X);
	}
	*/
	
	int min_path, min_next_node, greedy_criterion;
	vector<int> next_node, edge_length;

	// Graph[MAX] & A[MAX] -> have problem with index and label
	while(! V_X.empty())
	{
		min_path = MAX_DISTANCE; // init min
		for(unsigned int i = 0; i < X.size(); i++)
		{
			next_node = Graph[i].next_node;     // a vector
			edge_length = Graph[i].edge_length; // a vector
			
			// next_node.size() = edge_length.size()
			for(unsigned int j = 0; j < next_node.size(); j++)
			{
				if(is_in_Vector(next_node[j], V_X))
				{
					// A[Graph[i].label - 1] to access A[]!
					greedy_criterion = A[Graph[i].label - 1] + edge_length[j];
					if(greedy_criterion < min_path)
					{
						min_path = greedy_criterion;
						min_next_node = next_node[j];
					}
				}
			}
		}
		A[min_next_node - 1] = min_path;
		X.push_back(min_next_node);
		delete_in_Vector(min_next_node, V_X);
	}

	cout<<A[0]<<','<<A[1]<<','<<A[2]<<','<<A[3]<<'\n';

	return 0;
}