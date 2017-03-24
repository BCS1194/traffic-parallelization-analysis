#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct car {
  int speed;
  char path[];
};

struct road {
  int cost;
  int length;
  int capacity;
  int time;
  char origin;
  char destination;
  struct car cars[];
};


int simulation_one() {
  struct road a;// = malloc(sizeof(10));
  a.cost        = 3;
  a.length 	= 6;
  a.capacity    = 10;
  a.time	= 1;
  a.origin	= 'a';
  a.destination = 'b';

 /* car mazda = malloc(sizeof(car));

  mazda.path = [];
  mazda.speed = 1;

 int rand = Math.random(srand());*/
}

int main() {
  return 0;
}
