#include <stdio.h>
#include <math.h>


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

/*-----------------------------------------------*/


/*********************STRUCTS********************/

typedef struct  {
    char route[NAME_LENGTH + 1];
    double time;
}route_time;

/*-----------------------------------------------*/


/*****************PROTOTYPES**********************/

double get_travel_time(double dist, double speed, double acceleration,double deceleration);
double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration);
double acceleration_distance_calculator(double time ,double acceleration);
/*-----------------------------------------------*/


int main(void) {

    /*TODO
     *Station Stops
     *Emissions
     */


    printf("Minutter fra KBH til RING ved 50m/s %0.2lf secs og afstanden %dm \n",
            get_travel_time(KBH_RING_D, MAX_SPEED_1,ACCELERATION,DECELERATION), KBH_RING_D);
    return 0;
}

double get_travel_time(double dist, double speed, double acceleration,double deceleration) {

    double acceleration_time = acceleration_time_calculator(0,speed,acceleration);
    double deceleration_time =acceleration_time_calculator(0,speed,deceleration);

    double ac_distance = acceleration_distance_calculator(acceleration_time, acceleration);
    double dc_distance = acceleration_distance_calculator(deceleration_time, acceleration);

    dist = dist-ac_distance-dc_distance;//To find the time taken, we need to factor in ac- and deceleration time
    double cruiseTime = dist/speed;

    double time = acceleration_time+deceleration_time+cruiseTime;

    return time;
}

double acceleration_distance_calculator(double time ,double acceleration) {
    double acceleration_stretch = 0.5 * acceleration * pow(time,2);
    return acceleration_stretch;
}


double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration){

    double acceleration_time = (max_speed-start_and_end_speed )/ acceleration;

    return acceleration_time;

}






