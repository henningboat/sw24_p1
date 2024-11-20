#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STRING_LENGTH 100

typedef struct {
    char name[MAX_STRING_LENGTH];
    double max_speed;
    double acceleration;
    double deceleration;
}Train;

typedef struct {
    char name[MAX_STRING_LENGTH];
    int index;
}Station;

typedef struct
{
    int station_a_index;
    int station_b_index;
    double max_speed;
    double distance;
}Connection;

typedef struct
{
    const Train* trains;
    int num_trains;
    const Station* stations;
    int num_stations;
    const Connection* connections;
    int num_connections;
}ModelData;

#endif