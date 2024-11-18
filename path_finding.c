//Lav djikstra :) :] :} (:
//tag udgangspunkt i pseudokoden på wikipedia

#include "path_finding.h"
#include <stdio.h>

struct route{
    int a;
    int b;
    int cost;
};

typedef struct route route;

void Dijkstra()
{
    route route_list[] = {{1,2, 1},{2,3, 1},{0,1, 1},{5,6, 1},{3,4, 1},{6,7, 1},{4,5, 1}};
    int start_station;
    int end_station;
    int Q[] = {1,1,1,1,1,1,1};
    int dist[];
    int prev[];

}

/*  function Dijkstra(Graph, source):
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



