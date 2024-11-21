//Lav djikstra :) :] :} (:
//tag udgangspunkt i pseudokoden på wikipedia

#include "path_finding.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define length 7

struct route{
    int a;
    int b;
    int cost;
};

typedef struct route route;

struct station
{
    int station_id;
    double distance;
};

typedef struct station station;

void Find_closest_station(station stations[], int *current_station, int not_visited[]);

void Find_neighbours(station stations[], int current_station, route route_list[], int visited[]);

void Dijkstra(){
    //Placeholder ruter (de rigtige skal hentes fra Henning/Joseph)
    route route_list[length] = {{1,2, 2},{2,3, 2},{0,1, 2},{5,6, 2},{3,4, 2},{6,7, 2},{4,5, 2}};
    int start_station = 0; //Kan også kaldes "source"
    int end_station = 2;
    //Array med de stationer vi skal tjekke
    int not_visited[length] = {1,1,1,1,1,1,1}; //on/off Kan forbedres, maybe
    double dist[100000];//set to infinity (eller MEGET hoejt tal)
    int prev[length];
    int current_station;
    int k = 0;

    //make it to a set. example:{0,0}
    station stations[length];
    stations[start_station].station_id = start_station;
    stations[start_station].distance = 0;

    for(int i = 0; i < length; i++)
    {
        if(i != start_station)
        {
            stations[i].station_id = i;
            stations[i].distance = INFINITY;
            printf("%d",i);
        }
    }
    printf("%f\n",stations[start_station].distance);
    //Lav et while loop
    while(1) //virker ikke ordentligt
    {
        Find_closest_station(stations, &current_station, not_visited);
        if(current_station == end_station)
        {
            return;// stations[end_station].distance;
        }
        if(current_station==-1)
        {
            break;
        }
        //printf("test");
        Find_neighbours(stations, current_station, route_list, not_visited);
        printf("test 2");
        not_visited[current_station] = 0;
        //printf("Test 3");
    }

}

void Find_closest_station(station stations[], int *current_station, int not_visited[]){

    int next_next_index=-1;
    double min_distance=INFINITY;

    for(int i = 0; i < length; i++)
    {
        if(not_visited[i] == 1)
        {
            if(stations[i].distance<min_distance)
            {
                next_next_index = i;
                min_distance = stations[i].distance;
            }
        }
    }

    *current_station = next_next_index;

    /*
    int safety = 0;
    int ending_loop = 0;
    for(int i = 0; 1; i++){ //infinite loop
        printf("test 5\n");
        for(int j = 0; j<length && visited[stations[i].station_id] != 0; j++){
            printf("test 6\n");

            if(stations[j].distance == i && visited[stations[j].station_id] != 0){ //potential error
                printf("test 7\n");
                *current_station = stations[j].station_id;
                ending_loop = 1;
                printf("Current:%d\n", *current_station);
                //Noget skal slutte funktionen

                if(*current_station == end_station) //fungerer ikke
                {
                    //To be decided
                    //print ruten eller kald en funktion der printer ruten
                    printf("Du har fundet slutstationen");
                }
                break;
            }
        }
        if(stations[i].distance == INFINITY || visited[stations[i].station_id] == 0){
            safety++;
        }
        if(safety == length){
            printf("Der er ikke nogle reachable stationer");
            *current_station = -1;
            return;
            //Skal aendres til at lukke hele programmet, og printe noget
        }
        if(ending_loop == 1)
        {
            break;
        }
    }*/
}

void Find_neighbours(station stations[], int current_station, route route_list[], int visited[])
{
    for(int i = 0; i<length ; i++)
    {
        route current_route = route_list[i];
        int other_station;
        if(current_route.a==current_station)
        {
            other_station = current_route.b;
        }
        else if(current_route.b==current_station)
        {
            other_station = current_route.a;
        }else
        {
            continue;
        }


        double new_distance = current_route.cost + stations[current_station].distance;
        //unvisited[i].station_id = route_list[i].b;
        if(new_distance < stations[other_station].distance){
            stations[other_station].distance =new_distance;
            printf("Nabo:%f\n",stations[other_station].distance); //Koerer en gang
        }
    }
}



/*  function Dijkstra(Graph, source): //Source = start_station

       create vertex priority queue Q

       dist[source] ← 0                          // Initialization
       Q.add_with_priority(source, 0)            // associated priority equals dist[·]

      for each vertex v in Graph.Vertices:
          dist[v] ← INFINITY
          prev[v] ← UNDEFINED
          add v to Q
      dist[source] ← 0

      while Q is not empty:
          u ← vertex in Q with minimum dist[u]
          remove u from Q

          for each neighbor v of u still in Q:
              alt ← dist[u] + Graph.Edges(u, v)
              if alt < dist[v]:
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]
*/



