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

void read_data(string fn, int students, int exams)
{
    vector<int> sequenceDegree;
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
            if (c > 0){ s=s+1;
                cout << s << ": " << i + 1 << " " << j + 1 << " " << c << endl;}   
            adj_matrix[i * exams + j] = c;
        }
    } 

    int c=0;
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

    cout << "#################################" << endl;
    cout << "Conflict Density: " << cd << endl;

    int min=1000000;
    int max=0;
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
        sequenceDegree.push_back(c);
        if (c>max) max=c;
        if (c<min) min=c;

    }

    sort(sequenceDegree.begin(), sequenceDegree.end());
    int indexMed;
    if (sequenceDegree.size() % 2 == 0) {
        indexMed = sequenceDegree.size() / 2;
    } else {
        indexMed = (sequenceDegree.size() + 1) / 2;
    }

    double med = sequenceDegree[indexMed];

    int sum1 = 0;
    for (int i = 0; i < int(sequenceDegree.size()); i++) {
        sum1 += sequenceDegree[i];
    }
    double mean = double(sum1) / double(sequenceDegree.size());

    double sum2 = 0.0;
    double a, b;
    for (int i = 0; i < int(sequenceDegree.size()); i++) {
        a = double(sequenceDegree[i]) - mean;
        b = pow(a, 2.0);
        sum2 += b;
    }
    double S2 = sum2 / double(sequenceDegree.size());
    double S = sqrt(S2);
    double CV = (S / mean) * 100;

    cout << "Min: " << min << endl;
    cout << "Med: " << med << endl;
    cout << "Max: " << max << endl; 
    cout << "Mean: " << mean << endl;  
    cout << "CV: " << CV << " %"<< endl;

    delete[] adj_matrix;

}

int main()
{
    //read_data("../datasets/toy-e5-s6.stu", 6, 5);
    
    //read_data("../datasets/car-f-92.stu", 18419, 543);
    //read_data("../datasets/car-s-91.stu", 16925, 682);
    //read_data("../datasets/ear-f-83.stu", 1125, 190);
    //read_data("../datasets/hec-s-92.stu", 2823, 81);
    //read_data("../datasets/kfu-s-93.stu", 5349, 461);
    //read_data("../datasets/lse-f-91.stu", 2726, 381);
    //read_data("../datasets/pur-s-93.stu", 30029, 2419);
    //read_data("../datasets/rye-s-93.stu", 11483, 486);
    read_data("../datasets/sta-f-83.stu", 611, 139);
    //read_data("../datasets/tre-s-92.stu", 4360, 261);
    //read_data("../datasets/uta-s-92.stu", 21266, 622);
    //read_data("../datasets/ute-s-92.stu", 2749, 184);
    //read_data("../datasets/yor-f-83.stu", 941, 181);
    
}