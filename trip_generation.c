#include "trip_generation.h"

#include <stdio.h>

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

Passenger generate_passenger(const ModelData *model_data) {
    Passenger passenger;

     const Station *start = get_random_station(model_data);
     const Station *destination;
    do {
        destination = get_random_station(model_data);
    } while (start == destination);

    double train_journey_tolerance = 1 + 0.75 * ( get_random_number() %100000 )/ (double)100000;
    passenger.start = start;
    passenger.destination = destination;

    passenger.train_time_tolerance=train_journey_tolerance;

    return passenger;
}