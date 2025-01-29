#include "path_finding.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "travel_time.h"
#include "CuTest.h"

typedef struct route route;
int find_lowest_cost_station(const double* cost, const int* not_visited, const ModelData*model_data);
void assign_cost_to_neighbours(const ModelData*model_data, int current_station_index, const int* not_visited, double* cost, int* previous_station_index, int may_use_flight, double* speed_at_station, const Station* stations);
void print_path_finding_results(const ModelData *model_data, double *cost, double *speed_at_station, int *previous, int *current_station_index) ;


double get_total_travel_time(const Station *start, const Station *destination, const ModelData *model_data, int may_use_flights) {
#ifdef DEBUG_PRINT
    printf("PATH FINDING:\t\tComputing journey between %s and %s", start->name, destination->name);
    if (may_use_flights) {
        printf(" with planes.\n");
    }else {
        printf(" without planes.\n");
    }
#endif

    assert(start->index!=destination->index);

    int start_station_index = start->index;
    int end_station = destination->index;

    //Array med de stationer vi skal tjekke
    int* not_visited = malloc(sizeof(int)*model_data->num_stations);
    for (int i=0;i<model_data->num_stations;i++) {
        not_visited[i]=1;
    }

    double* cost = malloc(sizeof(double)*model_data->num_stations);
    double* speed_at_station = malloc(sizeof(double)*model_data->num_stations);
    int* previous = malloc(sizeof(int)*model_data->num_stations);

    for(int i = 0; i < model_data->num_stations; i++)
    {
        previous[i]=-1;
        speed_at_station[i] = 0;
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

#ifdef DEBUG_PRINT
            print_path_finding_results(model_data, cost, speed_at_station, previous, &current_station_index);
#endif

            free(not_visited);
            free(cost);
            free(speed_at_station);
            free(previous);

            return result;// stations[end_station].distance;
        }
        if(current_station_index==-1)
        {
            printf("Path finding could not reach end station. Skibidi");
            exit(EXIT_FAILURE);
        }
        assign_cost_to_neighbours(model_data, current_station_index, not_visited, cost, previous, may_use_flights, speed_at_station, model_data->stations);
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

void assign_cost_to_neighbours(const ModelData *model_data, int current_station_index, const int *not_visited, double *cost, int *
                               previous_station_index, int may_use_flight, double* speed_at_station, const Station* stations) {
    for(int connection_index = 0; connection_index < model_data->route_segment_count ; connection_index++)
    {
        RouteSegment current_route_segment = model_data->route_segments[connection_index];
        int other_station_index;
        if(current_route_segment.station_a_index==current_station_index)
        {
            other_station_index = current_route_segment.station_b_index;
        }
        else if(current_route_segment.station_b_index==current_station_index)
        {
            other_station_index = current_route_segment.station_a_index;
        }else
        {
            continue;
        }

        if(not_visited[other_station_index]==0) {
            continue;
        }

        double current_route_travel_time;
        int is_flight = current_route_segment.connection.fixed_time_cost != -1;

        //If
        if(is_flight && !may_use_flight) {
            continue;
        }

        double speed_at_other_station = stations[other_station_index].drive_through_speed;

        if(is_flight) {
            current_route_travel_time=current_route_segment.connection.fixed_time_cost;
        }else {
            current_route_travel_time = get_travel_time(&current_route_segment.train, &current_route_segment.connection, speed_at_station[current_station_index], speed_at_other_station);
        }



     //   printf("%s to %s: %lf minutes\n",model_data->stations[current_station_index].name, model_data->stations[other_station_index].name,current_route_travel_time/60);

        double new_cost = current_route_travel_time + cost[current_station_index];
        if(new_cost < cost[other_station_index]){
            cost[other_station_index] = new_cost;
            speed_at_station[other_station_index] = speed_at_other_station;

            previous_station_index[other_station_index] = current_station_index;
            // printf("Nabo:%f\n",stations[other_station_index].distance); //Koerer en gang
        }
    }
}

void print_path_finding_results(const ModelData *model_data, double *cost, double *speed_at_station, int *previous, int *current_station_index) {
    //print path for debugging
    while (*current_station_index!=-1) {
        printf("PATH FINDING:\t\t%s time: %.0fmin speed: %.0fm/s\n",model_data->stations[(*current_station_index)].name, cost[(*current_station_index)] / 60, speed_at_station[(*current_station_index)]);
        *current_station_index=previous[(*current_station_index)];
    }

    printf("\n");
}


/*::::::::::::::::::::::::::TESTING FUNCTIONS::::::::::::::::::::::::::*/

void test_FindLowestCost_AllUnvisited(CuTest *tc) {
    ModelData dummyModelData = {.num_stations = 5};
    double cost[] = {INFINITY, 10.0, 15.0, 5.0, INFINITY};
    int not_visited[] = {1, 1, 1, 1, 1};


    int actual = find_lowest_cost_station(cost, not_visited, &dummyModelData);
    int expected = 3;

    CuAssertIntEquals(tc, expected, actual);
}

void test_FindLowestCost_OneVisited(CuTest *tc) {
    ModelData dummyModelData = {.num_stations = 5};
    double cost[] = {INFINITY, 10.0, 15.0, 5.0, INFINITY};
    int not_visited[] = {1, 1, 1, 0, 1};


    int actual = find_lowest_cost_station(cost, not_visited, &dummyModelData);
    int expected = 1;


    CuAssertIntEquals(tc, expected, actual);
}



CuSuite *test_path_GetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_FindLowestCost_AllUnvisited);
    SUITE_ADD_TEST(suite, test_FindLowestCost_OneVisited);
    return suite;
}


