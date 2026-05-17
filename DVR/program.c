#include <stdio.h>

#define MAX 10

int main() {
    int cost[MAX][MAX], dist[MAX][MAX];
    int n, i, j, k;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
        }
    }

    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {

                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }

            }
        }
    }

    printf("\nShortest distance matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}