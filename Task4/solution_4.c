#include<stdio.h>

#define BLACK 0.4
#define WHITE 0.7

#define RIGHT 1
#define LEFT 2

enum direction{
    north, east, south, west
};

void print_readings(double *readings){
    printf("%lf %lf %lf %lf %lf\n", readings[0], readings[1], readings[2], readings[3], readings[4]);
}

int assign_direction(enum direction current, int turn){
    enum direction future;
    if(turn == RIGHT){
        future = (current + 1)%4;
    }

    else if(turn == LEFT){
        future = (current - 1)%4;
    }
    return future;
}

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

void copy_readings(double *readings, double *prev_readings){
    for(int i = 0; i < 5; i++){
        prev_readings[i] = readings[i];
    }
}

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

        // Turn left
        if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE){
            
            // Debug
            // print_readings(readings);
            // printf("%d\n", line_count);

            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                // Don't count till bot takes left turn
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK && readings[4]>WHITE){
                    // print_readings(previous_readings);
                    current_direction = assign_direction(current_direction, LEFT);
                    printf("LEFT TURN ---- %s ---- %s\n", type_of_junction(previous_readings), return_direction(current_direction));
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // Straight + Right
        else if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE && readings[4]>WHITE){
            
            // Debug
            // print_readings(readings);
            // printf("%d\n", line_count);

            // Don't count till bot comes out of the node
            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                if(readings[0]<WHITE && readings[3]<WHITE){
                    // printf("%d\n", line_count);
                    printf("STRAIGHT ---- %s ---- %s\n", type_of_junction(previous_readings), return_direction(current_direction));
                    break;
                }

                // Check if its a node
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // Turn right
        else if((readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE) || (readings[3]>WHITE && readings[2]>WHITE && readings[4]<WHITE)){
            
            // Debug
            // print_readings(readings);
            // printf("%d\n", line_count);

            while(fscanf(filepointer, "%lf %lf %lf %lf %lf", &readings[0], &readings[1], &readings[2], &readings[3], &readings[4]) != EOF){
                line_count++;
                // Don't count till bot takes right turn
                if(readings[0]<BLACK && readings[1]>WHITE && readings[2]>WHITE && readings[3]<BLACK && readings[4]>WHITE){
                    // print_readings(previous_readings);
                    printf("RIGHT TURN ---- %s ---- %s\n", type_of_junction(previous_readings), return_direction(current_direction));

                    current_direction = assign_direction(current_direction, RIGHT);
                    break;
                }

                // Check if its a node
                else if(readings[0]>WHITE && readings[1]>WHITE && readings[2]>WHITE && readings[3]>WHITE){
                    break;
                }

                copy_readings(readings, previous_readings);
            }
        }

        // Dead end
        else if(readings[0]<BLACK && readings[1]<BLACK && readings[2]<BLACK && readings[3]<BLACK && readings[4]<BLACK){

            // Debug
            // print_readings(readings);
            // printf("%d\n", line_count);

            printf("STOP ---- %s ---- %s\n", type_of_junction(readings), return_direction(current_direction));
            break;
        }

    }

    fclose(filepointer);

    return 0;
}