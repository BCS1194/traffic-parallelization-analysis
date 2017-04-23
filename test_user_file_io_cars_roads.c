#include "cars.h"

road_t shortest;
int cars_buffer[100];

/********************************************************************
 * This is the driver function for the program.
 *******************************************************************/
int main()
{
    int num_lines;
    int cars_count;
    int roads_count;
    char filename[26]; //look in to this
    int num_roads_remaining;

    get_filename(filename);
    num_lines = count_lines(filename);
    road_t roads[num_lines];
    read_file(filename, roads, num_lines);
    num_roads_remaining = (sizeof(roads) / sizeof(int)) / 2;

    printf("Enter a number (1-100) for the number of cars you would like to generate: ");
    scanf("%d", &cars_count);
    printf("The number of cars on the road is %d\n", cars_count);

    for(int i = 0; i < cars_count; i++)
    {
        cars_buffer[i] = 1;
    }

    /*for(int i = 0; i < 100; i++)
    {
        printf("%d\n", cars_buffer[i]);
    }*/

    simulation_one(roads, num_roads_remaining);

    //maybe implement another loop here to initialize all 100 entries to 0 first
}

/********************************************************************
 * This function gets the name of the file.
 *******************************************************************/
void get_filename(char *filename) 
{
    printf("Enter filename: ");
    scanf("%s", filename);
}

/********************************************************************
 * This function reads the contents of a file and saves it to the
 * road_t struct.
 *******************************************************************/
void read_file(char *filename, road_t roads[], int num_lines)
{ 
    FILE * fp;
    int ii = 0;

    fp = fopen(filename, "r");//change to filename
    if (!fp) {
        printf("Error file does not exist.\n");
        exit(0);
    }
    for(ii = 0; ii < num_lines; ii++)
    {
      fscanf(fp,"%d,%c\n", &roads[ii].cost, &roads[ii].id);
      //printf("%d %c\n", roads[ii].cost, roads[ii].id);
    }

    fclose(fp);
}

/********************************************************************
 * Simulation.
 *******************************************************************/
void simulation_one(road_t roads[], int num_roads_remaining)
{
    int jj = 0;

    //printf("\n%ld\n", (sizeof(roads) / sizeof(int)) / 2);
    //printf("%d\n", num_roads_remaining);

    printf("OUTSIDE CALL: %d %c\n", shortest.cost, shortest.id);

    shortest_path(roads, roads[0], roads[1], num_roads_remaining, jj);

    printf("\nThe shortest cost road is %c with a cost of %d\n", shortest.id, shortest.cost);
}

/********************************************************************
 * This function takes in different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
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

/********************************************************************
 * This function takes in a file and counts the number of lines
 * that are used in the file and returns the number of lines.
 *******************************************************************/
int count_lines(char *filename)
{
    int line = 0;
    int num_lines = 0;
    FILE *fp = fopen(filename,"r");
    
    if (!fp) {
        printf("Error file does not exist.\n");
        return 0;
    }
    
    num_lines++;

    while ((line = fgetc(fp)) != EOF)
    {
        if (line == '\n')
            num_lines++;
    }
    fclose(fp);
    return (num_lines - 1);
}

