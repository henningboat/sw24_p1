#include <stdio.h>
#include <math.h>


/****************DEFINED CONSTANTS***************/
#define MAX_SPEED_1 180.0 // km/t
#define MAX_SPEED_2 200.0 // km/t

#define TIME_FACTOR 60.0  // omregner til minut

#define NAME_LENGTH 20  // allokerer 20 pladser i lageret til struct

#define KBH_RING_D  60.0     //km              //rejseplan 30 min
#define RING_OD_D   102.0     //motorvejslængde fra google maps //rejseplan 45 min
#define OD_KOLD_D   68.0
#define KOLD_PAD_D  85.0
#define PAD_SCHL_D  47.0
#define SCHL_HAM_D  130.0

#define ACCELERATION 0.8 //1.2
#define DECELERATION 1.0 //1.1
/*-----------------------------------------------*/


//*********************STRUCTS********************/

typedef struct  {
    char route[NAME_LENGTH + 1];
    double time;
}route_time;

/*-----------------------------------------------*/


/*****************PROTOTYPES**********************/

double get_travel_time(double dist, double speed, double acceleration);
double convertKMHtoMS(double kmh);
double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration);
double acceleration_distance_calculator(double start_and_end_speed,double max_speed,double acceleration);
/*-----------------------------------------------*/


int main(void) {

    printf("Minutter fra KBH til RING ved 180km/t %lf minutter\n",
            get_travel_time(KBH_RING_D, MAX_SPEED_1,ACCELERATION));


    return 0;
}

// There will be a struct here instead of dist, speed leration
double get_travel_time(double dist, double speed, double leration) {

    double acceleration_Time = acceleration_time_calculator(0,speed,leration);

    double ac_dist= acceleration_distance_calculator(0,speed,leration);

    dist -= ac_dist;

    double time = (dist / speed) * TIME_FACTOR+acceleration_Time;

    return time;
}

double acceleration_distance_calculator(double start,double max_speed,double acceleration) {

    //stretch = 1/2 * acceleration * time^2

    double time = acceleration_time_calculator(start,max_speed,acceleration);

    double stretch = 1/2 * acceleration * pow(time,2);

    return stretch;
}


double acceleration_time_calculator(double start_and_end_speed,double max_speed,double acceleration){

    //convert km/h to m/s
    double m_per_s=convertKMHtoMS(max_speed);

    //calculate the time taken (start speed is left in for future refactoring)
    double leration_time = (m_per_s - start_and_end_speed / acceleration);
    printf("daaz nutz : %lf\n",acceleration);

    //return the time
    return leration_time;

}

double convertKMHtoMS(double kmh) {

    return kmh*1000/3600;

}





