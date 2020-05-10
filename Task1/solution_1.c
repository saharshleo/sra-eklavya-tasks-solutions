#include<stdio.h>

#define BLACK 0.4
#define WHITE 0.7

void print_readings(double *readings){
    printf("%lf %lf %lf %lf\n", readings[0], readings[1], readings[2], readings[3]);
}

int main(){

    char filename[20];
    printf("Enter the filename: ");

    // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
    scanf("%[^\n]%*c", filename); 

    FILE *filepointer;
    filepointer = fopen(filename, "r");
    
    if(filepointer == NULL){
        printf("Cannot Read File");
        return 0;
    }

    double readings[4];
    int node_count = 0;
    int line_count = 0;
   
    while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
        
        line_count++;

        if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
            
            // Debugging
            // print_readings(readings);
            // printf("Line: %d\n", line_count)
            
            // Don't count till bot comes out of the node
            while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
                line_count++;
                if(readings[0]<WHITE && readings[3]<WHITE){
                    node_count++;
                    break;
                }
            }
        }
    
    }

    printf("Number of nodes encountered are: %d!!\n", node_count);

    fclose(filepointer);

    return 0;
}