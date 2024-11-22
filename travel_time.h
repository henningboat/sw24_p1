#ifndef TRAVEL_TIME_H
#define TRAVEL_TIME_H
#include "structs.h"

double get_travel_time(const Train *train, const Connection *connection, double start_speed, double end_speed);

#endif