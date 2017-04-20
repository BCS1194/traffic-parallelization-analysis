#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// We plan on implementing a linked list and using this structure for the final deliverable.
/*typedef*/
/*struct node_log {
    char node;                // The value or data stored in the node
    struct node_log * next;   // A reference to the next node, null for last node
};*/ /*node_t*/

struct car {
    int size;                 // Size of the car; standard is 1
    //struct node_log path;   // A record of the nodes visited by the car
};

struct road {
    int road_id;              // The number of the road
    int cost;                 // The weight cost of the road
    int size;                 // The current size of the road
    int capacity;             // The maximum possible size of the road
    char origin;              // The start node
    char destination;         // The end node, must match start node of next road chosen
    struct car cars[11];      // A list of the cars currently on this road
    char node;                // The value or data stored in the node
    struct node_log * next;   // A reference to the next node, null for last node
};

struct road shortest_path(struct road a, struct road b);
struct road shortest_path_three(struct road a, struct road b, struct road c);
struct road setup(struct road origin, struct road next_road, struct car car);

int simulation_one()
{
    struct car car1 = {1};
    car1.size = 1;

    // Initializes different roads to choose from.
    struct road a = { 1, 4, 4, 10, 'a', '0', {a.cars[10]}}; // Origin road
    struct road b = { 2, 3, 3, 10, 'b', '0', {b.cars[10]}}; // Origin road
    struct road c = { 3, 1, 1, 10, 'c', 'e', {c.cars[10]}};
    struct road d = { 4, 2, 2, 10, 'd', 'm', {d.cars[10]}};
    struct road e = { 5, 5, 5, 10, 'e', '0', {e.cars[10]}};
    struct road f = { 6, 7, 7, 10, 'f', '0', {f.cars[10]}};
    struct road g = { 7, 3, 3, 10, 'g', '0', {g.cars[10]}};
    struct road h = { 8, 4, 4, 10, 'h', '0', {h.cars[10]}};
    struct road i = { 9, 2, 2, 10, 'i', '0', {i.cars[10]}};
    struct road j = {10, 4, 4, 10, 'j', '0', {j.cars[10]}};
    struct road k = {11, 5, 5, 10, 'k', '0', {k.cars[10]}};
    struct road l = {12, 2, 2, 10, 'l', 'l', {l.cars[10]}}; // Destination road
    struct road m = {13, 4, 4, 10, 'm', 'm', {m.cars[10]}}; // Destination road

    // The cars initial choice to start on road a or b.
    if (a.cost < b.cost) {
        a.cars[0] = car1;
        a.cost += car1.size;
        a.origin = 'a';
        printf("Car 1 entered on road a\n");
    }
    else {
        b.cars[0] = car1;
        b.cost += car1.size;
        b.origin = 'b';
        printf("Car 1 entered on road b\n");
    }

    // Based on the previous road and the shortest path function, next road is chosen.
    if (a.cost > a.size) {
        struct road shortest = shortest_path_three(c, d, e);
        setup(a, shortest, car1);


        // If statement based on which road the shortest_path function chose.
        if (shortest.origin == 'c') {
            struct road next_road = h;
            shortest = setup(shortest, next_road, car1);

            next_road = m;
            shortest = setup(shortest, next_road, car1);
        }
        else if (shortest.origin == 'd') {
            struct road next_road = m;
            shortest = setup(shortest, next_road, car1);
        }
        else if (shortest.origin == 'e') {
            struct road next_road = shortest_path(i, j);
            shortest = setup(shortest, next_road, car1);


            // If statement based on which road the shortest_path function chose.
            if (shortest.origin == 'i') {
                struct road next_road = m;
                shortest = setup(shortest, next_road, car1);
            }
            else if (shortest.origin == 'j') {
                struct road next_road = l;
                shortest = setup(shortest, next_road, car1);
            }
        }
    }

    if (b.cost > b.size) { 
        struct road shortest = shortest_path(f, g);
        setup(b, shortest, car1);

        // If statement based on which road the shortest_path function chose.
        if (shortest.origin == 'f') {
            struct road next_road = shortest_path(i,j);
            shortest = setup(shortest, next_road, car1);

            if (shortest.origin == 'i') {
                struct road next_road = m;
                shortest = setup(shortest, next_road, car1);
            }
            else if (shortest.origin == 'j') {
                struct road next_road = l;
                shortest = setup(shortest, next_road, car1);
            }
        }
        else if (shortest.origin == 'g') {
            struct road next_road = k;
            shortest = setup(shortest, next_road, car1);

            if (shortest.origin == 'k') {
                struct road next_road = l;
                shortest = setup(shortest, next_road, car1);
            }
        }
    }
    return 0;
}

int main()
{
    simulation_one();
    return 0;
}

/********************************************************************
 * This function takes in two different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
struct road shortest_path(struct road a, struct road b)
{
    struct road shortest;
    if (a.cost < b.cost) {
        shortest = a;
    }
    else {
        shortest = b;
    }
    return shortest;
}

/********************************************************************
 * This function takes in three different roads and will choose the
 * cars next road based on the cost of traveling on each road, then
 * it will return the road with the lowest cost/shortest path.
 *******************************************************************/
struct road shortest_path_three(struct road a, struct road b, struct road c)
{
    struct road shortest;
    if (a.cost <= b.cost) {
        shortest = a;
        if (a.cost <= c.cost) {
            shortest = a;
        }
        else {
            shortest = c;
        }
    }
    else {
        shortest = b;
        if (b.cost <= c.cost) {
            shortest = b;
        }
        else {
            shortest = c;
        }
    }
    return shortest;
}

/********************************************************************
 * This function takes in the old road, the next_road, and the car and
 * will move the car from the old road to the new road and print
 * out a message for the user.
 *******************************************************************/
struct road setup(struct road origin, struct road next, struct car car)
{
    origin.destination  = next.origin;
    next.cars[0]        = car;
    origin.cost        -= car.size;
    next.cost          += car.size;
    
    if (next.origin == 'm' || next.origin == 'l')
        printf("Car 1 left road %c and reached its destination of road %c\n", origin.origin, next.origin);
    else
        printf("Car 1 left road %c and entered road %c\n", origin.origin, next.origin);
    return next;
}

