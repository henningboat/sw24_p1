#include "simulation_loop.h"
#include "passenger_decision_making.h"
#include "trip_generation.h"

void run_passenger_simulation(int *trips_by_train, int *trips_by_plane, const ModelData *model_data) {
    Passenger passenger = generate_passenger(model_data);

    #ifdef DEBUG_PRINT
    printf("SIMULATION LOOP:\tComparing trips between %s and %s\n", passenger.start->name, passenger.destination->name);
    #endif

    double without_flights_time = get_total_travel_time(passenger.start, passenger.destination, model_data, 0);
    double with_flights_time = get_total_travel_time(passenger.start, passenger.destination, model_data, 1);

    if (passenger_chooses_train(passenger, without_flights_time, with_flights_time)) {
        (*trips_by_train)++;
#ifdef DEBUG_PRINT
        printf("SIMULATION LOOP:\t Train was faster\n\n");
#endif
    } else {
        (*trips_by_plane)++;
#ifdef DEBUG_PRINT
        printf("SIMULATION LOOP:\t Plane was faster\n\n");
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