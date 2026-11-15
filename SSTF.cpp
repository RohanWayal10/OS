#include <iostream>
#include <cstdlib> // for abs()
using namespace std;

int main() 
{
    int RQ[100], i, n, TotalHeadMoment = 0, initial, count = 0;
    
    cout << "Enter the number of Requests\n";
    cin >> n;
    
    cout << "Enter the Requests sequence\n";
    for (i = 0; i < n; i++) 
    {
        cin >> RQ[i];
    }
    
    cout << "Enter initial head position\n";
    cin >> initial;

    // Logic for SSTF disk scheduling
    /* Loop will execute until all processes are completed */
    while (count != n) 
    {
        int min = 1000, d, index = -1;
        
        for (i = 0; i < n; i++) 
        {
            d = abs(RQ[i] - initial);
            if (min > d) 
            {
                min = d;
                index = i;
            }
        }
        
        TotalHeadMoment = TotalHeadMoment + min;
        initial = RQ[index];
        
        // 1000 is used as a marker for visited requests
        RQ[index] = 1000;
        count++;
    }
    
    cout << "Total head movement is " << TotalHeadMoment << endl;
    return 0;
}
