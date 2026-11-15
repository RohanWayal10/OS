#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void selectionsort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        int minidx = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (a[j] < a[minidx]) 
            {
                minidx = j;
            }
        }
        int temp = a[i];
        a[i] = a[minidx];
        a[minidx] = temp;
    }
    cout << "\nusing selection sort \n";
    cout << "sorted array: ";
    for (int i = 0; i < n; i++) 
    {
        cout << a[i] << "\t";
    }
    cout << endl;
}

void bubblesort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (a[j] > a[j + 1]) 
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    cout << "\nusing bubble sort \n";
    cout << "sorted array: ";
    for (int i = 0; i < n; i++) 
    {
        cout << a[i] << "\t";
    }
    cout << endl;
}

int main() 
{
    int a[10];
    int n;
    
    cout << "enter value of n: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) 
    {
        cout << "enter element " << i + 1 << ": ";
        cin >> a[i];
    }
    
    cout << "Array is: ";
    for (int i = 0; i < n; i++) 
    {
        cout << a[i] << "\t";
    }
    cout << endl;

    pid_t pid = fork();

    if (pid < 0) 
    {
        cout << "\nprocess not created" << endl;
        exit(1);
    } 
    else 
    {
        if (pid == 0) 
        {
            // Child Process
            cout << "\n--- Child Process ---" << endl;
            cout << "Child ID: " << getpid() << ", Parent ID: " << getppid() << endl;
            bubblesort(a, n);
        } 
        else 
        {
            // Parent Process
            // Optional: wait(NULL); // Uncomment if you want parent to wait for child to finish first
            cout << "\n--- Parent Process ---" << endl;
            cout << "Parent ID: " << getpid() << endl;
            selectionsort(a, n);
        }
    }

    return 0;
}
