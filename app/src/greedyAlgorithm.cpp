#include <iostream> 
#include <list> 
using namespace std; 

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *vert; // A dynamic array of adjacency lists
public: 
	// Constructor and destructor 
	Graph(int V) { this->V = V; vert = new list<int>[V*V];} 
	~Graph()	 { delete [] vert; } 

	// function to add an edge to graph 
	void addEdge(int v, int w); 

	// Prints greedy coloring of the vertices 
	void greedyColoring(); 
}; 

void Graph::addEdge(int v, int w) 
{ 
	vert[v].push_back(w); 
	vert[w].push_back(v); 
} 

void Graph::greedyColoring() {

    int coloringVertices[V];

    coloringVertices[0] = 0; // Assign the first color to first vertex 

    for (int i = 1; i < V; i++) // Initialize remaining V-1 vertices as unassigned
        coloringVertices[i] = -1; 

    bool availableColors[V]; // A temporary array to store the available colors. True
    for (int cl = 0; cl < V; cl++)
        availableColors[cl] = false;

    for (int i = 1; i < V; i++) // Assign colors to remaining V-1 vertices
    {
        list<int>::iterator j;
        for (j=vert[i].begin(); j != vert[i].end(); j++)
            if (coloringVertices[*j] != -1)
                availableColors[coloringVertices[*j]] = true;
   
        int clr; // Find the first available color
        for (clr = 0; clr < V; clr++)
            if (availableColors[clr]== false)
                break;

        coloringVertices[i] = clr; 

        for (j=vert[i].begin(); j != vert[i].end(); j++) // Reset the values back to false for the next iteration
            if (coloringVertices[*j] != -1)
                availableColors[coloringVertices[*j]] = false;
    }
    
    cout << "#################################" << endl;
    cout << "Coloring graph \n";      
    for (int i = 0; i < V; i++){
                cout << "Vertex " << i << " --->  Color "<< coloringVertices[i] <<endl;
    }
}