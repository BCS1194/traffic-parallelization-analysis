#include "cars.h"
#include <omp.h>



road_t shortest;
road_t new_road;
road_t test_road[9];
int cars_buffer[100];
bool arrived = false;
bool new = true;
//car_t cars[];




/********************************************************************
 * This is the driver function for the program.
 *******************************************************************/
int main()
{
    int num_lines = 0;
    int cars_count = 0;
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
    
    printf("cars_count: %d\n", cars_count);
    simulation_one(roads, num_roads_remaining, cars_count);
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
        fscanf(fp,"%c,%d\n", &roads[ii].id, &roads[ii].cost);
    }
    
    fclose(fp);
}

/********************************************************************
 * Simulation.
 *******************************************************************/
void simulation_one(road_t roads[], int num_roads_remaining, int cars_count)
{
    car_t cars[cars_count];
    
    //initialize cars to be used
    for (int kk = 0; kk < cars_count; kk++)
    {
        car_t new_car = {kk, 1};
        cars[kk] = new_car;
    }
    
#   pragma omp parallel for default(none) shared(arrived, shortest, test_road, new_road, cars, cars_count, roads)
    for(int jj = 0; jj < cars_count; jj++)
    {
#       pragma omp critical
        arrived = false;
        shortest.id = '\0';
        int k = 0;
        
#       pragma omp critical
        for (int ii = 1; arrived != true; ii++) {
            if (k == 0) {
                test_road[k] = find_path(shortest, test_road[k], roads, &cars[jj], 0, jj);
                test_road[k].cost += cars[jj].weight;
                k++;
            }
          
            test_road[ii] = find_path(test_road[ii-1], test_road[ii], roads, &cars[jj], 0, jj);
            cars[jj].current_road = test_road[ii];
            int pp = 0;

            if (test_road[ii].id == roads[pp++].id) {
                roads[pp].cost += cars[jj].weight;
                pp = 0;
            }

            if (test_road[ii-1].id == roads[pp++].id) {
                roads[pp].cost -= cars[jj].weight;
            	pp = 0;
            }
        }
    }
}

/********************************************************************
 * This function takes in different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
road_t shortest_path(road_t roads[], road_t a, road_t b, int num_roads_remaining, int jj)
{
    if(a.cost < b.cost)
        shortest = a;
    else
        shortest = b;
    
    num_roads_remaining--;
    jj++;
    
    if(num_roads_remaining == 0)
        return shortest;
    else
        shortest_path(roads, shortest, roads[jj], num_roads_remaining, jj);
    
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
        printf("File has too many arguments (%d lines), must limit to 35 lines.\n", num_lines);
        exit(0);
    }
    fclose(fp);
    return (num_lines - 1);
}


road_t find_path(road_t road, road_t new_road, road_t roads[], car_t cass[], int num_roads_remaining, int ll)
{
    road_t path_opt[5];
    int jj = 0;
    
    switch (road.id)
    {
        case 'A':
            printf("Road 1.\n");
            new_road = roads[5];
            break;
        case 'B':
            printf("Road 2.\n");
            path_opt[0] = roads[6];
            path_opt[1] = roads[7];
            path_opt[2] = roads[8];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'C':
            printf("Road 3.\n");
            new_road = roads[9];
            break;
        case 'D':
            printf("Road 4.\n");
            new_road = roads[10];
            break;
        case 'E':
            printf("Road 5.\n");
            new_road = roads[11];
            break;
        case 'F':
            printf("Road 6.\n");
            path_opt[0] = roads[12];
            path_opt[1] = roads[13];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'G':
            printf("Road 7.\n");
            new_road = shortest_path(roads, roads[12], roads[13], 1, jj);
            break;
        case 'H':
            printf("Road 8.\n");
            path_opt[0] = roads[18];
            path_opt[1] = roads[19];
            path_opt[2] = roads[20];
            path_opt[3] = roads[21];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 3, jj);
            break;
        case 'I':
            printf("Road 9.\n");
            new_road = roads[9];
            break;
        case 'J':
            printf("Road 10.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'K':
            printf("Road 11.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'L':
            printf("Road 12.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'M':
            printf("Road 13.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
            break;
        case 'N':
            printf("Road 14.\n");
            new_road = roads[17];
            break;
        case 'O':
            printf("Road 15.\n");
            new_road = shortest_path(roads, roads[22], roads[23], 1, jj);
            break;
        case 'P':
            printf("Road 16.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'Q':
            printf("Road 17.\n");
            new_road = shortest_path(roads, roads[24], roads[25], 1, jj);
            break;
        case 'R':
            printf("Road 18.\n");
            new_road = shortest_path(roads, roads[28], roads[29], 1, jj);
            break;
        case 'S':
            printf("Road 19.\n");
            new_road = roads[17];
            break;
        case 'T':
            printf("Road 20.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
            break;
        case 'U':
            printf("Road 21.\n");
            new_road = roads[30];
            break;
        case 'V':
            printf("Road 22.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'W':
            printf("Road 23.\n");
            new_road = roads[30];
            break;
        case 'X':
            printf("Road 24.\n");
            new_road = shortest_path(roads, roads[24], roads[25], 1, jj);
            break;
        case 'Y':
            printf("Road 25.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'Z':
            printf("Road 26.\n");
            new_road = shortest_path(roads, roads[33], roads[34], 1, jj);
            break;
        case '1':
            printf("You have reached your destination (Road 27).\n");
            arrived = true;
            break;
        case '2':
            printf("Road 28.\n");
            new_road = shortest_path(roads, roads[28], roads[29], 1, jj);
            break;
        case '3':
            printf("You have reached your destination (Road 29).\n");
            arrived = true;
            break;
        case '4':
            printf("Road 30.\n");
            new_road = roads[30];
            break;
        case '5':
            printf("You have reached your destination (Road 31).\n");
            arrived = true;
            break;
        case '6':
            printf("Road 32.\n");
            new_road = roads[30];
            break;
        case '7':
            printf("You have reached your destination (Road 33).\n");
            arrived = true;
            break;
        case '8':
            printf("Road 34.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case '9':
            printf("You have reached your destination (Road 35).\n");
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
            
    }
    return new_road;
}

