#include<stdio.h>

// PRINT READINGS FROM BUFFER IN HEXADECIMAL FORM
void print_buffer_hex(unsigned char *buffer){
    for(int i = 0; i < 10; i++){
        printf("%x ", buffer[i]);
    }
}

// PRINT READINGS FROM BUFFER IN INTEGER FORM
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
    int distance;
    int strength;
    int checksum;
    int reading_count = 0;

    fread(buffer, sizeof(buffer), 1, filepointer);

    printf("Reading, Distance, Strength\n");

    while(!feof(filepointer)){
        reading_count++;

        // CHECK DATA READ
        // print_buffer_hex(buffer);
        // print_buffer_int(buffer);
        
        // CALCULATE CHECKSUM
        checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7];
        // printf("Checksum_cal: %d  from data: %d\n", checksum % 256, buffer[8]);

        // PRINT IF CHECKSUM VERIFIED
        // %256 ----> FOR LOWER BYTE
        if(checksum % 256 == buffer[8]){
            distance = 256 * buffer[3] + buffer[2]; // SINCE BUFFER[3] HAS HIGHER BYTE
            strength = 256 * buffer[5] + buffer[4]; // SINCE BUFFER[5] HAS HIGHER BYTE
            printf("%d, %d, %d\n", reading_count, distance, strength);

            // WRITE DISTANCE AND SIGNAL TO RESPECTIVE FILES
            fprintf(file_distance, "%d, %d\n", reading_count, distance);
            fprintf(file_signal, "%d, %d\n", reading_count, strength);
        }
        
        fread(buffer, sizeof(buffer), 1, filepointer);
    }

    fclose(filepointer);

    return 0;
}