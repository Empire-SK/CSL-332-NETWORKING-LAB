#include <stdio.h>

int main(){
    int n, storage = 0, out_rate, psize, bsize, size_left;
    int total_accepted = 0, total_dropped = 0, total_sent = 0;
    printf("Enter the number of inputs: ");
    scanf("%d", &n);
    printf("Enter the bucket size: ");
    scanf("%d", &bsize);
    printf("Enter the outgoing rate: ");
    scanf("%d", &out_rate);
    printf("\n=== Leaky Bucket Simulation ===\n");
    for(int i = 0; i < n; i++){
        printf("\n--- Time Step %d ---\n", i + 1);
        printf("Enter incoming packet size: ");
        scanf("%d", &psize);
        size_left = bsize - storage;
        if(psize <= size_left){
            storage += psize;
            total_accepted += psize;
            printf("✓ Accepted: %d units\n", psize);
        }else{
            int accepted = size_left; 
            int dropped = psize - size_left;
            if(accepted > 0){
                storage += accepted;
                total_accepted += accepted;
                printf("✓ Partially accepted: %d units\n", accepted);
            }
            total_dropped += dropped;
            printf("✗ Dropped: %d units\n", dropped);
        }
        printf("Bucket status (before leak): %d/%d\n", storage, bsize);
        int sent = (storage >= out_rate) ? out_rate : storage;
        storage -= sent;
        total_sent += sent;
        printf("Outgoing: %d units\n", sent);
        printf("Bucket status (after leak): %d/%d\n", storage, bsize);
    } 
    printf("\n--- Emptying remaining bucket ---\n");
    while(storage > 0){
        int sent = (storage >= out_rate) ? out_rate : storage;
        storage -= sent;
        total_sent += sent;
        printf("Outgoing: %d units | Remaining: %d/%d\n", sent, storage, bsize);
    }
    printf("\n=== Simulation Summary ===\n");
    printf("Total accepted: %d units\n", total_accepted);
    printf("Total dropped: %d units\n", total_dropped);
    printf("Total sent: %d units\n", total_sent);
    printf("Bucket empty: Yes\n");
    return 0;
}

