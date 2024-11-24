#include <stdio.h>
#include <math.h>
#include "travel_time.h"
#include "structs.h"

/*-------------------PROTOTYPES-----------------------*/
double acceleration_time_calculator(double start_or_end_speed, double cruise_speed, double acceleration);

double acceleration_distance_calculator(double start_speed,double end_speed, double acceleration);

double find_max_speed(double train, double connection);

/*----------------------------------------------------*/


/*::::::::::::::::::::::::::::..Functions..::::::::::::::::::::::::::::*/

double get_travel_time(const Train *train, const Connection *connection, double start_speed, double end_speed) {
    double cruise_speed = find_max_speed(train->max_speed, connection->max_speed);

    //de næste to linjer finder accelerations tiden og decelerations tiden, som til cruiseTime
    double acceleration_time = acceleration_time_calculator(start_speed, cruise_speed, train->acceleration);
    double deceleration_time = acceleration_time_calculator(end_speed, cruise_speed, train->deceleration);

    //Samme princip finder distancen som bruges i at finde cruiseTime
    double ac_distance = acceleration_distance_calculator(start_speed,end_speed, train->acceleration);
    double dc_distance = acceleration_distance_calculator(start_speed,end_speed, train->deceleration);

    /*if(ac_distance+dc_distance>=connection->distance){
        return acceleration_time+deceleration_time;
    }*/

    double dist = connection->distance - ac_distance - dc_distance;

    //To find the time taken, we need to factor in ac- and deceleration time
    double cruiseTime = dist / cruise_speed;

    // adderer acc- og deceleration tiden for at finde korrekte tid
    double time = acceleration_time + deceleration_time + cruiseTime;


    return time;
}

//Functionen regner distancen af accelerationen fra start til cruise_speed
double acceleration_distance_calculator(double start_speed,double end_speed, double acceleration) {

    double acceleration_distance = (pow(end_speed,2)-pow(start_speed,2))/(2*acceleration);
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
