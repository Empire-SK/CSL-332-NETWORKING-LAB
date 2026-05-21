#include <stdio.h>

int main()
{
    int n, i, j, k;
    int cost[10][10], dist[10][10], via[10][10];

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            via[i][j] = -1;
        }
    }

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    via[i][j] = k;
                }
            }
        }
    }

    printf("\nShortest distance table:\n");
    for(i = 0; i < n; i++)
    {
        printf("Router %d:\n", i+1);
        for(j = 0; j < n; j++)
        {
            if(i == j)
                printf("To node %d distance = %d (self)\n", j+1, dist[i][j]);
            else if(via[i][j] == -1)
                printf("To node %d distance = %d (direct)\n", j+1, dist[i][j]);
            else
                printf("To node %d distance = %d via node %d\n", j+1, dist[i][j], via[i][j]+1);
        }
        printf("\n");
    }

    return 0;
}