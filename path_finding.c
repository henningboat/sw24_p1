//Lav djikstra :) :] :} (:
//tag udgangspunkt i pseudokoden på wikipedia

#include "path_finding.h"
#include <stdio.h>
#include <math.h>

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

void Find_closest_station(station unvisited[], int *current_station, int end_station, int visited[]);

void Find_neighbours(station unvisited[], int current_station, route route_list[], int visited[]);

void Dijkstra(){
    //Placeholder ruter (de rigtige skal hentes fra Henning/Joseph)
    route route_list[length] = {{1,2, 1},{2,3, 1},{0,1, 1},{5,6, 1},{3,4, 1},{6,7, 1},{4,5, 1}};
    int start_station = 0; //Kan også kaldes "source"
    int end_station;
    //Array med de stationer vi skal tjekke
    int visited[length] = {1,1,1,1,1,1,1}; //on/off Kan forbedres, maybe
    double dist[100000];//set to infinity (eller MEGET hoejt tal)
    int prev[length];
    int current_station;
    int k = 0;

    //make it to a set. example:{0,0}
    station unvisited[length];
    unvisited[start_station].station_id = start_station;
    unvisited[start_station].distance = 0;

    //Lav et while loop
    for(int i = 0; i < length; i++)
    {
        if(i != start_station)
        {
            unvisited[i].station_id = i;
            unvisited[i].distance = INFINITY;
            printf("%d",i);
        }
    }
    Find_closest_station(unvisited, &current_station, end_station, visited);
    Find_neighbours(unvisited, current_station, route_list, visited);
    visited[current_station] = 0;

}

void Find_closest_station(station unvisited[], int *current_station, int end_station, int visited[]){
    int safety = 0;
    for(int i = 0; 1; i++){
        for(int j = 0; j<length && visited[unvisited[j].station_id] != 0; j++){
            if(unvisited[j].distance == i){
                *current_station = unvisited[j].station_id;
                if(*current_station == end_station)
                {
                    //To be decided
                }
                break;
            }
        }
        if(unvisited[i].distance == INFINITY || visited[unvisited[i].station_id] == 0){
            safety++;
        }
        if(safety == length){
            break;
            //Skal aendres til at lukke hele programmet, og printe noget
        }
    }

}

void Find_neighbours(station unvisited[], int current_station, route route_list[], int visited[])
{
    for(int i = 0; i<length && visited[unvisited[i].station_id] != 0; i++)
    {
        if(current_station == route_list[i].a)
        {
            //unvisited[i].station_id = route_list[i].b;
            if(route_list[i].cost + unvisited[current_station].distance < unvisited[i].distance)
            {
                unvisited[route_list[i].b].distance = route_list[i].cost + unvisited[current_station].distance;
            }
        }
        if(current_station == route_list[i].b)
        {
            //unvisited[i].station_id = route_list[i].a;
            if(route_list[i].cost + unvisited[current_station].distance < unvisited[i].distance)
            {
                unvisited[route_list[i].a].distance = route_list[i].cost + unvisited[current_station].distance;
            }
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



