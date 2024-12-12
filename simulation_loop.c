#include "simulation_loop.h"
#include "passenger_decision_making.h"

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

void run_passenger_simulation(int *trips_by_train, int *trips_by_plane, const ModelData *model_data) {
    const Station *start = get_random_station(model_data);
    const Station *destination;
    do {
        destination = get_random_station(model_data);
    } while (start == destination);

    Passenger passenger = generate_passenger();

    #ifdef DEBUG_PRINT
    printf("SIMULATION LOOP:\tComparing trips between %s and %s\n", start->name, destination->name);
    #endif

    double without_flights_time = get_total_travel_time(start, destination, model_data, 0);
    double with_flights_time = get_total_travel_time(start, destination, model_data, 1);

    if (passenger_chooses_train(passenger, without_flights_time, with_flights_time)) {
        (*trips_by_train)++;
#ifdef DEBUG_PRINT
        printf("SIMULATION LOOP:\t Plane was faster\n\n");
#endif
    } else {
        (*trips_by_plane)++;
#ifdef DEBUG_PRINT
        printf("SIMULATION LOOP:\t Plane was not faster\n\n");
#endif
    }
}

void run_simulation(int number_of_trips, const char * model_data_path) {
    srand(time(NULL));

    ModelData model_data = get_model_data(model_data_path);

    int trips_by_train=0;
    int trips_by_plane=0;

    printf("Running simulation for %d trips\n\n", number_of_trips);

    for (int i = 0;i<number_of_trips;i++) {
        run_passenger_simulation(&trips_by_train, &trips_by_plane, &model_data);
    }

    printf("Plane ratio: %0.1lf percent (Trips by train: %i  Trips by plane: %i)", ((double)trips_by_plane/(double)number_of_trips) * 100, trips_by_train, trips_by_plane);
}