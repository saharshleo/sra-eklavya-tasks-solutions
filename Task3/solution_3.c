#include<stdio.h>

void print_buffer_hex(unsigned char *buffer){
    for(int i = 0; i < 10; i++){
        printf("%x ", buffer[i]);
    }
}

void print_buffer_int(unsigned char *buffer){
    for(int i = 0; i < 10; i++){
        printf("%d ", buffer[i]);
    }
}

int main(){

    char filename[20];
    printf("Enter the filename: ");

    // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
    scanf("%[^\n]%*c", filename); 

    FILE *filepointer;
    filepointer = fopen(filename, "r");
    if(filepointer == NULL){
        printf("Cannot Read File\n");
        return 0;
    }

    FILE *file_distance;
    file_distance = fopen("distance.txt", "w");
    
    FILE *file_signal;
    file_signal = fopen("signal.txt", "w");
    
    unsigned char buffer[10];
    int distance, strength, checksum, reading_count = 0;

    fread(buffer, sizeof(buffer), 1, filepointer);

    printf("Reading, Distance, Strength\n");

    while(!feof(filepointer)){
        reading_count++;

        // print_buffer_hex(buffer);
        // print_buffer_int(buffer);
        
        // calculate checksum
        checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7];
        // printf("Checksum_cal: %d  from data: %d\n", checksum % 256, buffer[8]);

        // Print if checksum verified
        if(checksum % 256 == buffer[8]){
            distance = 256 * buffer[3] + buffer[2];
            strength = 256 * buffer[5] + buffer[4];
            printf("%d, %d, %d\n", reading_count, distance, strength);

            fprintf(file_distance, "%d, %d\n", reading_count, distance);
            fprintf(file_signal, "%d, %d\n", reading_count, strength);
        }
        
        fread(buffer, sizeof(buffer), 1, filepointer);
    }

    fclose(filepointer);

    return 0;
}