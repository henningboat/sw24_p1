#include "structs.h"
#include "model_input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_LEN 10000

void print_train(Train train);
void string_split(char* text, char** sub_str, char a);
void read_trains(Train* trains, int* num_trains);
void read_stations(Station* station, int* num_stations);
void print_station(Station station);
void read_connections(Connection* connection, int* num_connections, Station* station, int num_stations);

ModelData get_model_data(void) {

        ModelData result;

        int num_trains;
        Train* trains= malloc(100*sizeof(Train));
        read_trains(trains, &num_trains);
        result.trains = trains;
        result.num_trains = num_trains;

        Station* stations = malloc(100*sizeof(Station));
        int num_stations;
        read_stations(stations, &num_stations);
        result.stations = stations;
        result.num_stations = num_stations;

        Connection* connections = malloc(100*sizeof(Connection));
        int num_connections;
        read_connections(connections, &num_connections, stations, num_stations);
        result.connections = connections;
        result.num_connections = num_connections;

        print_train(trains[0]);
        printf("\n");
        print_train(trains[1]);
        printf("\n");

    for (int i=0;i<num_stations;i++)
    {
        print_station(stations[i]);
        printf("\n");
    }

    return result;
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
    while(fscanf(file, "%[^;];%lf;%lf;%lf\n", trains->name, &trains->max_speed, &trains->acceleration, &trains->deceleration)==4) {
        (*num_trains)++;
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

    while(fscanf(file, "%[^\n]\n", station->name)==1) {
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

    while (fscanf(file, "%[^;];%[^;];%lf;%lf\n",from_station, to_station, &track_length, &max_speed)==4)
    {
        int found_start = 0, found_stop = 0;
        for (int j = 0; j < num_stations; j++)
        {
            if (strcmp(from_station, stations[j].name) == 0)
            {    connections->station_a_index= j;
                printf("station %s is equal to index number %d\n", stations[j].name, j);
                found_start=1;
            }

            if (strcmp(to_station, stations[j].name) == 0)
            {   connections->station_b_index = j;
                printf("station %s is equal to index number %d\n", stations[j].name, j);
                found_stop=1;
            }

        }

        connections->distance=track_length;
        connections->max_speed=max_speed;

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
