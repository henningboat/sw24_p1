//Lav djikstra :) :] :} (:
//tag udgangspunkt i pseudokoden på wikipedia

#include "path_finding.h"
#include <stdio.h>

#define length 7

struct route{
    int a;
    int b;
    int cost;
};

typedef struct route route;

void Dijkstra(){
    //Placeholder ruter (de rigtige skal hentes fra Henning/Joseph)
    route route_list[length] = {{1,2, 1},{2,3, 1},{0,1, 1},{5,6, 1},{3,4, 1},{6,7, 1},{4,5, 1}};
    int start_station; //Kan også kaldes "source"
    int end_station;
    //Array med de stationer vi skal tjekke
    int Q[length] = {1,1,1,1,1,1,1}; //Hvorfor har jeg sat alle vaerdier til 1?
    double dist[];//set to infinity (eller MEGET hoejt tal)
    int prev[length];
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



