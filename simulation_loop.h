#ifndef SIMULATION_LOOP_H
#define SIMULATION_LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "model_input.h"
#include "path_finding.h"

void run_simulation(int number_of_trips, const char *model_data_path);

#endif SIMULATION_LOOP_H