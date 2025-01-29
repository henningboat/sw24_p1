#include "structs.h"
#include "passenger_decision_making.h"
#include "simulation_loop.h"

int passenger_chooses_train(Passenger passenger, double without_plane_time, double with_plane_time) {
  return (without_plane_time / passenger.train_time_tolerance <= with_plane_time);
}