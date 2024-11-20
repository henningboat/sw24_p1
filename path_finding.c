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

void Dijkstra(){
    //Placeholder ruter (de rigtige skal hentes fra Henning/Joseph)
    route route_list[length] = {{1,2, 1},{2,3, 1},{0,1, 1},{5,6, 1},{3,4, 1},{6,7, 1},{4,5, 1}};
    int start_station = 0; //Kan også kaldes "source"
    int end_station;
    //Array med de stationer vi skal tjekke
    int Q[length] = {1,1,1,1,1,1,1}; //Hvorfor har jeg sat alle vaerdier til 1?
    double dist[100000];//set to infinity (eller MEGET hoejt tal)
    int prev[length];

    //make it to a set. example:{0,0}
    station unvisited[length];
    unvisited[start_station].station_id = start_station;
    unvisited[start_station].distance = 0;
    for(int i = 0; i < length; i++)
    {
        if(i != start_station)
        {
            unvisited[i].station_id = i;
            unvisited[i].distance = INFINITY;
            printf("%d",i);
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



