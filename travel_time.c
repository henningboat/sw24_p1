#include <stdio.h>
#include <math.h>
#include "travel_time.h"

#include <assert.h>
#include <stdlib.h>

#include "structs.h"

#include "CuTest.h"

/*-------------------PROTOTYPES-----------------------*/
double acceleration_time_calculator(double start_or_end_speed, double cruise_speed, double acceleration);

double acceleration_distance_calculator(double start_speed, double end_speed, double acceleration);

double find_max_speed(double train, double connection);

void calculate_time_and_distance_acceleration(double *acceleration_time,
                                              double *acceleration_distance,
                                              double *deceleration_time,
                                              double *deceleration_distance,
                                              double acceleration,
                                              double deceleration,
                                              double start_speed,
                                              double end_speed,
                                              double cruise_speed);

/*----------------------------------------------------*/






/*::::::::::::::::::::::::::::..Functions..::::::::::::::::::::::::::::*/

double get_travel_time(const Train *train, const Connection *connection, double start_speed, double end_speed) {
    //LOCAL VARIABLES
    double cruise_speed = find_max_speed(train->max_speed, connection->max_speed);
    double acceleration_time = 0;
    double deceleration_time = 0;
    double ac_distance = 0;
    double dc_distance = 0;

    calculate_time_and_distance_acceleration(&acceleration_time,
                                             &ac_distance,
                                             &deceleration_time,
                                             &dc_distance,
                                             train->acceleration,
                                             train->deceleration,
                                             start_speed,
                                             end_speed,
                                             cruise_speed);


    while (ac_distance + dc_distance > connection->distance) {

        assert(cruise_speed>=1);
        cruise_speed /= 2.0;

        calculate_time_and_distance_acceleration(&acceleration_time,
                                                 &ac_distance,
                                                 &deceleration_time,
                                                 &dc_distance,
                                                 train->acceleration,
                                                 train->deceleration,
                                                 start_speed,
                                                 end_speed,
                                                 cruise_speed);
    }

    double dist = connection->distance - ac_distance - dc_distance;
    double cruiseTime = dist / cruise_speed;

    // adderer acc- og deceleration tiden for at finde korrekte tid
    double time = acceleration_time + deceleration_time + cruiseTime;

    assert(time > 0);
    return time;
}






void calculate_time_and_distance_acceleration(double *acceleration_time,
                                              double *acceleration_distance,
                                              double *deceleration_time,
                                              double *deceleration_distance,
                                              double acceleration,
                                              double deceleration,
                                              double start_speed,
                                              double end_speed,
                                              double cruise_speed) {

    *acceleration_time = acceleration_time_calculator(start_speed, cruise_speed, acceleration);
    *deceleration_time = acceleration_time_calculator(end_speed, cruise_speed, deceleration);

    *acceleration_distance = acceleration_distance_calculator(start_speed, cruise_speed, acceleration);
    *deceleration_distance = acceleration_distance_calculator(end_speed, cruise_speed, deceleration);
}

//Functionen regner distancen af accelerationen fra start til cruise_speed
double acceleration_distance_calculator(double start_speed, double end_speed, double acceleration) {
    double acceleration_distance = (pow(end_speed, 2) - pow(start_speed, 2)) / (2 * acceleration);
    return acceleration_distance;
}


double acceleration_time_calculator(double start_or_end_speed, double cruise_speed, double acceleration) {
    double acceleration_time = (cruise_speed - start_or_end_speed) / acceleration; //Regner ud accelerationstiden ud

    if (acceleration_time < 0) {
        //hvis det regnes deceleration vil det give en negativ værdi, så vi ganger det med -1
        acceleration_time *= -1;
        return acceleration_time;
    }

    return acceleration_time;
}


double find_max_speed(double train, double connection) {
    if (train > connection) {
        return connection;
    } else {
        return train;
    }
}


/*::::::::::::::::::::::::::TESTING FUNCTIONS::::::::::::::::::::::::::*/

void test_AccelerationTime(CuTest *tc) { // I want to test if it gets postive
    double actual = acceleration_time_calculator(0,180,-0.5);
    int expected = 360;
    CuAssertDblEquals(tc,expected,actual,0.01);
}

//const Train *train, const Connection *connection, double start_speed, double end_speed
void testing_get_travel_time(CuTest *tc) {

    /***Initialising Dummy Struct***/
    Train testTrain ={
        .name = "TestingTrain",
        .max_speed = 200.0,
        .acceleration = 0.5,
        .deceleration = 0.25
    };

    Connection testConnection = {
        .station_a_index = 0,
        .station_b_index = 1,
        .max_speed = 150.0,
        .distance = 5000.0,
        .fixed_time_cost = -1.0
    };
    /*******************************/


    double actual= get_travel_time(&testTrain,&testConnection,0,0);
    double expected= 245.83;
    CuAssertDblEquals(tc, expected,actual,0.75);




}
/*
void testing_cruiseSpeed_in_get_travel_time(CuTest *tc) {



}*/

CuSuite *test_calc_GetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite,test_AccelerationTime);
    SUITE_ADD_TEST(suite,testing_get_travel_time);


    return suite;
}
