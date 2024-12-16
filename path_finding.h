#ifndef PATH_FINDING_H
#define PATH_FINDING_H
#include "CuTest.h"
#include "structs.h"
void Dijkstra();
double get_total_travel_time(const Station * start, const Station * destination, const ModelData * model_data, int may_use_flight);
CuSuite *test_path_GetSuite();
#endif PATH_FINDING_H