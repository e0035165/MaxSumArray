//
//  main.cpp
//  PlaneProblem
//
//  Created by Sart Way on 18/2/23.
//

#include <iostream>
#include <string>
#include<algorithm>
#include<functional>
#include<fstream>
#include<vector>
#include <set>
#include <queue>
#include<map>
#include <chrono>
#include <thread>
#include "NaiveSolution.hpp"

using namespace std;
string ltrim(const string &str);
string rtrim(const string &str);
vector<string> split(const string &str);
long maximumSum(vector<long>a, long m);
static long maxans = 0;
static long mod = 0;


struct Node
{
    long data;
    Node* left = NULL;
    Node* right = NULL;
    vector<Node*>copies;
    int height = 0;
    int index = -1;
    Node(long data)
    {
        this->data = data;
        this->height = 1;
    }
    
    Node(long data, int index)
    {
        this->data = data;
        this->height = 1;
        this->index = index;
    }
    

};

Node* MAX = new Node(LONG_MAX);
Node* MIN = new Node(LONG_MIN);

void printNodal(Node* curr, vector<Node*>&vect);
bool sameNodeCheck(Node* newone, Node* currentOne, Node* smallerOne, Node* biggerOne);
void setHeight(Node* curr);
int getNodeBalanceFactor(Node* left, Node* right);

bool sameNodeCheck(Node* newone, Node* currentOne, Node* smallerOne, Node* biggerOne)
{
    if(newone->data == currentOne->data)
    {
        long temp = maxans;
        int changed_index = newone->index;
        currentOne->copies.push_back(newone);
        return true;
    } else {
        return false;
    }
}

void printNodal(Node* curr, vector<Node*>&vect)
{
    if (curr == nullptr)
    {
        return;
    }
    printNodal(curr->left,vect);

    vect.push_back(curr);

    printNodal(curr->right,vect);

    return;
}

void setHeight(Node* curr)
{
    if (curr->right != NULL && curr->left != NULL)
    {
        curr->height = 1 + max(curr->right->height, curr->left->height);
    }
    else if (curr->right == NULL && curr->left != NULL)
    {
        curr->height = 1 + curr->left->height;
    }
    else if (curr->right != NULL && curr->left == NULL)
    {
        curr->height = 1 + curr->right->height;
    }
    else {
        curr->height = 0;
    }
}

int getNodeBalanceFactor(Node* left, Node* right)
{
    int lefter = left != NULL ? left->height : 0;
    int righter = right != NULL ? right->height : 0;
    return lefter - righter;
}


Node* insertNode(Node* newone, Node* currentOne, Node* smallerOne, Node* biggerOne)
{
    if(currentOne == NULL)
    {

        return newone;
    }
    
    if(!sameNodeCheck(newone, currentOne, smallerOne, biggerOne))
    {
        if(newone->data < currentOne->data)
        {
            currentOne->left = insertNode(newone, currentOne->left, smallerOne, currentOne);
        } else {
            currentOne->right = insertNode(newone, currentOne->right, currentOne, biggerOne);
        }
    } else {
        
    }
    
    return currentOne;
}


Node* getMaxfromNode(Node* temp)
{
    while(temp->right != nullptr)
    {
        temp = temp->right;
    }
    
    return temp;
}


Node* getMinfromNode(Node* temo)
{
    while(temo->left != nullptr)
    {
        temo = temo->left;
    }
    return temo;
}


int main(int argc, const char * argv[]) {
    
    fstream input("File.txt", ios::in | ios::out);

    string q_temp;
    getline(input, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));
    cout << q << endl;
    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(input, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        long m = stol(first_multiple_input[1]);

        string a_temp_temp;
        getline(input, a_temp_temp);

        vector<string> a_temp = split(rtrim(a_temp_temp));

        vector<long> a(n);

        for (int i = 0; i < n; i++) {
            long a_item = stol(a_temp[i]);

            a[i] = a_item;
        }
        mod = m;
        long result = maximumSum(a, m);
        cout << result << endl;
        maxans = 0;
    }

    input.close();

    return 0;
}




long maximumSum(vector<long> a, long m) {
    vector<long>sum_forward((int)a.size());
    sum_forward[0] = a[0]%m;
    
    int i = 0;
    while(++i<(int)a.size())
    {
        sum_forward[i] = ((sum_forward[i-1]%m) + (a[i]%m))%m;
    }
    
    NaiveSolution* soln = new NaiveSolution();
    return soln->getLargestModSequence(sum_forward, m);
//    for(int i=0;i<(int)a.size();++i)
//    {
//        cout << sum_forward[i] << " ";
//    }
//    cout << endl;
//    //maxans = 0;
//    Node* start = new Node(sum_forward[0],0);
//    Node* max = new Node(LONG_MAX);
//    Node* min = new Node(LONG_MIN);
//    for(int i=0;i<a.size();++i)
//    {
//
//        Node* temp = new Node(sum_forward[i],i);
//        start = insertNode(temp, start, min, max);
//
//    }
//    vector<Node*>nextone;
//    printNodal(start, nextone);
//
//    for(int i=0;i<nextone.size()-1;++i)
//    {
//        if(nextone[i+1]->index > nextone[i]->index)
//        {
//            long lte = m - (nextone[i+1]->data - nextone[i]->data);
//            if(lte > maxans)
//            {
//                cout << " Change in maxans " << nextone[i+1]->index << " value " << nextone[i]->index << " " << nextone[i+1]->data << " " << nextone[i]->data << endl;
//                //lte << endl;
//                maxans = lte;
//            }
//        }
//    }
    //cout << endl;
//    
//
//
//
//    return maxans;
}


string ltrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
