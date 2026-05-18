#include <stdio.h>

#define N 10
#define INF 9999

int main() {
    int cost[N][N], dist[N][N], from[N][N];
    int n;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Input + Initialization
    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = cost[i][j];

            from[i][j] = j;
        }
    }

    // Bellman-Ford logic
    int change;
    do {
        change = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {

                    if (dist[i][k] + cost[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + cost[k][j];
                        from[i][j] = from[i][k];
                        change = 1;
                    }

                }
            }
        }

    } while (change);

    // Output
    for (int i = 0; i < n; i++) {
        printf("\nRouter %d\n", i + 1);

        for (int j = 0; j < n; j++) {
            printf("To %d via %d cost %d\n",
                   j + 1, from[i][j] + 1, dist[i][j]);
        }
    }

    return 0;
}
