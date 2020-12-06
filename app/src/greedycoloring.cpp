#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;

int count_common_elements(set<int> s1, set<int> s2)
{
    int c = 0;
    for (int x : s1)
    {
        for (int y : s2)
        {
            if (x == y)
            {
                c++;
                break;
            }
        }
    }
    return c;
}

class Vertex {

    private:
        int vertex;
        int degree;

    public:
        Vertex();

        Vertex(int vertex, int degree){
            setVertex(vertex);
            setDegree(degree);
        }

        bool operator < (const Vertex& v){
            return getDegree() < v.degree;
        }

        void setVertex(int vertex){
            vertex = vertex;
        }

        int getVertex(){
            return vertex;
        }

        void setDegree(int degree){
            degree = degree;
        }

        int getDegree(){
           return degree; 
        }
};

void gColoring(string fn,int student, int exams){ 
    vector<Vertex> vertices;
    vector<set<int>> exam_students(exams + 1);
    fstream fs(fn);
    if (!fs.is_open())
    {
        cerr << "Could not open file " << fn << std::endl;
        exit(-1);
    }
    int student_id = 0;
    string line;
    while (getline(fs, line))
    {
        if (line.empty())
            continue;
        student_id++;
        istringstream iss(line);
        int exam_id;
        while (iss >> exam_id)
        {
            exam_students[exam_id].insert(student_id);
        }
    }
    fs.close();
    int AdjMatrix[exams][exams] ;
    for (int i =1; i<exams; i++){
       int count = 0; 
        for (int j=1; j<exams; j++){
            if ( exam_students[i]==exam_students[j]) {count++;}
            AdjMatrix[i][j] = count;
        }
    }
    int s=0;
    cout << "Adjacency Matrix" << endl;
    int *adj_matrix = new int[exams * exams];
    for (int i = 0; i < exams; i++)
    {
        for (int j = 0; j < exams; j++)
        {
            if (i == j){
                adj_matrix[i * exams + j] = 0; // adj_matrix[i][j]
                continue;
            }
            int c = count_common_elements(exam_students[i + 1], exam_students[j + 1]);
            if (c > 0) 
                cout << i + 1 << " " << j + 1 << " " << c << endl;  
            adj_matrix[i * exams + j] = c;
        }
    } 

    for (int i = 0; i < exams; i++)
    {
        int c = 0;
        for (int j = 0; j < exams; j++)
        {
            if (adj_matrix[i * exams + j] > 0)
            {
                c++;
            }
        }
        Vertex v(i, c);
        vertices.push_back(v);
    }

    sort(vertices.rbegin(), vertices.rend());
    int colorOfVertex[exams];

    colorOfVertex[vertices[0].getVertex()] = 0;

    for (int u = 1; u < exams; u++)
        colorOfVertex[vertices[u].getVertex()] = -1; 

    bool availableColors[exams];
    for (int cr = 0; cr < exams; cr++)
        availableColors[cr] = true;

    
    for (int u = 1; u < exams; u++)
    {
        for (int i = 0; i < exams; i++) {
            if (adj_matrix[vertices[u].getVertex() * exams + i] <= 0)
                continue;

            if (colorOfVertex[i] != -1)
                availableColors[colorOfVertex[i]] = false;
        }
       
        int cr;
        for (cr = 0; cr < exams; cr++)
            if (availableColors[cr])
                break;

        colorOfVertex[vertices[u].getVertex()] = cr; 
        
        for (int i = 0; i < exams; i++) {
            if (adj_matrix[vertices[u].getVertex() * exams + i] <= 0)
                continue;

            if (colorOfVertex[i] != -1)
                availableColors[colorOfVertex[i]] = true;
        }
    }

    for (int u = 0; u < exams; u++)
        cout << "Vertex " << u << " --->  Color "<< colorOfVertex[u] << endl;
}
int main()
{
    //gColoring("../datasets/toy-e5-s6.stu", 6, 5);
    
    //gColoring("../datasets/car-f-92.stu", 18419, 543);
    //gColoring("../datasets/car-s-91.stu", 16925, 682);
    //gColoring("../datasets/ear-f-83.stu", 1125, 190);
    //gColoring("../datasets/hec-s-92.stu", 2823, 81);
    //gColoring("../datasets/kfu-s-93.stu", 5349, 461);
    //gColoring("../datasets/lse-f-91.stu", 2726, 381);
    //gColoring("../datasets/pur-s-93.stu", 30029, 2419);
    //gColoring("../datasets/rye-s-93.stu", 11483, 486);
    gColoring("../datasets/sta-f-83.stu", 611, 139);
    //read_data("../datasets/tre-s-92.stu", 4360, 261);
    //read_data("../datasets/uta-s-92.stu", 21266, 622);
    //read_data("../datasets/ute-s-92.stu", 2749, 184);
    //read_data("../datasets/yor-f-83.stu", 941, 181);
}