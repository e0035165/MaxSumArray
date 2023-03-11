//
//  main.cpp
//  PlaneProblem
//
//  Created by Sart Way on 18/2/23.
//

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    return 0;
}




int solution(int N, string &S) {
    // Implement your solution here
    int** rowLab = new int*[N];
    for(int i=0;i<N;++i)
    {
        rowLab[i] = new int[10];
        for(int j=0;j<10;++j)
        {
            rowLab[i][j] = 0;
        }
    }
    string s;
    stringstream ss(S);
    vector<string>v;
    while(getline(ss,s,' '))
    {
        v.push_back(s);
    }
    
    for(auto x=v.begin();x!=v.end();++x)
    {
        if((*x)[1] == 'J' || (*x)[1] == 'K')
        {
            rowLab[(int)((*x)[0] - '1')][(int)((*x)[1] - 'A' - 1)] = 1;
        } else {
            rowLab[(int)((*x)[0] - '1')][(int)((*x)[1] - 'A')] = 1;
        }
    }

    for(int i=0;i<N;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout << rowLab[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0;i<N;++i)
    {
        delete[] rowLab[i];
    }

    delete[] rowLab;

    return 1;
}
