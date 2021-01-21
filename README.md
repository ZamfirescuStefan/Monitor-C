# Monitor implementation in C 

Implementation of a monitor that resolves bounded producer/consumer problem using conditional variables. 


## The program is compiled with the command: 

> $ gcc Monitor.h Monitor.c main.c -o exe -pthread
  
## The program is run with:
> $ ./exe 
 
## The stuctucture for the input is:
* size of buffer
* number of producers
* values of producers
* number of consumers
* values of consumers

<i>
This program was developed as a homework for the Operating System Class at the University of Bucharest, Faculty of Mathematics and Computer Science, 2020-2021.
</i>
