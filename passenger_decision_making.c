#include "structs.h"
#include "passenger_decision_making.h"
#include "simulation_loop.h"

Passenger generate_passenger(){
  double train_journey_tolerance = 1 + 0.75 * ( get_random_number() %100000 )/ (double)100000;
  Passenger passenger;
  passenger.train_time_tolerance=train_journey_tolerance;
  return passenger;
}


int passenger_chooses_train(Passenger passenger, double without_train_time, double with_train_time) {
  return without_train_time / passenger.train_time_tolerance <= with_train_time;
}