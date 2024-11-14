#include <stdio.h>
#include "path_finding.h"

struct route{
    int a;
    int b;
    int cost;
};

typedef struct route route;

void find_neighbours(route* first_route, route route_list [], route open_set[], route closed_set [], int j );
void print_neighboors(route fylde_navn[]);
// vi skal have en function som sender vores rute fra open set til closed set.
//

void test_path_finding (){

    route open_set [10000];
    int open_set_counter = 0;
    route closed_set [10000];
    int closed_set_counter = 0;
    int end_st = 6;
    int current_st = 0;
    route route_list[] = {{0,1, 1},{1,2, 1},{2,3, 1},{3,4, 1},{4,5, 1},{5,6, 1},{6,7, 1}}; //lav fuinction som kan scanne korrekt start i array selvom par ikke er sorteret.
    route first_route = route_list [0];
    route current_route = first_route;
    int j = 0;
    //KALD input funktion

    while (end_st != first_route.a &&
    end_st != first_route.b){
        find_neighbours(&first_route, route_list, open_set, closed_set, j);
        j++;
        printf("loops: %d \n", j);
        print_neighboors(open_set);
    }
    printf("%d \n", end_st);
    printf("%d %d \n", first_route.a, first_route.b);
}

void find_neighbours(route* first_route, route route_list [], route open_set[], route closed_set [], int j ){

    route potential_route;
    int i;
    int k = 0;
    //for løkke skal have en variable istedet for tallet 7.
    for (i = 0; i < 7; i++){
        potential_route = route_list[i];
        if((first_route->a == potential_route.a||
           first_route->a == potential_route.b||
           first_route->b == potential_route.a||
           (first_route->b == potential_route.b) && (first_route->a !=potential_route.a && first_route->b !=potential_route.b))
           ||(potential_route.a != closed_set[i].a && potential_route.b != closed_set[i].b)){


            //kalde compare open_set()
            open_set[k] = potential_route;
            k++;
            closed_set[j] = *first_route;
           }
    }

}

void print_neighboors(route fylde_navn[]){
    int i;
    for(i = 0; i < 7; i++){
        route fylde_navn2 = fylde_navn[i];
        printf("%d %d %d \n",fylde_navn2.a, fylde_navn2.b, fylde_navn2.cost);
    }
}