#include<stdio.h>

#define BLACK 0.4   // THRESHOLD FOR BLACK
#define WHITE 0.7   // THRESHOLD FOR WHITE

#define RIGHT 1
#define LEFT 2

// ENCODING DIRECTION AS PER PROBLEM STATEMENT
enum direction{
    north, east, south, west
};

// PRINT READINGS TO CONSOLE
void print_readings(double *readings){
    printf("%lf %lf %lf %lf %lf\n", readings[0], readings[1], readings[2], readings[3], readings[4]);
}

// DECIDE FUTURE DIRECTION BASED ON CURRENT DIRECTION AND TYPE OF TURN
int assign_direction(enum direction current, int turn_type){
    enum direction future;
    if(turn_type == RIGHT){
        future = (current + 1)%4;   // %4 FOR RESTRICTING VALUES TO 0 AND 3
    }

    else if(turn_type == LEFT){
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

// FOR COPYING READINGS TO PREVIOUS READINGS
void copy_readings(double *readings, double *prev_readings){
    for(int i = 0; i < 5; i++){
        prev_readings[i] = readings[i];
    }
}

// DETECTING JUNCTION TYPE
const char *type_of_junction(double *readings){
    
    if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE && readings[4]>WHITE){
        return "PLUS";
    }
    else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE && readings[4]<WHITE){
        return "T";
    }
    else if(readings[2]>WHITE && readings[3]>WHITE && readings[4]>WHITE){
        return "RIGHT + STRAIGHT";
    }
    else if(readings[0]>WHITE && readings[1]>WHITE && readings[4]>WHITE){
        return "LEFT + STRAIGHT";
    }
    else if(readings[3]>WHITE){
        return "ONLY RIGHT";
    }
    else if(readings[0]>WHITE){
        return "ONLY LEFT";
    }
    else if(readings[0]<BLACK && readings[1]<BLACK && readings[2]<BLACK && readings[3]<BLACK && readings[4]<BLACK){
        return "END";
    }
    
    return "UNKNOWN";
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

    double readings[5];
    double previous_readings[5];
    enum direction current_direction = north;

    int line_count = 0;

    while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
         
        line_count++;

        // TURN LEFT
        if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON A JUNCTION HAVING LEFT TURN
            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                
                // END OF LEFT TURN
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK && readings[4]>WHITE){
                    current_direction = assign_direction(current_direction, LEFT);
                    printf("%-10s\t%-18s\t%-10s\n", "LEFT TURN", type_of_junction(previous_readings), return_direction(current_direction));
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // STRAIGHT + RIGHT
        else if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE && readings[4]>WHITE){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON A JUNCTION WITH PATH FORWARD AND RIGHTWARDS
            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                
                // END OF JUNCTION
                if(readings[0]<WHITE && readings[3]<WHITE){
                    printf("%-10s\t%-18s\t%-10s\n", "STRAIGHT", type_of_junction(previous_readings), return_direction(current_direction));
                    break;
                }

                // CHECK IF IT WAS A NODE
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // TURN RIGHT
        else if((readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE) || (readings[3]>WHITE && readings[2]>WHITE && readings[4]<WHITE)){
            
            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            // CURRENTLY ON A JUNCTION HAVING RIGHT TURN
            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                
                // END OF RIGHT TURN
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK && readings[4]>WHITE){
                    current_direction = assign_direction(current_direction, RIGHT);
                    printf("%-10s\t%-18s\t%-10s\n", "RIGHT TURN", type_of_junction(previous_readings), return_direction(current_direction));
                    break;
                }

                // CHECK IF IT WAS A NODE
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // DEAD END
        else if(readings[0]<BLACK && readings[1]<BLACK && readings[2]<BLACK && readings[3]<BLACK && readings[4]<BLACK){

            // DEBUGGING
            // print_readings(readings);
            // printf("Line: %d\n", line_count);

            printf("%-10s\t%-18s\t%-10s\n", "STOP", type_of_junction(readings), return_direction(current_direction));
            break;
        }

    }

    fclose(filepointer);

    return 0;
}