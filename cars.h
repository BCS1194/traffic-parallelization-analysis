#ifndef cars_h
#define cars_h

#include <stdio.h>
#include <stdlib.h>


typedef struct road {
    char id;
    int  cost;
} road_t;

typedef struct car {
    int id;
    int weight;
    road_t current_road;
    road_t roads_traveled[];
} car_t;

void get_filename(char *filename);
int count_lines(char *filename);
void read_file(char *filename, road_t roads[], int lines);
void simulation_one(road_t roads[], int num_roads_remaining, int cars_count);
road_t find_path(road_t road, road_t new_road, road_t roads[], int num_roads_remaining);
road_t shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj);

#endif
