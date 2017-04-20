#include <stdio.h>
#include <stdlib.h>


typedef struct road {
    int  cost;
    char id;             
} road_t;

road_t shortest;
road_t roads[9];

int num_roads_remaining = (sizeof(roads) / sizeof(int)) / 2;
int jj               = 0;

void shortest_path(road_t a, road_t b, int num_roads_remaining, int jj);

void getFilename(char *filename) 
{
  printf("Enter filename: ");
  scanf("%s", filename);
}

void readFile(char *filename)
{
  
  FILE * fp;
  int ii = 0;

  fp = fopen(filename, "r");//change to filename
  for(ii = 0; ii < 9; ii++) {
    fscanf(fp,"%d,%c\n", &roads[ii].cost, &roads[ii].id);
    printf("%d %c\n", roads[ii].cost, roads[ii].id);
  }
  fclose(fp);
}

void simulation_one() {
    road_t a = {roads[0].cost, roads[0].id}; // Origin road
    road_t b = {roads[1].cost, roads[1].id}; // Origin road
    road_t c = {roads[2].cost, roads[2].id};
    road_t d = {roads[3].cost, roads[3].id};
    road_t e = {roads[4].cost, roads[4].id};
    road_t f = {roads[5].cost, roads[5].id}; // Origin road
    road_t g = {roads[6].cost, roads[6].id}; // Origin road
    road_t h = {roads[7].cost, roads[7].id};
    road_t i = {roads[8].cost, roads[8].id};
    road_t j = {roads[9].cost, roads[9].id};

    printf("\n%ld\n", (sizeof(roads) / sizeof(int)) / 2);
    printf("%d\n", num_roads_remaining);

    printf("OUTSIDE CALL: %d %c\n", shortest.cost, shortest.id);

    shortest_path(roads[0], roads[1], num_roads_remaining, jj);

    printf("\n%d\n", shortest.cost);
}

void shortest_path(road_t a, road_t b, int num_roads_remaining, int jj)
{
    printf("\nThis is call %d\n", jj + 1);

    if(a.cost < b.cost)
        shortest = a;
    else
        shortest = b;

    printf("INSIDE CALL: %d %c\n", shortest.cost, shortest.id);

    num_roads_remaining--;
    jj++;

    printf("num_roads_remaining = %d\n", num_roads_remaining);
    printf("index = %d\n", jj);

    if(num_roads_remaining == 0)
        return;
    else
        shortest_path(shortest, roads[jj], num_roads_remaining, jj);
}

int main()
{
  char filename[26];
  getFilename(filename);
  readFile(filename);
  simulation_one();
  //printf("filename: %s\n", filename);


}



