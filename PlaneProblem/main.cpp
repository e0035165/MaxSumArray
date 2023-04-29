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
long newmaximumSum(vector<long> a, long m);
void longer(pair<long,int>[], int, int);
void merger(pair<long,int>[], int, int, int);
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
    //cout << curr->index << " ";
    vect.push_back(curr);

    printNodal(curr->right,vect);

    return;
}

void longer(pair<long,int>arr[], int start, int end)
{
    if(start >= end)
    {
        return;
    }
    int mid = start + ((end - start) / 2);
    longer(arr, start, mid);
    longer(arr, mid + 1, end);
    merger(arr, start, mid, end);
}

void merger(pair<long,int> arr[], int start, int mid, int end)
{
    pair<long,int>* leftarr_copy = new pair<long,int>[(mid - start) + 1];
    pair<long,int>* rightarr_copy = new pair<long,int>[end - mid];
    int right = 0;
    int left = 0;

    for (int x = start; x <= mid; x++) {
        leftarr_copy[left] = arr[x];
        left++;
    }

    for (int x = mid + 1; x <= end; x++) {
        rightarr_copy[right] = arr[x];
        right++;
    }
    
    int right_ptr = 0;
    int left_ptr = 0;
    int x = start;
    while (right_ptr < right && left_ptr < left) {
        if (rightarr_copy[right_ptr].first < leftarr_copy[left_ptr].first) {
            arr[x] = rightarr_copy[right_ptr];
            right_ptr++;
        }
        else {
            arr[x] = leftarr_copy[left_ptr];
            left_ptr++;
        }
        x++;
    }
    if (left_ptr == left) {
        while (right_ptr < right) {
            arr[x] = rightarr_copy[right_ptr];
            x++;
            right_ptr++;
        }
    }
    else {
        while (left_ptr < left) {
            arr[x] = leftarr_copy[left_ptr];
            x++;
            left_ptr++;
        }
    }

    delete[] leftarr_copy;
    delete[] rightarr_copy;
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
    fstream output("output.txt", ios::in);
    string q_temp;
    getline(input, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));
    //cout << q << endl;
    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        string rtemp;
        getline(input, first_multiple_input_temp);
        getline(output, rtemp);
        long r = stol(ltrim(rtrim(rtemp)));
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
        long result = newmaximumSum(a, m);
        cout << result << endl;
        if(result != r)
        {
            cout << "Failure " << endl;
            break;
        }
        maxans = 0;
    }

    input.close();

    return 0;
}


long maximumSum(vector<long> a, long m) {
    //cout << m << endl;
    vector<long>sum_forward((int)a.size());
    sum_forward[0] = a[0]%m;
    
    int i = 0;
    while(++i<(int)a.size())
    {
        sum_forward[i] = ((sum_forward[i-1]%m) + (a[i]%m))%m;
    }
    
    Node* start = new Node(sum_forward[0],0);
    if(start->data > maxans)
    {
        maxans = start->data;
    }
    Node* max = new Node(LONG_MAX);
    Node* min = new Node(LONG_MIN);
    for(int i=1;i<a.size();++i)
    {

        Node* temp = new Node(sum_forward[i],i);
        if(temp->data > maxans)
        {
            maxans = temp->data;
        }
        start = insertNode(temp, start, min, max);
        
    }
    vector<Node*>nextone;
    printNodal(start, nextone);
    //cout << endl;
    int ptone = -1;
    int ptTwo = 0;
    for(int i=0;i<nextone.size()-1;++i)
    {
        //long lte = m - (nextone[i+1]->data - nextone[i]->data);
        long lte = 0;
        if(nextone[i+1]->index > nextone[i]->index)
        {
            lte = nextone[i+1]->data - nextone[i]->data;
        } else {
            lte = m - (nextone[i+1]->data - nextone[i]->data);
        }
        if(lte > maxans)
        {
            ptone = nextone[i]->index;
            ptTwo = nextone[i+1]->index;
            maxans = lte;
        }
    }
    
    return maxans;
}


long newmaximumSum(vector<long> a, long m) {
    //cout << m << endl;
    vector<long>sum_forward((int)a.size());
    sum_forward[0] = a[0]%m;
    pair<long,int>* enigma = new pair<long,int>[(int)a.size()];
    enigma[0].first = sum_forward[0];
    enigma[0].second = 0;
    int i = 0;
    if(sum_forward[0] > maxans)
    {
        maxans = sum_forward[0];
    }
    while(++i<(int)a.size())
    {
        sum_forward[i] = ((sum_forward[i-1]%m) + (a[i]%m))%m;
        if(sum_forward[i] > maxans)
        {
            maxans = sum_forward[i];
        }
        enigma[i].first = sum_forward[i];
        enigma[i].second = i;
    }
    
    longer(enigma,0,(int)(a.size()-1));
    for(int i=0;i<a.size()-1;++i)
    {
        long lte = 0;
        if(enigma[i+1].second > enigma[i].second)
        {
            lte = enigma[i+1].first - enigma[i].first;
        } else {
            lte = m - (enigma[i+1].first - enigma[i].first);
        }
        if(lte > maxans)
        {
            maxans = lte;
        }
    }
    
    
    
    
    return maxans;
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
