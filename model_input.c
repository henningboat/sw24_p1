#include "structs.h"
#include "model_input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_LEN 10000

Train read_train(char* str);
void print_train(Train train);
void string_split(char* text, char** sub_str, char a);
char* read_file(char* path);
void read_trains(Train* trains, int* num_trains);
Station read_station(char* str, int index);
void read_stations(Station* station, int* num_stations);
void print_station(Station station);
Connection read_connection(char* str, Station* stations, int num_stations);


void read_connections(Connection* connection, int* num_connections, Station* station, int num_stations);

ModelData get_model_data(void) {

        ModelData result;

        int num_trains;
        Train* trains= malloc(1000);
        read_trains(trains, &num_trains);
        result.trains = trains;
        result.num_trains = num_trains;

        Station* stations = malloc(1000);
        int num_stations;
        read_stations(stations, &num_stations);
        result.stations = stations;
        result.num_stations = num_stations;

        Connection* connections = malloc(10000);
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

void string_split(char* text, char** sub_str, char a)
{
    int i = 0;
    sub_str[0] = text;
    int sub_str_index = 1;

    while (1)
    {
        if (text[i] == '\0')
        {
            break;
        }
        if (text[i] == a)
        {
            text[i] = '\0';

            sub_str[sub_str_index] = text + i + 1;
            sub_str_index++;
        }
        i++;
    }
    sub_str[sub_str_index] = NULL;
}

Train read_train(char* str)
{
    char* sub_str[100];
    string_split(str, sub_str,';');
    Train train;
    train.name=(sub_str[0]);
    train.max_speed=atof(sub_str[1]);
    train.acceleration=atof(sub_str[2]);
    train.deceleration=atof(sub_str[3]);


    return train;
}

void print_train(Train train)
{
    printf("the trains name: %s\n and the trains max speed: %f\n and the trains acceleration: %f\n and the trains deceleration: %f\n",
        train.name, train.max_speed, train.acceleration, train.deceleration);
}

char* read_file(char* path)
{
    FILE *input_file_pointer;
    char* str = malloc(MAX_STR_LEN);
    int ch;
    int i = 0;

    input_file_pointer = fopen(path, "r");

    if (input_file_pointer != NULL){        /* File could be opened */
        while ((ch = fgetc(input_file_pointer)) != EOF){
            str[i] = ch;
            i++;
        }
        str[i] = '\0';

        printf("Read from file:\n %s\n", str);
        printf("\n");

        fclose(input_file_pointer);
    }

    else{
        printf("Could not open input file. Bye.");
        exit(EXIT_FAILURE);
    }

    return str;
}

void read_trains(Train* trains, int* num_trains) {

    char* sub_str[1000];
    int i=0;
    char* str = read_file("model_data/trains.txt");
    string_split(str,sub_str,'\n');

    while (1)
    {
        trains[i] = read_train(sub_str[i]);
        i++;
        if(sub_str[i]==NULL)
        {
            break;
        }
    }

    *num_trains = i;
}

void read_stations(Station* station, int* num_stations)
{
    char* sub_str[1000];
    int i=0;
    char* str = read_file("model_data/Stations.txt");
    string_split(str,sub_str,'\n');

    while (1)
    {
        station[i] = read_station(sub_str[i], i);
        i++;
        if(sub_str[i]==NULL)
        {
            break;
        }
    }

    *num_stations = i;
}

Station read_station(char* str, int index)
{
    char* sub_str[100];
    string_split(str, sub_str,';');
    Station station;
    station.name=(sub_str[0]);
    station.index=index;

    return station;
}

void print_station(Station station)
{
    printf("Name of station: %s\n", station.name);
}

Connection read_connection(char* str, Station* stations, int num_stations)
{
    char* sub_str[100];
    string_split(str, sub_str,';');
    Connection connection;

    for (int j = 0; j < num_stations; j++)
    {
        if (strcmp(sub_str[0], stations[j].name) == 0)
        {    connection.station_a_index= j;
            printf("station %s is equal to index number %d\n", stations[j].name, j);
        }

        if (strcmp(sub_str[1], stations[j].name) == 0)
        {   connection.station_b_index = j;
            printf("station %s is equal to index number %d\n", stations[j].name, j);
        }

    }

    connection.distance=atof(sub_str[2]);
    connection.max_speed=atof(sub_str[3]);
    return connection;
}

void read_connections(Connection* connections, int* num_connections, Station* stations, int num_stations)
{char* sub_str[1000];
    int i=0;
    char* str = read_file("model_data/connections.txt");
    string_split(str,sub_str,'\n');

    while (1)
    {
        connections[i] = read_connection(sub_str[i], stations, num_stations);
        i++;
        if(sub_str[i]==NULL)
        {
            break;
        }
    }

    *num_connections = i;
}
