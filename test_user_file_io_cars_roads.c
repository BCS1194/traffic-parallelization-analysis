#include "cars.h"

road_t shortest;
int cars_buffer[100];

int main()
{
    int lines;
    int cars_count;
    int roads_count;
    char filename[26]; //look in to this
    int num_roads_remaining;

    getFilename(filename);
    lines = countLines(filename);
    road_t roads[lines];
    readFile(filename, roads, lines);
    num_roads_remaining = (sizeof(roads) / sizeof(int)) / 2;
    //printf("filename: %s\n", filename);

    printf("Enter a number (1-100) for the number of cars you would like to generate: ");
    scanf("%d", &cars_count);
    printf("Your number is %d\n", cars_count);

    for(int i = 0; i < cars_count; i++)
    {
        cars_buffer[i] = 1;
    }

    /*for(int i = 0; i < 100; i++)
    {
        printf("%d\n", cars_buffer[i]);
    }*/

   
    printf("*****%d\n", lines);
    simulation_one(roads, num_roads_remaining);


    //maybe implement another loop here to initialize all 100 entries to 0 first
}

void getFilename(char *filename) 
{
    printf("Enter filename: ");
    scanf("%s", filename);
}

void readFile(char *filename, road_t roads[], int lines)
{ 
    FILE * fp;
    int ii = 0;
    int jj = 0;

    fp = fopen(filename, "r");//change to filename

    for(ii = 0; ii < lines; ii++)
    {
      fscanf(fp,"%d,%c\n", &roads[ii].cost, &roads[ii].id);
      printf("%d %c\n", roads[ii].cost, roads[ii].id);
    }

    fclose(fp);
}

void simulation_one(road_t roads[], int num_roads_remaining)
{
    int jj = 0;
    //num_roads_remaining = (sizeof(roads) / sizeof(int)) / 2;
/*
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
*/

    //printf("\n%ld\n", (sizeof(roads) / sizeof(int)) / 2);
    printf("%d\n", num_roads_remaining);

    printf("OUTSIDE CALL: %d %c\n", shortest.cost, shortest.id);

    shortest_path(roads, roads[0], roads[1], num_roads_remaining, jj);

    printf("\n%d\n", shortest.cost);
}

void shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj)
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
        shortest_path(roads, shortest, roads[jj], num_roads_remaining, jj);
}

int countLines(char *filename)
{
    // count the number of lines in the file called filename
    
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;
    
    if (fp == NULL)
        return 0;
    
    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return (lines - 1);
}

