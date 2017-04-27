#include "cars.h"
#include <stdbool.h>

road_t shortest;
road_t new_road;
road_t test_road[9];
int cars_buffer[100];
bool arrived = false;

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
<<<<<<< HEAD
    int k = 0;
    for (int ii = 1; arrived != true; ii++) {
        if (k == 0) {
            test_road[k] = find_path(shortest, test_road[k], roads, 0);
            //printf("IN If: test_road[k] = %c\n", test_road[k].id);
            k++;
        }
        test_road[ii] = find_path(test_road[ii-1], test_road[ii], roads, 0);
    }
    //printf("2test switch statement: 1:%c 2:%c\n", shortest.id, new_road.id);
=======
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
    
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
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
            printf("Case A.\n");
            new_road = roads[5];
            break;
        case 'B':
            printf("Case B.\n");
            path_opt[0] = roads[6];
            path_opt[1] = roads[7];
            path_opt[2] = roads[8];
<<<<<<< HEAD
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
=======
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'C':
            printf("Case C.\n");
            new_road = roads[9];
            break;
        case 'D':
            printf("Case D.\n");
            new_road = roads[10];
            break;
        case 'E':
            printf("Case E.\n");
            new_road = roads[11];
            break;
        case 'F':
<<<<<<< HEAD
            printf("Case F.\n");
            path_opt[0] = roads[12];
            path_opt[1] = roads[13];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'G':
            printf("Case G.\n");
            new_road = shortest_path(roads, roads[12], roads[13], 1, jj);
=======
            new_road = shortest_path(roads, roads[12], roads[13], 0, 0);
            break;
        case 'G':
            new_road = shortest_path(roads, roads[12], roads[13], 0, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'H':
            printf("Case H.\n");
            path_opt[0] = roads[18];
            path_opt[1] = roads[19];
            path_opt[2] = roads[20];
            path_opt[3] = roads[21];
<<<<<<< HEAD
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 3, jj);
=======
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'I':
            printf("Case I.\n");
            new_road = roads[9];
            break;
        case 'J':
            printf("Case J.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
<<<<<<< HEAD
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
=======
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'K':
            printf("Case K.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
<<<<<<< HEAD
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
=======
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'L':
            printf("Case L.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
<<<<<<< HEAD
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'M':
            printf("Case M.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
=======
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 1, 0);
            break;
        case 'M':
            new_road = shortest_path(roads, roads[26], roads[27], 0, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'N':
            printf("Case N.\n");
            new_road = roads[17];
            break;
        case 'O':
<<<<<<< HEAD
            printf("Case O.\n");
            new_road = shortest_path(roads, roads[22], roads[23], 1, jj);
            break;
        case 'P':
            printf("Case P.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'Q':
            printf("Case Q.\n");
            new_road = shortest_path(roads, roads[24], roads[25], 1, jj);
            break;
        case 'R':
            printf("Case R.\n");
            new_road = shortest_path(roads, roads[28], roads[29], 1, jj);
=======
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
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'S':
            printf("Case S.\n");
            new_road = roads[17];
            break;
        case 'T':
<<<<<<< HEAD
            printf("Case T.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
=======
            new_road = shortest_path(roads, roads[26], roads[27], 0, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'U':
            printf("Case U.\n");
            new_road = roads[30];
            break;
        case 'V':
<<<<<<< HEAD
            printf("Case V.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
=======
            new_road = shortest_path(roads, roads[31], roads[32], 0, 0);
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
            break;
        case 'W':
            printf("Case W.\n");
            new_road = roads[30];
            break;
        case 'X':
<<<<<<< HEAD
            printf("Case X.\n");
            new_road = shortest_path(roads, roads[24], roads[25], 1, jj);
            break;
        case 'Y':
            printf("Case Y.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'Z':
            printf("Case Z.\n");
            new_road = shortest_path(roads, roads[33], roads[34], 1, jj);
            break;
        case '1':
            printf("You have reached your destination (27).\n");
            arrived = true;
            break;
        case '2':
            printf("Case 28.\n");
            new_road = shortest_path(roads, roads[28], roads[29], 1, jj);
            break;
        case '3':
            printf("You have reached your destination (29).\n");
            arrived = true;
            break;
        case '4':
            printf("Case 30.\n");
            new_road = roads[30];
            break;
        case '5':
            printf("You have reached your destination (31).\n");
            arrived = true;
            break;
        case '6':
            printf("Case 32.\n");
            new_road = roads[30];
            break;
        case '7':
            printf("You have reached your destination (33).\n");
            arrived = true;
            break;
        case '8':
            printf("Case 34.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case '9':
            printf("You have reached your destination (35).\n");
            arrived = true;
            break;
        default:
            printf("Default.\n");
            path_opt[0] = roads[0];
            path_opt[1] = roads[1];
            path_opt[2] = roads[2];
            path_opt[3] = roads[3];
            path_opt[4] = roads[4];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 4, 0);
            break;
=======
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
>>>>>>> dd19570d6b749772c909f6532f454e644791cb66
    }
    return new_road;
}

