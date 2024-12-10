#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STRING_LENGTH 200
#define PATH_STRING_LENGTH 500

typedef struct {
    char name[MAX_STRING_LENGTH];
    double max_speed;
    double acceleration;
    double deceleration;
}Train;

typedef struct {
    char name[MAX_STRING_LENGTH];
    int index;
    int population;
    int vehicle_stops_here;
    double drive_through_speed;
    int original_station_index;
}Station;

typedef struct
{
    int station_a_index;
    int station_b_index;
    double max_speed;
    double distance;
    //If this contains a value not equal to -1, we use this value in
    //path finding instead of calculating the travel time
    double fixed_time_cost;
}Connection;

typedef struct
{
    int station_a_index;
    int station_b_index;
    Train train;
    Connection connection;
    char train_route_name[MAX_STRING_LENGTH];
}RouteSegment;

typedef struct
{
    const Train* trains;
    int num_trains;
    const Station* stations;
    int num_stations;
    const Connection* connections;
    int connections_count;
    const RouteSegment* route_segments;
    int route_segment_count;
    int total_population;
}ModelData;

#endif