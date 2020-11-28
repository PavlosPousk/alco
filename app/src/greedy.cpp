#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;
 
// Data structure to store graph edges
struct Edge {
    int src, dest;
};
 
class Graph
{
public:
    // An array of vectors to represent adjacency list
    vector<vector<int>> adjList;
 
    // Constructor
    Graph(vector<Edge> const &edges, int N)
    {
        // resize the vector to N elements of type vector<int>
        adjList.resize(N);
 
        // add edges to the undirected graph
        for (Edge edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
 
            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }
};
 
// Add more colors for graphs with many more vertices
string color[] =
{
    "", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK",
    "BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"
};
 
// Function to assign colors to vertices of graph
void colorGraph(const Graph &graph, int N)
{
    // stores color assigned to each vertex
    unordered_map<int, int> result;
 
    // assign color to vertex one by one
    for (int u = 0; u < N; u++)
    {
        // set to store color of adjacent vertices of u
        set<int> assigned;
 
        // check colors of adjacent vertices of u and store in set
        for (int i : graph.adjList[u]) {
            if (result[i]) {
                assigned.insert(result[i]);
            }
        }
 
        // check for first free color
        int color = 1;
        for (auto &c: assigned ) {
            if (color != c) {
                break;
            }
            color++;
        }
 
        // assigns vertex u the first available color
        result[u] = color;
    }
 
    for (int v = 0; v < N; v++) {
        cout << "Color assigned to vertex " << v << " is "
            << color[result[v]] << '\n';
    }
}
 
// Greedy coloring of graph
int main()
{
    // vector of graph edges as per above diagram
    vector<Edge> edges = {
        {0, 1}, {0, 4}, {0, 5}, {4, 5}, {1, 4}, {1, 3}, {2, 3}, {2, 4}
    };
 
    // Number of nodes in the graph
    int N = 6;
 
    // create a graph from edges
    Graph graph(edges, N);
 
    // color graph using greedy algorithm
    colorGraph(graph, N);
 
    return 0;
}