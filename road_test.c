#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//linked list
/*typedef*/
struct node_log {
    char node;               // The value or data stored in the node
    struct node_log * next;  // A reference to the next node, null for last node
} /*node_t*/;

struct car {
    //int speed;
    int size;                //size of the car; standard is 1
    struct node_log path;    //a record of the nodes visited by the car
};

struct road {
    int road_id;        //the number of the road
    int cost;           //the weight cost of the road
    int size;           //the current size of the road
    int capacity;       //the maximum possible size of the road
    char origin;        //the start node
    char destination;   //the end node, must match the start node of the next road to be joined
    struct car cars[10];  //a list of the cars currently on this road
  char node;                // The value or data stored in the node
  struct node_log * next;   // A reference to the next node, null for last node
} /*node_t*/;


struct road shortest_path(struct road a, struct road b, struct road c);

int simulation_one()
{
    struct car car1 = {1};
    car1.size = 1;
    char temp;
    
    struct road a = { 1, 4, 0, 10, 'a', '0', a.cars[10]};
    struct road b = { 2, 3, 0, 10, 'b', '0', b.cars[10]};
    struct road c = { 3, 6, 0, 10, 'c', 'e', c.cars[10]};
    struct road d = { 4, 2, 0, 10, 'd', 'm', d.cars[10]};
    struct road e = { 5, 5, 0, 10, 'e', '0', e.cars[10]};
    struct road f = { 6, 7, 0, 10, 'f', '0', f.cars[10]};
    struct road g = { 7, 3, 0, 10, 'g', '0', g.cars[10]};
    struct road h = { 8, 4, 0, 10, 'h', '0', h.cars[10]};
    struct road i = { 9, 2, 0, 10, 'i', '0', i.cars[10]};
    struct road j = {10, 4, 0, 10, 'j', '0', j.cars[10]};
    struct road k = {11, 5, 0, 10, 'k', '0', k.cars[10]};
    struct road l = {12, 2, 0, 10, 'l', '0', l.cars[10]};
    struct road m = {13, 4, 0, 10, 'm', '0', m.cars[10]};
    struct road z = {26, 100, 0, 10, 'z', '0', z.cars[10]};
    
    
    //the cars initial choice to start on road a or b
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
    
    
    
    
    //Based on the previous road and the shortest path function, the car chooses its next road
    if (a.cost > 4) {
        struct road shortest = shortest_path(c, d, e);
        a.destination        = shortest.origin;
        shortest.cars[0]       = car1;
        a.cost              -= car1.size;
        shortest.cost       += car1.size;
    
        printf("Car 1 left road a and entered road %c\n", shortest.origin);
        if (shortest.origin == 'c') {
            struct road next_road = h;
            shortest.destination  = next_road.origin;
            shortest.cars[0]      = car1;
            shortest.cost        -= car1.size;
            next_road.cost       += car1.size;
      
        }
        else if (shortest.origin == 'd') {
            struct road next_road = m;
            shortest.destination  = next_road.origin;
            shortest.cars[0]      = car1;
            shortest.cost        -= car1.size;
            next_road.cost       += car1.size;
        }
        else if (shortest.origin == 'e') {
            struct road next_road = shortest_path(i, j, z);
            shortest.destination  = next_road.origin;
            shortest.cars[0]      = car1;
            shortest.cost        -= car1.size;
            next_road.cost       += car1.size;
        }
    }
  
    if (b.cost > 3) {
        struct road shortest = shortest_path(f, g, z);
        b.destination        = shortest.origin;
        shortest.cars[0]     = car1;
        b.cost              -= car1.size;
        shortest.cost       += car1.size;
    
        printf("Car 1 left road b and entered road %c\n", shortest.origin);
        
        if (shortest.origin == 'f') {
            struct road next_road = shortest_path(i,j,z);
            shortest.destination  = next_road.origin;
            shortest.cars[0]      = car1;
            shortest.cost        -= car1.size;
            next_road.cost       += car1.size;
            printf("Car 1 left road %c and entered road %c\n", shortest.origin, next_road.origin);
      
            //if road i was chosen, the next road is....
            if (shortest.origin == 'i') {
                struct road next_road = m;
                shortest.destination  = next_road.origin;
                shortest.cars[0]      = car1;
                shortest.cost        -= car1.size;
                next_road.cost       += car1.size;
                printf("Car 1 left road %c and reached its destination of road %c\n", shortest.origin, next_road.origin);
            }
            //if road j was chosen, the next road is....
            else if (shortest.origin == 'j') {
                struct road next_road = l;
                shortest.destination  = next_road.origin;
                shortest.cars[0]      = car1;
                shortest.cost        -= car1.size;
                next_road.cost       += car1.size;
                printf("Car 1 left road %c and reached its destination of road %c\n", shortest.origin, next_road.origin);
            }
        }
        else if (shortest.origin == 'g') {
            struct road next_road = k;
            shortest.destination  = next_road.origin;
            shortest.cars[0]      = car1;
            shortest.cost        -= car1.size;
            next_road.cost       += car1.size;
            printf("Car 1 left road %c and entered road %c\n", shortest.origin, next_road.origin);
            if (next_road.origin == 'k') {
                struct road next_road = l;
                shortest.destination  = next_road.origin;
                shortest.cars[0]      = car1;
                shortest.cost        -= car1.size;
                next_road.cost       += car1.size;
                printf("Car 1 left road %c and reached its destination of road %c\n", shortest.origin, next_road.origin);
            }
            //road g's next set of road choices
            
        }
    }
    return 0;

}




int main()
{
    simulation_one();
    return 0;
}


struct road shortest_path(struct road a, struct road b, struct road c)
{
    struct road shortest;
    if (a.cost < b.cost) {
        shortest = a;
        if (a.cost < c.cost) {
            shortest = a;
        }
        else {
            shortest = c;
        }
    }
    else {
        shortest = b;
        if (b.cost < c.cost) {
            shortest = b;
        }
        else {
            shortest = c;
        }
    }
    return shortest;
}

