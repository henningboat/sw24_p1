#include "path_finding.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define length 7

//Skal hentes fra structs.h i stedet
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
    int start_station = 0;
    int end_station = 2;
    //Array med de stationer vi skal tjekke
    int not_visited[length] = {1,1,1,1,1,1,1};
    int current_station;

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
    while(1)
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
        Find_neighbours(stations, current_station, route_list, not_visited);
        not_visited[current_station] = 0;
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
        if(new_distance < stations[other_station].distance){
            stations[other_station].distance =new_distance;
            printf("Nabo:%f\n",stations[other_station].distance); //Koerer en gang
        }
    }
}