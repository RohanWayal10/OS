#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main(void)
{
    int n, m;
    int alloc[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];
    int finish[MAX_P] = {0};
    int safeSeq[MAX_P];
    int work[MAX_R];

    int i, j, count = 0;

    // Input number of processes
    printf("Enter number of processes (1-%d): ", MAX_P);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_P)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Input number of resource types
    printf("Enter number of resource types (1-%d): ", MAX_R);

    if (scanf("%d", &m) != 1 || m < 1 || m > MAX_R)
    {
        printf("Invalid number of resource types.\n");
        return 1;
    }

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            if (scanf("%d", &alloc[i][j]) != 1 || alloc[i][j] < 0)
            {
                printf("Invalid allocation value.\n");
                return 1;
            }
        }
    }

    // Input Maximum Demand Matrix
    printf("\nEnter Maximum Demand Matrix (%d x %d):\n", n, m);

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            if (scanf("%d", &max[i][j]) != 1 || max[i][j] < alloc[i][j])
            {
                printf("Invalid maximum demand: it must be >= allocation.\n");
                return 1;
            }
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources (%d values): ", m);

    for (j = 0; j < m; j++)
    {
        if (scanf("%d", &available[j]) != 1 || available[j] < 0)
        {
            printf("Invalid available resource value.\n");
            return 1;
        }
    }

    // Calculate Need Matrix
    printf("\nNeed Matrix (Maximum - Allocation):\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // Initialize Work = Available
    for (j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    // Check Safe Sequence
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int canFinish = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = 0;
                        break;
                    }
                }

                if (canFinish)
                {
                    for (j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            break;
        }
    }

    // Display Result
    if (count == n)
    {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in an UNSAFE state.\n");
        printf("No safe sequence exists for the given data.\n");
    }

    return 0;
}
