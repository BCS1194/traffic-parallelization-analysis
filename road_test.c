#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//linked list
/*typedef*/
struct node_log {
  char node;        // The value or data stored in the node
  struct node_log * next;  // A reference to the next node, null for last node
} /*node_t*/;

struct car {
  //int speed;
  int size;         //size of the car; standard is 1
  struct node_log path;    //a record of the nodes visited by the car
};

struct road {
  int cost;           //the weight cost of the road
  int size;           //the current size of the road
  int capacity;       //the maximum possible size of the road
  char origin;        //the start node
  char destination;   //the end node, must match the start node of the next road to be joined
  struct car cars[10];  //a list of the cars currently on this road
  
  //int length;       //the distance (in measurable units) of the road
  //int time;         //the time it would take for a car to get from start to end
};

int simulation_one()
{
  struct road a = {a.size, 0, 10}; //, 'c', 'd', NULL};
  struct car roadX[10];
  
  
  struct car car1 = {1};
  struct car car2;
  struct car car3;
  struct car car4;
  car1.size = 1;
  car2.size = 1;
  car3.size = 1;
  car4.size = 1;
  
  a.cars[0] = car1;
  a.cars[1] = car2;
  a.cars[2] = car3;
  a.cars[3] = car4;
  for (int ii = 0; ii < 10; ii++) {
    roadX[ii].size = 0;
  }
  roadX[2] = car1;
  
  int jj = 0;
  int kk = jj+1;
  for (int ii = 0; ii < 10; ii++) {
    if(roadX[ii].size != 1  && a.cars[ii].size == 1) {
      printf("Car %d entered road on slot %d.\n", ii, jj);
      roadX[ii] = a.cars[jj++];
      
    }
    else if(a.cars[ii].size != 1) {
      continue;
    }
    else {
      printf("Car %d left spot %d and moved to spot %d\n", ii, ii, ii+1 );
      roadX[ii+1] = a.cars[jj++];
      roadX[ii] = a.cars[kk];
    }
    // printf("Car %d left spot %d and moved to spot %d\n", jj, ii, ii+1 );
  }
  
}

int main()
{
  simulation_one();
  return 0;
}
