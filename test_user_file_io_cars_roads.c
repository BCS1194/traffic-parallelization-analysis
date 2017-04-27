#include "cars.h"
#include <stdbool.h>

road_t shortest;
road_t new_road;
int cars_buffer[100];

/********************************************************************
 * This is the driver function for the program.
 *******************************************************************/
int main()
{
    int num_lines = 0;
    int cars_count = 0;
    //int roads_count = 0;
    char filename[26]; //look in to this
    int num_roads_remaining = 0;

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

    printf("%ld\n", (sizeof(roads) / sizeof(int)) / 2);
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
    //the maximum number of roads that could form a path from
    //origin to destination for this simulation
    #define MAX_ROADS_POSS 9

    int jj = 0;
    road_t path[MAX_ROADS_POSS];
    
    //printf("\n%ld\n", (sizeof(roads) / sizeof(int)) / 2);
    //printf("%d\n", num_roads_remaining);
    
    //printf("OUTSIDE CALL: %d %c\n", shortest.cost, shortest.id);
    
    
    
    
    //printf("\nThe shortest cost road is %c with a cost of %d\n", shortest.id, shortest.cost);
    
    int count = 0;
    bool first = true;

    printf("before while loop\n");

    while(count < MAX_ROADS_POSS)
    {
    printf("IN while loop, count = %d\n", count);
        if(first)
        {
            printf("IN IF, count = %d\n", count);
            path[count] = find_path_one(shortest, roads); //***********************************************
            count++;
            first = false;
        }

        path[count] = find_path_one(path[count - 1], roads);
        count++;
    }

    printf("%c\n", path[0].id);
    printf("%c\n", path[1].id);
    printf("%c\n", path[2].id);
    printf("%c\n", path[3].id);
    printf("%c\n", path[4].id);
    printf("%c\n", path[5].id);
    printf("%c\n", path[6].id);

    //path[0] = new_road;

    printf("test switch statement: %c\n", new_road.id);
    
    printf("done\n");
    
}

/********************************************************************
 * This function takes in different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
road_t shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj)
{
    printf("\nThis is call %d\n", jj + 1);

    if(a.cost < b.cost)
        shortest = a;
    else
        shortest = b;

    //printf("INSIDE CALL: %d %c\n", shortest.cost, shortest.id);

    num_roads_remaining--;
    jj++;

    //printf("num_roads_remaining = %d\n", num_roads_remaining);
    //printf("index = %d\n", jj);

    if(num_roads_remaining == 0)
        return shortest;
    else
        shortest_path(roads, shortest, roads[jj], num_roads_remaining, jj);

    //return shortest;
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

    if (num_lines >= 37) {
      printf("File has too many arguments, must limit to 35 lines.\n");
      exit(0);
    }
    fclose(fp);
    return (num_lines - 1);
}


/********************************************************************
* This function takes in a road and the array of all roads in the
* simulation and, based on the road's ID, determines which road
* should be next on the path by calling the shortest_path() function
* and passing in the appropriate roads to compare against. Each call
* to this function will add another road to the overall path until
* and end road is reached and the path is complete.
********************************************************************/
road_t find_path_one(road_t road, road_t roads[])
{
    road_t path_opt[5];
    road_t new_road;

    switch(road.id) {
        default:
            path_opt[0] = roads[0];
            path_opt[1] = roads[1];
            path_opt[2] = roads[2];
            path_opt[3] = roads[3];
            path_opt[4] = roads[4];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 4, 0);
            break;
        case 'A':
            new_road = roads[5];
            printf("%c\n", new_road.id);
            break;
        case 'B':
            path_opt[0] = roads[6];
            path_opt[1] = roads[7];
            path_opt[2] = roads[8];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
            break;
        case 'C':
            new_road = roads[9];
            break;
        case 'D':
            new_road = roads[10];
            break;
        case 'E':
            new_road = roads[11];
            break;
        case 'F':
            new_road = shortest_path(roads, roads[12], roads[13], 0, 0);
            break;
        case 'G':
            new_road = shortest_path(roads, roads[12], roads[13], 0, 0);
            break;
        case 'H':
            path_opt[0] = roads[18];
            path_opt[1] = roads[19];
            path_opt[2] = roads[20];
            path_opt[3] = roads[21];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, 0);
            break;
        case 'I':
            new_road = roads[9];
            break;
        case 'J':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
            break;
        case 'K':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
            break;
        case 'L':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
            break;
        case 'M':
            new_road = shortest_path(roads, roads[26], roads[27], 0, 0);
            break;
        case 'N':
            new_road = roads[17];
            break;
        case 'O':
            new_road = shortest_path(roads, roads[22], roads[23], 0, 0);
            break;
        case 'P':
            new_road = shortest_path(roads, roads[31], roads[32], 0, 0);
            break;
        case 'Q':
            new_road = shortest_path(roads, roads[24], roads[25], 0, 0);
            break;
        case 'R':
            new_road = shortest_path(roads, roads[28], roads[29], 0, 0);
            break;
        case 'S':
            new_road = roads[17];
            break;
        case 'T':
            new_road = shortest_path(roads, roads[26], roads[27], 0, 0);
            break;
        case 'U':
            new_road = roads[30];
            break;
        case 'V':
            new_road = shortest_path(roads, roads[31], roads[32], 0, 0);
            break;
        case 'W':
            new_road = roads[30];
            break;
        case 'X':
            new_road = shortest_path(roads, roads[24], roads[25], 0, 0);
            break;
        case 'Y':
            new_road = shortest_path(roads, roads[31], roads[32], 0, 0);
            break;
        case 'Z':
            new_road = shortest_path(roads, roads[33], roads[34], 0, 0);
            break;
        case 'a':
            printf("You have reached your destination (27).");
            break;
        case 'b':
            new_road = shortest_path(roads, roads[28], roads[29], 0, 0);
            break;
        case 'c':
            printf("You have reached your destination (29).");
            break;
        case 'd':
            new_road = roads[30];
            break;
        case 'e':
            printf("You have reached your destination (31).");
            break;
        case 'f':
            new_road = roads[30];
            break;
        case 'g':
            printf("You have reached your destination (33).");
            break;
        case 'h':
            new_road = shortest_path(roads, roads[31], roads[32], 0, 0);
            break;
        case 'i':
            printf("You have reached your destination (35).");
            break;
    }
    return new_road;
}

