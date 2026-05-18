#include <stdio.h>

int main() {
    int bucket, rate, n;
    int store = 0, incoming;

    printf("Enter bucket size, rate, number of inputs: ");
    scanf("%d %d %d", &bucket, &rate, &n);

    while (n > 0) {
        printf("\nEnter incoming packet size: ");
        scanf("%d", &incoming);

        // Add packets to buffer
        if (store + incoming <= bucket) {
            store = store + incoming;
        } else {
            printf("Dropped: %d\n", (store + incoming) - bucket);
            store = bucket;
        }

        printf("Buffer: %d / %d\n", store, bucket);

        // Send packets out
        if (store > rate) {
            store = store - rate;
        } else {
            store = 0;
        }

        printf("After outgoing: %d / %d\n", store, bucket);

        n--;
    }

    return 0;
}
