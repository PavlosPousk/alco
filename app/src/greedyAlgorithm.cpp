#include <iostream> 
#include <list> 
using namespace std; 

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *vert; // A dynamic array of adjacency lists
    int *adj_matrix= new int[V * V];; 
public: 
	// Constructor and destructor 
	Graph(int V,int *adj_matrix1) { this->V = V; vert = new list<int>[V]; adj_matrix=adj_matrix1;} 
	~Graph()	 { delete [] vert; } 

	// function to add an edge to graph 
	void addEdge(int v, int w); 

	// Prints greedy coloring of the vertices 
	void greedyColoring(); 
}; 

void Graph::addEdge(int v, int w) 
{ 
	vert[v].push_back(w); 
	vert[w].push_back(v); // Note: the graph is undirected 
} 

void Graph::greedyColoring() {
    
    int coloringVertices[V];

    coloringVertices[0] = 0;

    for (int i = 1; i < V; i++)
        coloringVertices[i] = -1; 

    bool availableColors[V];
    for (int cl = 0; cl < V; cl++)
        availableColors[cl] = false;

    for (int i = 1; i < V; i++)
    {
        list<int>::iterator j;
        for (j=vert[i].begin(); j != vert[i].end(); j++)
            if (coloringVertices[*j] != -1)
                availableColors[coloringVertices[*j]] = true;
   
        int clr;
        for (clr = 0; clr < V; clr++)
            if (availableColors[clr])
                break;

        coloringVertices[i] = clr; 

        for (j=vert[i].begin(); j != vert[i].end(); j++)
            if (coloringVertices[*j] != -1)
                availableColors[coloringVertices[*j]] = false;
    }
    
    cout << "#################################" << endl;
    cout << "Coloring graph \n";      
    for (int i = 0; i < V; i++){
                cout << "Vertex " << i << " --->  Color "<< coloringVertices[i] <<endl;
    }
}