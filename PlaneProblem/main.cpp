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
int CeilIndex(int* v, int l, int r, int key);

int CeilIndex(int* v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}




int main(int argc, const char * argv[]) {
    
    fstream input("File.txt", ios::in | ios::out);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        long m = stol(first_multiple_input[1]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split(rtrim(a_temp_temp));

        vector<long> a(n);

        for (int i = 0; i < n; i++) {
            long a_item = stol(a_temp[i]);

            a[i] = a_item;
        }

        long result = maximumSum(a, m);

        cout << result << "\n";
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
    long ans = 0;
    long ans_two = 0;
    vector<long>lister;
    vector<vector<long>>horizontal_lister;
    lister.push_back(sum[0]);
    vector<long>buffer;
    horizontal_lister.push_back(buffer);
    for(int i=1;i<sum.size();++i)
    {
        if(lister[lister.size() - 1] < sum[i])
        {
            vector<long>buffer;
            horizontal_lister.push_back(buffer);
            lister.push_back(sum[i]);
        } else {
            
        }
    }
    
    
    
    
    
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
