
#include <stdio.h>
#include "simulation_loop.h"


int main(void) {
    int number_of_trips;
    char model_data_path[PATH_STRING_LENGTH];

    printf("enter path to model data\n");
    scanf("%s", model_data_path);
    printf("enter number of trips to simulate\n");
    scanf("%d", &number_of_trips);

    run_simulation(number_of_trips, model_data_path);

    return 0;
}
