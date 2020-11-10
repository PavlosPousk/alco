#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

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

void read_data(string fn, int students, int exams)
{
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
            cout << "Student " << student_id << " is enrolled in exam " << exam_id << endl;
        }
    }
    fs.close();

    cout << "#################################" << endl;

    for (int i = 1; i <= exams; i++)
    {
        cout << "Exam " << i << " Enrolled students: ";
        for(int student_id: exam_students[i]){
            cout << student_id << " ";
        }
        cout << endl;
    }

    cout << "#################################" << endl;

    int AdjMatrix[exams][exams] ;
    for (int i =1; i<exams; i++){
       int count = 0; 
        for (int j=1; j<exams; j++){
            if ( exam_students[i]==exam_students[j]) {count++;}
            AdjMatrix[i][j] = count;
        }
    }

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

    int c = 0;
    for (int i = 0; i < exams; i++)
    {
        for (int j = 0; j < exams; j++)
        {
            if (adj_matrix[i * exams + j] > 0)
            {
                c++;
            }
        }
    }

    double cd = double(c) / double(exams * exams);
    cout << "Conflict Density: " << cd << endl;

    delete[] adj_matrix;
}

int main()
{
    //read_data("../datasets/car-f-92.stu", 18419, 543);
    read_data("../datasets/toy-e5-s6.stu", 6, 5);
}