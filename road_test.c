#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//linked list
/*typedef*/
struct node_log {
  char node;                // The value or data stored in the node
  struct node_log * next;   // A reference to the next node, null for last node
} /*node_t*/;

struct car {
  //int speed;
  int size;             //size of the car; standard is 1
  struct node_log path; //a record of the nodes visited by the car
};

struct road {
  int cost;           //the weight cost of the road
  int size;           //the current size of the road
  int capacity;       //the maximum possible size of the road
  char origin;        //the start node
  char destination;   //the end node, must match the start node of the next road to be joined
  struct car cars[10];//a list of the cars currently on this road
  
  //int length;       //the distance (in measurable units) of the road
  //int time;         //the time it would take for a car to get from start to end
};

int simulation_one()
{
  struct road a = {a.size, 0, 10};  //, 'c', 'd', NULL};
  struct car actual_road[10] = {0}; //initialize the road and set all spaces to size 0
  
  
  struct car car1 = {1}; //initialize car with a size of 1
  struct car car2 = {1};
  struct car car3 = {1};
  struct car car4 = {1};
  
  a.cars[0] = car1;
  a.cars[1] = car2;
  a.cars[2] = car3;
  a.cars[3] = car4;

  actual_road[2] = car1;
  
  int jj = 0;
  int kk = 1;
  for (int ii = 0; ii < 10; ii++) {
    if(actual_road[ii].size != 1 && a.cars[ii].size == 1) {
      printf("Car %d entered road on slot %d.\n", ii, jj);
      actual_road[ii] = a.cars[jj++];
      
    }
    else if(a.cars[ii].size != 1) {
      continue;
    }
    else {
      printf("Car %d left spot %d and moved to spot %d\n", ii, ii, ii+1 );
      actual_road[ii+1] = a.cars[jj++];
      actual_road[ii] = a.cars[kk];
    }
    // printf("Car %d left spot %d and moved to spot %d\n", jj, ii, ii+1 );
  }
  return 1;
}

int main()
{
  simulation_one();
  return 0;
}
