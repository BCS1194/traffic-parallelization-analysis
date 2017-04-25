#include "cars.h"

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

    //printf("OUTSIDE CALL: %d %c\n", shortest.cost, shortest.id);



    //road_t first_road;

    shortest_path(roads, roads[0], roads[1], num_roads_remaining, jj);
         
    printf("\nThe shortest cost road is %c with a cost of %d\n", shortest.id, shortest.cost);
         
         //NEW STUFF
    road_t first_five[5] = {roads[0], roads[1], roads[2],
             roads[3], roads[4]};
         
    printf("New roads array has %ld roads stored in it\n", (sizeof(first_five) / sizeof(first_five[0])));
    
    shortest = shortest_path(first_five, first_five[0], first_five[1], 5, 0);
    
    printf("%d %c\n", shortest.cost, shortest.id);
    
    printf("The shortest road in the first_five array is %c\n", shortest.id);
    
    new_road = find_path(shortest, new_road, roads, num_roads_remaining);
    printf("test switch statement: %c\n", new_road.id);
    

    
}

/********************************************************************
 * This function takes in different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
road_t shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj)
{
    //printf("\nThis is call %d\n", jj + 1);

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
    //printf("INSIDE CALL: %d %c\n", shortest.cost, shortest.id);
    return shortest;
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


road_t find_path(road_t road, road_t new_road, road_t roads[], int num_roads_remaining)
{
    road_t path_opt[4];
    int jj = 0;
    switch(road.id) {
        case 'A':
            new_road = roads[5];
            break;
        case 'B':
            path_opt[0] = roads[6];
            path_opt[1] = roads[7];
            path_opt[2] = roads[8];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, jj);
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
            new_road = shortest_path(roads, roads[12], roads[13], num_roads_remaining, jj);
            break;
        case 'G':
            new_road = shortest_path(roads, roads[12], roads[13], num_roads_remaining, jj);
            break;
        case 'H':
            path_opt[0] = roads[18];
            path_opt[1] = roads[19];
            path_opt[2] = roads[20];
            path_opt[3] = roads[21];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'I':
            new_road = roads[9];
            break;
        case 'J':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, jj);
            break;
        case 'K':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, jj);
            break;
        case 'L':
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, jj);
            break;
        case 'M':
            new_road = shortest_path(roads, roads[26], roads[27], num_roads_remaining, jj);
            break;
        case 'N':
            new_road = roads[17];
            break;
        case 'O':
            new_road = shortest_path(roads, roads[22], roads[23], num_roads_remaining, jj);
            break;
        case 'P':
            new_road = shortest_path(roads, roads[31], roads[32], num_roads_remaining, jj);
            break;
        case 'Q':
            new_road = shortest_path(roads, roads[24], roads[25], num_roads_remaining, jj);
            break;
        case 'R':
            new_road = shortest_path(roads, roads[28], roads[29], num_roads_remaining, jj);
            break;
        case 'S':
            new_road = roads[17];
            break;
        case 'T':
            new_road = shortest_path(roads, roads[26], roads[27], num_roads_remaining, jj);
            break;
        case 'U':
            new_road = roads[30];
            break;
        case 'V':
            new_road = shortest_path(roads, roads[31], roads[32], num_roads_remaining, jj);
            break;
        case 'W':
            new_road = roads[30];
            break;
        case 'X':
            new_road = shortest_path(roads, roads[24], roads[25], num_roads_remaining, jj);
            break;
        case 'Y':
            new_road = shortest_path(roads, roads[31], roads[32], num_roads_remaining, jj);
            break;
        case 'Z':
            new_road = shortest_path(roads, roads[33], roads[34], num_roads_remaining, jj);
            break;
        case '1':
            printf("You have reached your destination (27).");
            break;
        case '2':
            new_road = shortest_path(roads, roads[28], roads[29], num_roads_remaining, jj);
            break;
        case '3':
            printf("You have reached your destination (29).");
            break;
        case '4':
            new_road = roads[30];
            break;
        case '5':
            printf("You have reached your destination (31).");
            break;
        case '6':
            new_road = roads[30];
            break;
        case '7':
            printf("You have reached your destination (33).");
            break;
        case '8':
            new_road = shortest_path(roads, roads[31], roads[32], num_roads_remaining, jj);
            break;
        case '9':
            printf("You have reached your destination (35).");
            break;
    }
    return new_road;
}

