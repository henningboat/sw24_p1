﻿#include "structs.h"
#include "passenger_decision_making.h"
#include "simulation_loop.h"

int passenger_chooses_train(Passenger passenger, double without_train_time, double with_train_time) {
  return without_train_time / passenger.train_time_tolerance <= with_train_time;
}