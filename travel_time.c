#include <stdio.h>
#include <math.h>
#include "travel_time.h"
#include "structs.h"
#include "structs.h"
/****************DEFINED CONSTANTS***************/

#define MAX_SPEED_1 50    //180.0 km/t = 50m/s
#define MAX_SPEED_2 200.0 // km/t

#define TIME_FACTOR 60.0  // omregner til minut

#define NAME_LENGTH 20  // allokerer 20 pladser i lageret til struct

#define KBH_RING_D  60000  //meters //rejseplan 30 min
#define RING_OD_D   102.0     //motorvejslængde fra google maps //rejseplan 45 min
#define OD_KOLD_D   68.0
#define KOLD_PAD_D  85.0
#define PAD_SCHL_D  47.0
#define SCHL_HAM_D  130.0

#define ACCELERATION 0.5 //1.2
#define DECELERATION 0.4 //1.1
#define START_SPEED 60
#define END_SPEED 0
/*----------------------------------------------------*/


/*-------------------PROTOTYPES-----------------------*/
double acceleration_time_calculator(double start_or_end_speed, double cruise_speed, double acceleration);

double acceleration_distance_calculator(double time, double acceleration);

double find_max_speed(double train, double connection);
/*----------------------------------------------------*/



/*::::::::::::::::::::::::::::..Functions..::::::::::::::::::::::::::::*/

double get_travel_time(const Train *train, const Connection *connection, double start_speed, double end_speed) {
    double cruise_speed = find_max_speed(train->max_speed, connection->max_speed);

    //de næste to linjer finder accelerations tiden og decelerations tiden, som til cruiseTime
    double acceleration_time = acceleration_time_calculator(start_speed, cruise_speed, train->acceleration);
    double deceleration_time = acceleration_time_calculator(end_speed, cruise_speed, train->deceleration);

    //Samme princip finder distancen som bruges i at finde cruiseTime
    double ac_distance = acceleration_distance_calculator(acceleration_time, train->acceleration);
    double dc_distance = acceleration_distance_calculator(deceleration_time, train->deceleration);

    double dist = connection->distance - ac_distance - dc_distance;

    //To find the time taken, we need to factor in ac- and deceleration time
    double cruiseTime = dist / cruise_speed;

    double time = acceleration_time + deceleration_time + cruiseTime;
    // adderer acc- og deceleration tiden for at finde korrekte tid

    return time;
}

//Functionen regner distancen af accelerationen fra start til cruise_speed
double acceleration_distance_calculator(double time, double acceleration) {
    double acceleration_stretch = 0.5 * acceleration * pow(time, 2);
    return acceleration_stretch;
}


double acceleration_time_calculator(double start_or_end_speed, double cruise_speed, double acceleration) {
    double acceleration_time = (cruise_speed - start_or_end_speed) / acceleration; //Regner ud accelerationstiden ud


    if (acceleration_time < 0) {
        //hvis det regnes deceleration vil det give en negativ værdi, så vi ganger det med -1
        acceleration_time *= -1;
        printf("i if statement : %lf\n", acceleration_time);

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
