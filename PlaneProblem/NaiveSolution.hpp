//
//  NaiveSolution.hpp
//  PlaneProblem
//
//  Created by Sart Way on 11/4/23.
//

#ifndef NaiveSolution_hpp
#define NaiveSolution_hpp

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
class NaiveSolution
{
public:
    NaiveSolution(){}
    ~NaiveSolution(){}
    long getLargestModSequence(int x, int y, vector<long> array, long mod, int SIZE);
    long getLargestModSequence(int x, int y, long* array, long mod);
    long getLargestModSequence(int x, int y, vector<long> array, int SIZE, long mod)
    {
        if(x == SIZE || y == SIZE || x >= y)
        {
            return 0;
        } else {
            long A = getLargestModSequence(x, y+1, array, SIZE, mod);
            long B = getLargestModSequence(x+1, y, array, SIZE, mod);

            long C = ((array[y] - array[x])+mod)%mod;
            long CA = array[y];

            C = CA > C ? CA : C;
            return A > B ? A > C ? A : C : B > C ? B : C;
        }
    }
    
    
    long getLargestModSequence(vector<long>array, long mod)
    {
        int SIZE = (int)array.size();
        long** answer = new long*[SIZE + 1];
        for(int i=0;i<=SIZE;++i)
        {
            answer[i] = new long[SIZE+1];
        }
        
        for(int i=0;i<=SIZE;++i)
        {
            if(i==SIZE)
            {
                for(int j=0;j<=SIZE;++j)
                {
                    answer[i][j] = 0;
                }
            } else {
                for(int j=0;j<SIZE;++j)
                {
                    if(j <= i)
                    {
                        answer[i][j] = 0;
                    } else {
                        answer[i][j] = -1;
                    }
                }
                answer[i][SIZE] = 0;
            }
        }
        
//        for(int i=0;i<=SIZE;++i)
//        {
//            for(int j=0;j<=SIZE;++j)
//            {
//                cout << answer[i][j] << " ";
//            }
//            cout << endl;
//        }
        long maxans = LONG_MIN;
        for(int i=0;i<SIZE;++i)
        {
            for(int j=i+1;j<SIZE;++j)
            {
                long C = ((array[j] - array[i])+mod)%mod;
                long CA = array[j];

                C = CA > C ? CA : C;
                long A = answer[i][j+1];
                long B = answer[i+1][j];
                answer[i][j] = A > B ? A > C ? A : C : B > C ? B : C;
                if(answer[i][j] > maxans)
                {
                    maxans = answer[i][j];
                }
            }
        }
        
        //cout << maxans << endl;
        return maxans;
    }
    
    pair<long,pair<int,int>> getLargestModSequences(vector<long>array, long od)
    {
        pair<long, pair<int,int>>answers;
        int SIZE = (int)array.size();
        int pointOne = -1;
        int pointTwo = 0;
        long** answer = new long*[SIZE + 1];
        pair<int,int>**positron = new pair<int,int>*[SIZE+1];
        for(int i=0;i<=SIZE;++i)
        {
            positron[i] = new pair<int,int>[SIZE+1];
            answer[i] = new long[SIZE+1];
        }
        
        for(int i=0;i<=SIZE;++i)
        {
            if(i==SIZE)
            {
                for(int j=0;j<=SIZE;++j)
                {
                    answer[i][j] = 0;
                    positron[i][j] = pair<int,int>(-1,-1);
                }
            } else {
                for(int j=0;j<SIZE;++j)
                {
                    if(j <= i)
                    {
                        answer[i][j] = 0;
                        positron[i][j] = pair<int,int>(-1,-1);
                    } else {
                        answer[i][j] = -1;
                        positron[i][j] = pair<int,int>(-1,-1);
                    }
                }
                answer[i][SIZE] = 0;
            }
        }
        
//        for(int i=0;i<=SIZE;++i)
//        {
//            for(int j=0;j<=SIZE;++j)
//            {
//                cout << answer[i][j] << " ";
//            }
//            cout << endl;
//        }
        long maxans = LONG_MIN;
        long secondMax = LONG_MIN;
        for(int i=0;i<SIZE;++i)
        {
            for(int j=i+1;j<SIZE;++j)
            {
                long C = ((array[j] - array[i])+od)%od;
                if(C > secondMax)
                {
                    secondMax = C;
                    pointOne = i;
                    pointTwo = j;
                }
                long CA = array[j];

                C = CA > C ? CA : C;

                long A = answer[i][j+1];
                long B = answer[i+1][j];
                answer[i][j] = A > B ? A > C ? A : C : B > C ? B : C;
                if(answer[i][j] > maxans)
                {
                    maxans = answer[i][j];
                }
            }
        }
        
        answers.first = maxans;
        answers.second = pair<int,int>(pointOne,pointTwo);
        return answers;
    }
    
};
#endif /* NaiveSolution_hpp */
