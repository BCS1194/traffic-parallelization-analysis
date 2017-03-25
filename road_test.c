#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//linked list
/*typedef*/ struct node_log {
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
  struct car cars[];  //a list of the cars currently on this road

  //int length;       //the distance (in measurable units) of the road
  //int time;         //the time it would take for a car to get from start to end
};

int simulation_one()
{
  struct road a = {a.size, 0, 10}; //, 'c', 'd', NULL};
    //a.cars = [10];

  /*
    a.size        = 0;
    a.capacity    = 10;
    a.origin      = NULL;
    a.destination = NULL;
    a.cost        = a.size;
  */

    //a.length 	= 6;
    //a.time	= 1;

  struct car car1 = {1};

  /*
    car1.size   = 1;
    car1.path   = [];
  */
}

int main() 
{
  return 0;
}
