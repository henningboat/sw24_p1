#include "structs.h"
#include "model_input.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_LEN 10000

void print_train(Train train);
void read_trains(Train* trains, int* num_trains);
void read_stations(Station* station, int* num_stations);
void print_station(Station station);
void read_connections(Connection* connection, int* num_connections, Station* station, int num_stations);
double km_to_meter(double km);
double kmh_to_meters_per_second(double kmt);


ModelData get_model_data(void) {
    ModelData result;

    int num_trains = 0;
    Train* trains= malloc(100*sizeof(Train));
    read_trains(trains, &num_trains);
    result.trains = trains;
    result.num_trains = num_trains;

    Station* stations = malloc(100*sizeof(Station));
    int num_stations = 0;
    read_stations(stations, &num_stations);
    result.stations = stations;
    result.num_stations = num_stations;

    result.total_population = 0;
    for (int i=0;i<result.num_stations;i++) {
        result.total_population+=result.stations[i].population;
    }

    Connection* connections = malloc(100*sizeof(Connection));
    int num_connections = 0;
    read_connections(connections, &num_connections, stations, num_stations);
    result.connections = connections;
    result.connections_count = num_connections;


    return result;
}

const Station* get_station_by_name(char *name, const ModelData *model_data) {
    for (int i=0; i<model_data->num_stations;i++) {
        if(strcmp(name, model_data->stations[i].name) == 0 ) {
            return &model_data->stations[i];
        }
    }

    printf("Could not find station %s, program will terminate", name);
    exit(EXIT_FAILURE);
}

void print_train(Train train)
{
    printf("the trains name: %s\n and the trains max speed: %f\n and the trains acceleration: %f\n and the trains deceleration: %f\n",
        train.name, train.max_speed, train.acceleration, train.deceleration);
}

void read_trains(Train* trains, int* num_trains) {

    FILE *file;
    file = fopen("model_data/trains.txt", "r");

    if(file==NULL) {
        exit(EXIT_FAILURE);
    }
    double train_speed_kmh;
    while(fscanf(file, "%[^;];%lf;%lf;%lf\n", trains->name, &train_speed_kmh, &trains->acceleration, &trains->deceleration)==4) {
        (*num_trains)++;
        trains->max_speed=kmh_to_meters_per_second(train_speed_kmh);
        trains++;
    }
    fclose(file);
}

void read_stations(Station* station, int* num_stations)
{
    FILE *file;
    file = fopen("model_data/stations.txt", "r");

    if(file==NULL) {
        exit(EXIT_FAILURE);
    }

    while(fscanf(file, "%[^;];%d\n", station->name, &station->population)==2) {
        station->index=*num_stations;

        (*num_stations)++;
        station++;
    }

    fclose(file);
}

void print_station(Station station)
{
    printf("Name of station: %s\n", station.name);
}

double convert_minutes_to_seconds(double fixed_time_cost_seconds);

void read_connections(Connection* connections, int* num_connections, Station* stations, int num_stations)
{
    FILE *file;
    file = fopen("model_data/connections.txt", "r");

    if(file==NULL) {
        exit(EXIT_FAILURE);
    }

    char from_station[100];
    char to_station[100];
    double track_length;
    double max_speed;
    double fixed_time_cost_seconds;

    while (fscanf(file, "%[^;];%[^;];%lf;%lf;%lf\n",from_station, to_station, &max_speed, &track_length, &fixed_time_cost_seconds)==5)
    {
        int found_start = 0, found_stop = 0;
        for (int j = 0; j < num_stations; j++)
        {
            if (strcmp(from_station, stations[j].name) == 0)
            {    connections->station_a_index= j;
                //printf("station %s is equal to index number %d\n", stations[j].name, j);
                found_start=1;
            }

            if (strcmp(to_station, stations[j].name) == 0)
            {   connections->station_b_index = j;
               // printf("station %s is equal to index number %d\n", stations[j].name, j);
                found_stop=1;
            }

        }
        track_length = km_to_meter(track_length);
        max_speed = kmh_to_meters_per_second(max_speed);

        connections->distance=track_length;
        connections->max_speed=max_speed;

        if(fixed_time_cost_seconds==-1) {
            connections->fixed_time_cost=-1;
        }else {
            connections->fixed_time_cost=convert_minutes_to_seconds(fixed_time_cost_seconds);
        }

        if(!found_start) {
            printf("Could not find start station %s when reading connection. Make sure the station is present in stations.txt.", from_station);
            exit(EXIT_FAILURE);
        }
        if(!found_stop) {
            printf("Could not find end station %s when reading connection. Make sure the station is present in stations.txt.", to_station);
            exit(EXIT_FAILURE);
        }

        (*num_connections)++;
        connections++;
    }
    fclose(file);

}

double km_to_meter(double km)
{
    double meter = 1000 * km;

    return meter;
}

double kmh_to_meters_per_second(double kmt)
{
    double ms = kmt/3.6;

    return ms;
}

double convert_minutes_to_seconds(double seconds) {
    return seconds * 60;
}

