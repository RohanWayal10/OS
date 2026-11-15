#include <iostream>
#include <cstdlib> // for abs()
using namespace std;

int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move;
    
    cout << "Enter the number of Requests\n";
    cin >> n;
    
    cout << "Enter the Requests sequence\n";
    for (i = 0; i < n; i++)
        cin >> RQ[i];
        
    cout << "Enter initial head position\n";
    cin >> initial;
    
    cout << "Enter total disk size\n";
    cin >> size;
    
    cout << "Enter the head movement direction for high 1 and for low 0\n";
    cin >> move;

    // Logic for SCAN disk scheduling
    // Logic to sort the request array
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index = n;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }

    // If movement is towards high value
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        // Last movement for max size (size - 1)
        TotalHeadMoment = TotalHeadMoment + abs((size - 1) - initial);
        initial = size - 1;
        
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    // If movement is towards low value
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        // Last movement for min size (0)
        TotalHeadMoment = TotalHeadMoment + abs(initial - 0);
        initial = 0;
        
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    cout << "Total head movement is " << TotalHeadMoment << endl;
    return 0;
}
