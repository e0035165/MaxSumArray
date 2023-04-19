//
//  NaiveSolution.cpp
//  PlaneProblem
//
//  Created by Sart Way on 11/4/23.
//

#include "NaiveSolution.hpp"
long NaiveSolution::getLargestModSequence(int x, int y, vector<long> array, long mod, int SIZE)
{
    if(x == SIZE || y == SIZE)
    {
        return 0;
    } else {
        long A = getLargestModSequence(x, y+1, array, mod, SIZE);
//        long B = getLargestModSequence(x+1, y, array, mod, SIZE);
        long B = 0;
        if(x+1 < y)
        {
            B = getLargestModSequence(x+1, y, array, mod, SIZE);
        }

        long C = ((array[y] - array[x])+mod)%mod;
        long CA = array[y];

        C = CA > C ? CA : C;
        return A > B ? A > C ? A : C : B > C ? B : C;
    }
}
