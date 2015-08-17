/*****Using Naive Implementaion*******/

/****************************************************************************************/
// Header & Namespace & Macro

# include<iostream>   // in & out (stream)
# include<fstream>    // file operation (stream)
# include<vector>     // dynamic array

using namespace std;   // studio -> C++ standard library
# define MAX 200       // # of vertices in Graph
//# define MAX 5
# define MAX_DISTANCE 1000000 // maximum distance (will bring concenience!!!)

/****************************************************************************************/
// Data Structure

// unDirected Graph
struct node
{
    int label;
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
		V_X.push_back(i + 1);   //1 to 200
	}
	X.push_back(1); //using 1 (the first vertex) as the source vertex
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

	int temp_int, label, index;
	char temp_char;
	while(true)
	{
		if(ifile>>label>>temp_char) // if exist sth to read to temp_int & temp_char (prevent end of file to run extra loop :-)~)
		{
			// temp_char will be '\t'; label will be the 1st i.e. -> self_label
			index = label - 1; // label from 1 to 200, but index from 0 to 199
			while(true) // if exist sth to read to temp_int & temp_char
			{
				ifile>>temp_int>>temp_char; // temp_char will be ',' or '\t'
				if(temp_char == ',') Graph[index].next_node.push_back(temp_int); // should not use ","! it's array!!! -> use ',' instead!!! (different with Python)
				if(temp_char == '\t') Graph[index].edge_length.push_back(temp_int);
				
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
	readGraph("dijkstraData.txt");
	
	int min_path_length, min_next_node, greedy_criterion;
	vector<int> next_node, edge_length;

	// Graph[MAX] & A[MAX] -> have problem with index and label
	while(! V_X.empty())
	{
		min_path_length = MAX_DISTANCE; // init min
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
					if(greedy_criterion < min_path_length)
					{
						min_path_length = greedy_criterion;
						min_next_node = next_node[j];
					}
				}
			}
		}
		A[min_next_node - 1] = min_path_length;
		X.push_back(min_next_node);
		delete_in_Vector(min_next_node, V_X);
	}

	cout<<A[6]<<','<<A[36]<<','<<A[58]<<','<<A[81]<<','<<A[98]<<','<<A[114]<<','<<A[132]<<','<<A[164]<<','<<A[187]<<','<<A[196]<<'\n';
	//cout<<A[0]<<','<<A[1]<<','<<A[2]<<','<<A[3]<<','<<A[4]<<'\n';

	return 0;
}