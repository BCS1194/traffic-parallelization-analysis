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
    
    simulation_one(roads, num_roads_remaining, cars_count);
    
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
        fscanf(fp,"%c,%d\n", &roads[ii].id, &roads[ii].cost);
        //printf("%d %c\n", roads[ii].cost, roads[ii].id);
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
    //printf("fifth car is car #%d\n", cars[4].id);


    /* As it is right now, we either traverse all cars once per road, or all roads once per car.
     * I have it set up to do all cars once per road currently. So assuming 100 cars, that means
     * 100 cars will be sorted from the origin to the destination for each road until the arrival
     * boolean is tripped.
     *
     * For each iteration, the road's cost is being incrememnted and the previous road's cost is
     * decremented.
     *
     * When run, the results I see indicate that the first car in the array is traversing all roads
     * along the initial shortest path. Any other cars after the first car will report they have
     * reached their destination (Case 32) without actually traversing the map.
     *
     * There are other nuances with the execution output between 1 car and 100 cars. In writing this,
     * I feel that I may still be thinking about this wrongly....
     *
     * Good luck
     */


    //this loop will traverse the entire map
    for (int ii = 1; arrived != true; ii++) //this boolean needs to be reworked, maybe
    {
        printf("\nROAD %c\n", roads[ii].id);

        //this loop will traverse the entire array of cars
        for(int jj = 0; jj < cars_count; jj++)
        {
            printf("CAR %d\n", cars[jj].id);

            if (ii == 1)
            {
                test_road[ii - 1] = find_path(shortest, test_road[ii - 1], roads, 0);
                //printf("IN If: test_road[k] = %c\n", test_road[k].id);

            }

            test_road[ii] = find_path(test_road[ii - 1], test_road[ii], roads, 0);
            cars[jj].current_road = test_road[ii];

            //increment cost of current road by the weight of the current car
            roads[ii].cost += cars[jj].weight;

            //decrement cost of previous road by the weight value of current car
            roads[ii - 1].cost -= cars[jj].weight; //check this
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
        printf("File has too many arguments (%d lines), must limit to 35 lines.\n", num_lines);
        exit(0);
    }
    fclose(fp);
    return (num_lines - 1);
}


road_t find_path(road_t road, road_t new_road, road_t roads[], int num_roads_remaining)
{
    road_t path_opt[5];
    int jj = 0;
    switch(road.id) {
        case 'A':
            printf("Case A.\n");
            new_road = roads[5];
            break;
        case 'B':
            printf("Case B.\n");
            path_opt[0] = roads[6];
            path_opt[1] = roads[7];
            path_opt[2] = roads[8];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
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
            printf("Case F.\n");
            path_opt[0] = roads[12];
            path_opt[1] = roads[13];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'G':
            printf("Case G.\n");
            new_road = shortest_path(roads, roads[12], roads[13], 1, jj);
            break;
        case 'H':
            printf("Case H.\n");
            path_opt[0] = roads[18];
            path_opt[1] = roads[19];
            path_opt[2] = roads[20];
            path_opt[3] = roads[21];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 3, jj);
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
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'K':
            printf("Case K.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'L':
            printf("Case L.\n");
            path_opt[0] = roads[14];
            path_opt[1] = roads[15];
            path_opt[2] = roads[16];
            new_road = shortest_path(path_opt, path_opt[0], path_opt[1], 2, jj);
            break;
        case 'M':
            printf("Case M.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
            break;
        case 'N':
            printf("Case N.\n");
            new_road = roads[17];
            break;
        case 'O':
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
            break;
        case 'S':
            printf("Case S.\n");
            new_road = roads[17];
            break;
        case 'T':
            printf("Case T.\n");
            new_road = shortest_path(roads, roads[26], roads[27], 1, jj);
            break;
        case 'U':
            printf("Case U.\n");
            new_road = roads[30];
            break;
        case 'V':
            printf("Case V.\n");
            new_road = shortest_path(roads, roads[31], roads[32], 1, jj);
            break;
        case 'W':
            printf("Case W.\n");
            new_road = roads[30];
            break;
        case 'X':
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
            
    }
    return new_road;
}

