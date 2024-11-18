#include <stdio.h>
#include <math.h>


/****************DEFINED CONSTANTS***************/

#define MAX_SPEED_1 180.0 // km/t
#define MAX_SPEED_2 200.0 // km/t

#define TIME_FACTOR 60.0  // omregner til minut

#define NAME_LENGTH 20  // allokerer 20 pladser i lageret til struct

#define KBH_RING_D  60.0     //km //rejseplan 30 min
#define RING_OD_D   102.0     //motorvejslængde fra google maps //rejseplan 45 min
#define OD_KOLD_D   68.0
#define KOLD_PAD_D  85.0
#define PAD_SCHL_D  47.0
#define SCHL_HAM_D  130.0

#define ACCELERATION 1.2 //1.2
#define DECELERATION 1.0 //1.1

/*-----------------------------------------------*/


/*********************STRUCTS********************/

typedef struct  {
    char route[NAME_LENGTH + 1];
    double time;
}route_time;

/*-----------------------------------------------*/


/*****************PROTOTYPES**********************/

double get_travel_time(double dist, double speed, double acceleration,double deceleration);
double convertKMHtoMS(double kmh);
double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration);
double acceleration_distance_calculator(double time ,double acceleration);
/*-----------------------------------------------*/


int main(void) {

    /*TODO
     *air force/drag
     *power drag i.e rails and friction
     *Station stop
     *make a function that can turn minutes into  | hours | minutes | format
     *Emission
     */

    printf("Minutter fra KBH til RING ved 180km/t %2.2lf minutter og afstanden %2.0lfkm \n",
            get_travel_time(KBH_RING_D, MAX_SPEED_1,ACCELERATION,DECELERATION), KBH_RING_D);

    return 0;
}

// There will be a struct here instead of dist, speed leration
double get_travel_time(double dist, double speed, double acceleration,double deceleration) {

    double acceleration_time = acceleration_time_calculator(0,speed,acceleration);
    double deceleration_time =acceleration_time_calculator(0,speed,deceleration);

    double ac_distance = acceleration_distance_calculator(acceleration_time, acceleration);
    double dc_distance = acceleration_distance_calculator(acceleration_time, acceleration);

    dist = dist-ac_distance-dc_distance;//To find the time taken, we need to factor in ac- and deceleration time
    double time = (dist / speed) * TIME_FACTOR+acceleration_time+deceleration_time; // constant time removed and added ac and dc time


    return time;
}

double acceleration_distance_calculator(double time ,double acceleration) {
    double acceleration_stretch = 0.5 * acceleration * pow(time,2);
    return acceleration_stretch;
}


double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration){
    double m_per_s=convertKMHtoMS(max_speed); //convert km/h to m/s

    double acceleration_time = (m_per_s - start_and_end_speed )/ acceleration;

    return acceleration_time/60;

}

double convertKMHtoMS(double kmh) {

    return kmh*1000/3600;

}





