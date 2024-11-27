#ifndef PATH_FINDING_H
#define PATH_FINDING_H
#include "structs.h"

void Dijkstra();
double get_total_travel_time(const Station * start, const Station * destination, const ModelData * model_data);

#endif PATH_FINDING_H