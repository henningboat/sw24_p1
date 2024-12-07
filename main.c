#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "model_input.h"
#include "path_finding.h"

const Station *get_random_station(const ModelData *model_data);

unsigned int get_random_number() {
    //It turns out that rand() returns a random number between 0 and MAX_RAND, which is defined differently
    //on different operating systems/compilers. On some windows computers, it turned out to be as low as
    //32.000.

    //in order to get a random 32 bit number that we can rely on, we just randomly set all 32 bits of an
    //unsigned int randomly to either 1 or zero. This ensures that our code works with any compiler

    unsigned int random_number = 0;
    for (int i= 0;i<32; i++) {
        if (rand()%2==0) {
            random_number|=1<<i;
        }
    }

    return random_number;
}

const Station *get_random_station(const ModelData *model_data) {
    unsigned int random_number = get_random_number() % model_data->total_population;

    for (int i = 0; i < model_data->num_stations; i++) {
        const Station *station = &model_data->stations[i];
        if (random_number <= station->population) {
            return station;
        } else {
            random_number -= station->population;
        }
    }


    printf("Random city selector ran through all stations, this is not supposed to happen. Program will be aborted :(");
    exit(EXIT_FAILURE);
}

void run_passenger_simulation(int *trips_by_train, int *trips_by_plane, ModelData *model_data) {
    const Station *a = get_random_station(model_data);
    const Station *b;
    do {
        b = get_random_station(model_data);
    } while (a == b);

    double without_flights_time = get_total_travel_time(a, b, model_data, 0);
    double with_flights_time = get_total_travel_time(a, b, model_data, 1);

    if (with_flights_time < without_flights_time) {
        (*trips_by_plane)++;
    } else {
        (*trips_by_train)++;
    }
}

int main(void) {

    srand(time(NULL));


    ModelData model_data = get_model_data();

    int trips_by_train=0;
    int trips_by_plane=0;

    int trip_count = 1000000;

    for (int i = 0;i<trip_count;i++) {
        run_passenger_simulation(&trips_by_train, &trips_by_plane, &model_data);
    }

    printf("Plane ration: %lf percent (Trips by train: %i  Trips by plane: %i)", ((double)trips_by_plane/(double)trip_count) * 100, trips_by_train, trips_by_plane);

    return 0;
}
