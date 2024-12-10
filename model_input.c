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
void read_route_segments(RouteSegment* route_segment, int* num_route_segments, Station* stations, int* num_stations, Connection* connections, int num_connections, Train* trains, int num_trains);


ModelData get_model_data(void) {
    ModelData result;

    int num_trains = 0;
    Train* trains= malloc(1000*sizeof(Train));
    read_trains(trains, &num_trains);
    result.trains = trains;
    result.num_trains = num_trains;

    Station* stations = malloc(1000*sizeof(Station));
    int num_stations = 0;
    read_stations(stations, &num_stations);
    result.stations = stations;


    Connection* connections = malloc(1000*sizeof(Connection));
    int num_connections = 0;
    read_connections(connections, &num_connections, stations, num_stations);
    result.connections = connections;
    result.connections_count = num_connections;

    RouteSegment* route_segments=malloc(1000*sizeof(RouteSegment));
    int num_route_segments = 0;

    read_route_segments(route_segments, &num_route_segments,stations, &num_stations, connections, num_connections,trains,num_trains);

    result.num_stations = num_stations;


    result.total_population = 0;
    for (int i=0;i<result.num_stations;i++) {
        result.total_population+=result.stations[i].population;
    }

    result.route_segments=route_segments;
    result.route_segment_count=num_route_segments;

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
        station->drive_through_speed = 0;
        station->vehicle_stops_here = 1;
        station->original_station_index=station -> index;

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

void assert(int value, const char* error_message) {
    if (!value) {
        printf("assertion failed. Error message: ");
        printf(error_message);
        exit(EXIT_FAILURE);
    }
}

void read_connections(Connection* connections, int* num_connections, Station* stations, int num_stations) {
    FILE *file;
    file = fopen("model_data/connections.txt", "r");

    if(file==NULL) {
        exit(EXIT_FAILURE);
    }

    char from_station[MAX_STRING_LENGTH];
    char to_station[MAX_STRING_LENGTH];
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


Connection find_connection(int station_a_index,int station_b_index,  Connection* connections, int num_connections) {
    for (int i = 0;i < num_connections;i++) {
        Connection connection = connections[i];

        if (station_a_index==connection.station_a_index&&station_b_index == connection.station_b_index) {
            return connection;
        }
        if (station_b_index==connection.station_a_index&&station_a_index == connection.station_b_index) {
            return connection;
        }
    }

    assert(0, "Could not find connection");
}

Station get_station_index(char* station_name, Station* stations, int num_stations) {
    for (int i=0;i<num_stations;i++) {
        if (strcmp(stations[i].name, station_name)==0) {
            return stations[i];
        }
    }
    assert(0,"lol");
}

void read_route_segments(RouteSegment* route_segment, int* num_route_segments, Station* stations, int* num_stations, Connection* connections, int num_connections, Train* trains, int num_trains) {
    FILE *file;
    file = fopen("model_data/train_routes.txt", "r");

    if(file==NULL) {
        exit(EXIT_FAILURE);
    }

    int last_char = fgetc(file);
    while (!feof(file))
    {
        char train_route_name[MAX_STRING_LENGTH];
        char train_model_name[MAX_STRING_LENGTH];
        fscanf(file,"%[^;];%[^;];", train_route_name, train_model_name);
      //  printf("route: %s %s. Stations: ", train_route_name, train_model_name);


        int train_found = 0;
        for (int i=0; i<num_trains;i++) {
            if (strcmp(trains[i].name, train_model_name)==0) {
                route_segment->train = trains[i];
                train_found=1;
            }
        }

        assert(train_found, "Train was not found");
        int stops_at_station;
        char first_station_name[MAX_STRING_LENGTH];
        fscanf(file, "%[^;];%i;", first_station_name, &stops_at_station);

        assert(stops_at_station, "A train route must stop at it's first station");

        Station from_station = get_station_index(first_station_name, stations, *num_stations);

        while (1) {
            char to_station_name[MAX_STRING_LENGTH];
            fscanf(file, "%[^;];%i", to_station_name, &stops_at_station);

            Station to_station = get_station_index(to_station_name, stations, *num_stations);

            Connection connection = find_connection(from_station.original_station_index, to_station.index,connections, num_connections);
            route_segment->connection = connection;

            if (!stops_at_station) {
                //If we don't stop at the next station, we create a new "drive through station"
                int new_station_index = *num_stations;

                char new_station_name[MAX_STR_LEN] = "";
                strcpy(new_station_name, to_station.name);
                strcpy(&new_station_name[strlen(to_station.name)], " (Drive Through)");


                to_station = (Station){.name="", .index=new_station_index, .population=0,.vehicle_stops_here=0,.drive_through_speed=kmh_to_meters_per_second(120), .original_station_index=to_station.index};
                strcpy(&to_station.name[0], new_station_name);

                stations[new_station_index]=to_station;
                (*num_stations)++;
            }

            route_segment->station_a_index =from_station.index;
            route_segment->station_b_index = to_station.index;


            from_station=to_station;

            (*num_route_segments)++;
            route_segment++;

            last_char= fgetc(file);
            if (last_char=='\n' || last_char==EOF) {
                break;
            }
        }
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

