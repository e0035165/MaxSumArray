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

using namespace std;
string ltrim(const string &str);
string rtrim(const string &str);
vector<string> split(const string &str);
long maximumSum(vector<long>a, long m);



struct Node
{
    long data;
    Node* left = NULL;
    Node* right = NULL;
    vector<Node*>copies;
    int height = 0;
    Node(long data)
    {
        this->data = data;
        this->height = 1;
    }
    

};

void printNodal(Node* curr);
bool sameNodeCheck(Node* newone, Node* currentOne);
void setHeight(Node* curr);
int getNodeBalanceFactor(Node* left, Node* right);

bool sameNodeCheck(Node* newone, Node* currentOne)
{
    if(newone->data == currentOne->data)
    {
        currentOne->copies.push_back(newone);
        return true;
    } else {
        return false;
    }
}

void printNodal(Node* curr)
{
    if (curr == nullptr)
    {
        return;
    }
    printNodal(curr->left);

    cout << curr->data << " ";

    printNodal(curr->right);

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


Node* insertNode(Node* newone, Node* currentOne)
{
    if(currentOne == NULL)
    {
        return newone;
    }
    
    if(!sameNodeCheck(newone, currentOne))
    {
        if(newone->data < currentOne->data)
        {
            //cout << "left " << currentOne->data << endl;
            currentOne->left = insertNode(newone, currentOne->left);
        } else {
            //cout << "right " << currentOne->data << endl;
            currentOne->right = insertNode(newone, currentOne->right);
        }
    } else {
        
    }
    
    return currentOne;
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

        long result = maximumSum(a, m);

        //cout << result << "\n";
    }

    input.close();

    return 0;
}




long maximumSum(vector<long> a, long m) {
    vector<long>sum((int)a.size());
    sum[0] = a[0];
    int itr = 1;
    for(auto x=a.begin()+1;x!=a.end();++x)
    {
        sum[itr] = (*x) + sum[itr-1];
        sum[itr] = (sum[itr]%m);
        ++itr;
    }
    long max = LONG_MIN;
    long min = LONG_MAX;
    
    Node* start = new Node(sum[0]);

    int i = 0;
    while(++i < sum.size())
    {
        start = insertNode(new Node(sum[i]), start);
    }
    
    printNodal(start);
    cout << endl;
    cout << endl;
    
    return 0;
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
