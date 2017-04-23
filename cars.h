#ifndef cars_h
#define cars_h

#include <stdio.h>
#include <stdlib.h>

typedef struct road {
    int  cost;
    char id;             
} road_t;

/*typedef struct node {
    struct node *next; //points to the next place
    struct info data; //contains the data
} node_t;*/

void shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj);
void get_filename(char *filename);
int count_lines(char *filename);
void read_file(char *filename, road_t roads[], int lines);
void simulation_one(road_t roads[], int num_roads_remaining);


#endif /* cars_h */
