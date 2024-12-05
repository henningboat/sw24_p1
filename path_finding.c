#include "path_finding.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "travel_time.h"


typedef struct route route;
int find_lowest_cost_station(const double* cost, const int* not_visited, const ModelData*model_data);
void assign_cost_to_neighbours(const ModelData*model_data, int current_station_index, const int* not_visited, double* cost, int* previous_station_index, int may_use_flight);


double get_total_travel_time(const Station *start, const Station *destination, const ModelData *model_data, int may_use_flights) {
    //Placeholder ruter (de rigtige skal hentes fra Henning/Joseph)

    int start_station_index = start->index;
    int end_station = destination->index;
    //Array med de stationer vi skal tjekke
    int* not_visited = malloc(sizeof(int)*model_data->num_stations);
    for (int i=0;i<model_data->num_stations;i++) {
        not_visited[i]=1;
    }

    double* cost = malloc(sizeof(double)*model_data->num_stations);
    int* previous = malloc(sizeof(int)*model_data->num_stations);

    for(int i = 0; i < model_data->num_stations; i++)
    {
        previous[i]=-1;
        if(i == start_station_index)
        {
            cost[i] = 0;
        }else {
            cost[i] = INFINITY;
            //printf("%d",i);
        }
    }
    //printf("%f\n",stations[start_station_index].distance);
    while(1)
    {
        int current_station_index = find_lowest_cost_station(cost, not_visited, model_data);
        if(current_station_index == end_station) {
            double result = cost[current_station_index];
            free(not_visited);
            free(cost);

            //print path for debugging
            while (current_station_index!=-1) {
                printf("%s  ",model_data->stations[current_station_index].name);


                current_station_index=previous[current_station_index];
            }

            printf("\n");

            free(previous);

            return result;// stations[end_station].distance;
        }
        if(current_station_index==-1)
        {
            printf("Path finding could not reach end station. Skibidi");
            exit(EXIT_FAILURE);
        }
        assign_cost_to_neighbours(model_data, current_station_index, not_visited, cost, previous, may_use_flights);
        not_visited[current_station_index] = 0;
    }
}

int find_lowest_cost_station(const double* cost, const int* not_visited, const ModelData*model_data){

    int lowest_cost_index =- 1;
    double min_cost = INFINITY;

    for(int i = 0; i < model_data->num_stations; i++)
    {
        if(not_visited[i] == 1)
        {
            if(cost[i]<min_cost)
            {
                lowest_cost_index = i;
                min_cost = cost[i];
            }
        }
    }
    return lowest_cost_index;
}

void assign_cost_to_neighbours(const ModelData*model_data, int current_station_index, const int* not_visited, double* cost, int* previous_station_index, int* reached_by_connection_index, int may_use_flight) {
    for(int connection_index = 0; connection_index < model_data->connections_count ; connection_index++)
    {
        Connection current_connection = model_data->connections[connection_index];
        int other_station_index;
        if(current_connection.station_a_index==current_station_index)
        {
            other_station_index = current_connection.station_b_index;
        }
        else if(current_connection.station_b_index==current_station_index)
        {
            other_station_index = current_connection.station_a_index;
        }else
        {
            continue;
        }

        if(not_visited[other_station_index]==0) {
            continue;
        }

        double current_route_travel_time;
        int is_flight = current_connection.fixed_time_cost != -1;

        //If
        if(is_flight && !may_use_flight) {
            continue;
        }

        if(is_flight) {
            current_route_travel_time=current_connection.fixed_time_cost;
        }else {
            current_route_travel_time = get_travel_time(&model_data->trains[0], &current_connection, 0, 0);
        }
        printf("%s to %s: %lf minutes\n",model_data->stations[current_station_index].name, model_data->stations[other_station_index].name,current_route_travel_time/60);

        double new_cost = current_route_travel_time + cost[current_station_index];
        if(new_cost < cost[other_station_index]){
            cost[other_station_index] = new_cost;
            previous_station_index[other_station_index] = current_station_index;
            // printf("Nabo:%f\n",stations[other_station_index].distance); //Koerer en gang
        }
    }
}