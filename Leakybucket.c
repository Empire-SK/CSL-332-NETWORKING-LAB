#include <stdio.h>

int main() {
    int bucket_size, output_rate, n, i;
    int packet_size;

    int bucket = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter output rate: ");
    scanf("%d", &output_rate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    for(i = 1; i <= n; i++) {
        printf("\nEnter size of packet %d: ", i);
        scanf("%d", &packet_size);

        if(bucket + packet_size <= bucket_size) {
            bucket += packet_size;
            printf("Packet accepted. Bucket content = %d\n", bucket);
        } 
        else {
            printf("Packet dropped (bucket overflow)\n");
        }

        if(bucket >= output_rate) {
            bucket -= output_rate;
        } 
        else {
            bucket = 0;
        }

        printf("After leaking, bucket content = %d\n", bucket);
    }

    return 0;
}