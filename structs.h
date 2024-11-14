#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char* name;
    double max_speed;
    double acceleration;
    double deceleration;
}Train;

typedef struct {
    char* name;
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
    Train* trains;
    int num_trains;
    Station* stations;
    int num_stations;
    Connection* connections;
    int num_connections;
}ModelData;

#endif