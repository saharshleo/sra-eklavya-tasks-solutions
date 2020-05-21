#include<stdio.h>

#define BLACK 0.4   // THRESHOLD FOR BLACK
#define WHITE 0.7   // THRESHOLD FOR WHITE

// #define RIGHT 1
// #define LEFT 2

// ENCODING DIRECTION AS PER PROBLEM STATEMENT
enum direction{
    north, east, south, west
};

// PRINT READINGS TO CONSOLE
void print_readings(double *readings){
    printf("%lf %lf %lf %lf\n", readings[0], readings[1], readings[2], readings[3]);
}

// DECIDE FUTURE DIRECTION BASED ON CURRENT DIRECTION AND TYPE OF TURN
int assign_direction(enum direction current, char *turn_type){
    enum direction future;
    if(turn_type == "RIGHT"){
        future = (current + 1)%4;   // %4 FOR RESTRICTING VALUES TO 0 AND 3
    }

    else if(turn_type == "LEFT"){
        future = (current - 1)%4;   // %4 FOR RESTRICTING VALUES TO 0 AND 3
    }
    return future;
}

// RETURN DIRECTION NAME (STRING) BASED ON ENCODING (INTEGER)
const char *return_direction(enum direction current){
    switch (current){
        case north:
            return "North";
        
        case east:
            return "East";

        case south:
            return "South";
        
        case west:
            return "West";
        
        default:
            return "Unknown";
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

    double readings[4];
    int node_count = 0;
    int left_turn_count = 0;
    int right_turn_count = 0;
    enum direction current_direction = north;

    int line_count = 0;

    while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
         
        line_count++;

        // NODE
        if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON A NODE
            while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
                
                line_count++;
                
                // END OF NODE
                if(readings[0]<WHITE && readings[3]<WHITE){                    
                    printf("NODE\n");
                    node_count++;
                    break;
                }
            }
        }

        // TURN RIGHT
        else if(readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON RIGHT TURN
            while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
                
                line_count++;
               
                // END OF RIGHT TURN
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK){
                    printf("RIGHT TURN\n");
                    right_turn_count++;
                    current_direction = assign_direction(current_direction, "RIGHT");
                    break;
                }

                // CHECK IF IT WAS A NODE
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }
            }
        }
    
        // TURN LEFT
        else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON LEFT TURN
            while(fscanf(filepointer, "%lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3]) != EOF){
                
                line_count++;
                
                // END OF LEFT TURN
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK){
                    printf("LEFT TURN\n");
                    left_turn_count++;
                    current_direction = assign_direction(current_direction, "LEFT");
                    break;
                }

                // CHECK IF IT WAS A NODE
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }
            }
        }

    }

    printf("Number of nodes encountered are: %d!!\n", node_count);
    printf("Number of left turns encountered are: %d!!\n", left_turn_count);
    printf("Number of right turns encountered are: %d!!\n", right_turn_count);
    printf("You are now facing: %s!!\n", return_direction(current_direction));

    fclose(filepointer);

    return 0;
}