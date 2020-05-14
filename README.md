# sra-eklavya-tasks-solutions  
This repo contains all the solutions for the problems given to first years in [Eklavya 2020](https://sra-vjti.github.io/eklavya2020-assignments/)
hosted by [SRA VJTI](http://sra.vjti.info/) in the period of lockdown due to COVID-19.  

## Task 1  
Finding number of nodes encountered by a line following robot.  
Detailed problem statement can be found [here](https://sra-vjti.github.io/eklavya2020-assignments/assignment_1.html).
  
    gcc solution_1.c  
    ./a.out  
    
**Output**  

    Enter the filename: data.txt  
    Number of nodes encountered are: 3!!  
    
    Enter the filename: data_1.txt  
    Number of nodes encountered are: 3!!  

## Task 2  
Finding number of nodes, left turns, right turns and final facing direction of a line following robot.  
Detailed problem statement can be found [here](https://sra-vjti.github.io/eklavya2020-assignments/assignment_2.html).

    gcc solution_2.c  
    ./a.out  
    
**Output**  

    Enter the filename: data.txt
    NODE
    RIGHT TURN
    Number of nodes encountered are: 1!!
    Number of left turns encountered are: 0!!
    Number of right turns encountered are: 1!!
    You are now facing: East!!  
    
    Enter the filename: data_1.txt
    NODE
    RIGHT TURN
    LEFT TURN
    Number of nodes encountered are: 1!!
    Number of left turns encountered are: 1!!
    Number of right turns encountered are: 1!!
    You are now facing: North!!  
    
    Enter the filename: data_2.txt
    LEFT TURN
    RIGHT TURN
    LEFT TURN
    NODE
    Number of nodes encountered are: 1!!
    Number of left turns encountered are: 2!!
    Number of right turns encountered are: 1!!
    You are now facing: West!!  
    
    Enter the filename: data_3.txt
    RIGHT TURN
    Number of nodes encountered are: 0!!
    Number of left turns encountered are: 0!!
    Number of right turns encountered are: 1!!
    You are now facing: East!!  
    
    Enter the filename: data_4.txt
    RIGHT TURN
    LEFT TURN
    LEFT TURN
    RIGHT TURN
    RIGHT TURN
    LEFT TURN
    NODE
    RIGHT TURN
    LEFT TURN
    LEFT TURN
    RIGHT TURN
    RIGHT TURN
    Number of nodes encountered are: 1!!
    Number of left turns encountered are: 5!!
    Number of right turns encountered are: 6!!
    You are now facing: East!!  
    
## Task 3  
Given a lidar data in bin file, find the distance and strength readings and plot the same.  
Detailed problem statement can be found [here](https://sra-vjti.github.io/eklavya2020-assignments/assignment_3.html).

    gcc solution_3.c  
    ./a.out  
    
    gnuplot  
    gnuplot> plot "./distance.txt" using 1:2 with linespoints  
    gnuplot> plot "./signal.txt " using 1:2 with linespoints  
    
**Output**  

    Enter the filename: data.bin
    Reading, Distance, Strength
    1, 2000, 200
    2, 2000, 200  
    ...  
    
    Enter the filename: data_1.bin
    Reading, Distance, Strength
    1, 2000, 80
    2, 2000, 80  
    ...  
    102, 1500, 120
    103, 1500, 120  

**Output Plots**  
**data.bin**  
  
Distance  
![distance](https://github.com/saharshleo/sra-eklavya-tasks-solutions/blob/master/Task3/data_distance.png)  
  
Strength  
![signal](https://github.com/saharshleo/sra-eklavya-tasks-solutions/blob/master/Task3/data_signal.png)  

**data_1.bin**  

Distance  
![distance_1](https://github.com/saharshleo/sra-eklavya-tasks-solutions/blob/master/Task3/data_1_distance.png)  

Strength
![signal_1](https://github.com/saharshleo/sra-eklavya-tasks-solutions/blob/master/Task3/data_1_signal.png)  
    
## Task 4  
Given line sensor data of a line following bot in a maze following Left follow rule, 
write left follow algorithm and give dynamic output for encountered turn, type of junction and direction facing.  
Detailed problem statement can be found [here](https://sra-vjti.github.io/eklavya2020-assignments/bonus.html).  
Password is `1N5L6R_east2000`.  
  
    gcc solution_4.c  
    ./a.out  
  
**Output**  

    Enter the filename: data.txt
    LEFT TURN       PLUS                    West      
    RIGHT TURN      ONLY RIGHT              North     
    LEFT TURN       LEFT + STRAIGHT         West      
    RIGHT TURN      ONLY RIGHT              North     
    STRAIGHT        RIGHT + STRAIGHT        North     
    RIGHT TURN      ONLY RIGHT              East      
    RIGHT TURN      ONLY RIGHT              South     
    LEFT TURN       PLUS                    East      
    RIGHT TURN      ONLY RIGHT              South     
    LEFT TURN       ONLY LEFT               East      
    LEFT TURN       ONLY LEFT               North     
    STRAIGHT        RIGHT + STRAIGHT        North     
    STOP            END                     North      
    
    
