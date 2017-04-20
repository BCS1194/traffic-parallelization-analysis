#include <stdio.h>
#include <stdlib.h>

struct car {
    int size;                 // Size of the car; standard is 1
    //struct node_log path;   // A record of the nodes visited by the car
};

typedef struct road {
    char road_id;              // The number of the road
    int cost;                 // The initial cost of the road (how long it takes to get from point A to point B on this road)
    int size;                 // The current size of the road (the cost of the road + the number of cars)
    int capacity;             // The maximum possible size of the road
    char origin;              // The start node
    char destination;         // The end node, must match start node of next road chosen
    //struct car cars[10];      // A list of the cars currently on this road
    //struct node_log * next;   // A reference to the next node, null for last node
} road;

road roads[13];
struct road shortest;
struct road next_road;
struct road a, b, c, d, e, f, g, h, i, j,  k, l, m;

struct road switches(struct road shortest);
struct road shortest_path(struct road a, struct road b);
struct road setup(struct road origin, struct road next_road);

void getFilename(char *filename) 
{
  //printf("Enter filename: ");
  //scanf("%s", filename);
  //fgets(filename, 100, stdin);

}

void readFile(char *filename)
{
  
  FILE * fp;
  int ii = 0;
  filename = "input1.txt";


  fp = fopen(filename, "r");//change to filename
  for(ii = 0; ii < 13; ii++) {
    fscanf(fp,"%c, %d, %d, %d, %c, %c\n", &roads[ii].road_id, &roads[ii].cost, &roads[ii].size,
                                        &roads[ii].capacity, &roads[ii].origin, &roads[ii].destination);


  // printf("ii: %d.  ", ii);

    //printf("ii is %d: %c %d %d %d %c %c\n", ii, roads[ii].road_id, roads[ii].cost, roads[ii].size,
    //                                            roads[ii].capacity, roads[ii].origin, roads[ii].destination);
  }
  fclose(fp);
}

void simulation_one() {
    road a = {roads[0].road_id, roads[0].cost, roads[0].size, roads[0].capacity, roads[0].origin, roads[0].destination}; // Origin road
    struct road b = {roads[1].road_id, roads[1].cost, roads[1].size, roads[1].capacity, roads[1].origin, roads[1].destination}; // Origin road
    struct road c = {roads[2].road_id, roads[2].cost, roads[2].size, roads[2].capacity, roads[2].origin, roads[2].destination};
    struct road d = {roads[3].road_id, roads[3].cost, roads[3].size, roads[3].capacity, roads[3].origin, roads[3].destination};
    struct road e = {roads[4].road_id, roads[4].cost, roads[4].size, roads[4].capacity, roads[4].origin, roads[4].destination};
    struct road f = {roads[5].road_id, roads[5].cost, roads[5].size, roads[5].capacity, roads[5].origin, roads[5].destination};
    struct road g = {roads[6].road_id, roads[6].cost, roads[6].size, roads[6].capacity, roads[6].origin, roads[6].destination};
    struct road h = {roads[7].road_id, roads[7].cost, roads[7].size, roads[7].capacity, roads[7].origin, roads[7].destination};
    struct road i = {roads[8].road_id, roads[8].cost, roads[8].size, roads[8].capacity, roads[8].origin, roads[8].destination};
    struct road j = {roads[9].road_id, roads[9].cost, roads[9].size, roads[9].capacity, roads[9].origin, roads[9].destination};
    struct road k = {roads[10].road_id, roads[10].cost, roads[10].size, roads[10].capacity, roads[10].origin, roads[10].destination};
    struct road l = {roads[11].road_id, roads[11].cost, roads[11].size, roads[11].capacity, roads[11].origin, roads[11].destination};
    struct road m = {roads[12].road_id, roads[12].cost, roads[12].size, roads[12].capacity, roads[12].origin, roads[12].destination};


  if (a.cost <= b.cost) {
    shortest = a;
    switches(shortest);
    if (shortest.road_id == 'c') {
      switches(shortest);
    }

  }

  else {
    shortest = b;
  }



}


int main()
{
  char filename[26];
  getFilename(filename);
  readFile(filename);
  simulation_one();
  //printf("filename: %s\n", filename);


}


/********************************************************************
 * This function takes in two different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
struct road shortest_path(struct road a, struct road b)
{
    struct road shortest;
    if (a.cost < b.cost) {
        shortest = a;
    }
    else {
        shortest = b;
    }
    return shortest;
}



/********************************************************************
 * This function takes in the old road, the next_road, and the car and
 * will move the car from the old road to the new road and print
 * out a message for the user.
 *******************************************************************/
struct road setup(struct road origin, struct road next)
{
    origin.destination  = next.origin;
    
    if (next.origin == 'm' || next.origin == 'l')
        printf("Car 1 left road %c and reached its destination of road %c\n", origin.origin, next.origin);
    else
        printf("Car 1 left road %c and entered road %c\n", origin.origin, origin.destination);

    return next;
}


/********************************************************************
 * 
 *******************************************************************/
struct road switches(struct road shortest) {
      switch (shortest.road_id) {
        case 'a':
          next_road = shortest_path(c, shortest_path(d, h));
          shortest = setup(shortest, next_road);
          break;
        case 'b':
          next_road = shortest_path(e, f);
          shortest = setup(shortest, next_road);
          break;
        case 'c':
          next_road = g;
          shortest = setup(shortest, next_road);
          break;
        case 'd':
          next_road = shortest_path(j, shortest_path(k, i));
          shortest = setup(shortest, next_road);
          break;
        case 'e':
          next_road = shortest_path(j, shortest_path(k, i));
          shortest = setup(shortest, next_road);
          break;
        case 'f':
          next_road = shortest_path(j, shortest_path(k, i));
          shortest = setup(shortest, next_road);;
          break;
        case 'g':
          next_road = shortest_path(m, j);
          shortest = setup(shortest, next_road);
          break;
        case 'h':
          next_road = shortest_path(m, j);
          shortest = setup(shortest, next_road);
          break;
        case 'i':
          next_road = shortest_path(k, l);
          shortest = setup(shortest, next_road);
          break;
        case 'j':
          next_road = shortest_path(m, k);
          shortest = setup(shortest, next_road);
          break;
        case 'k':
          next_road = shortest_path(l, m);
          shortest = setup(shortest, next_road);
          break;
    }
}
