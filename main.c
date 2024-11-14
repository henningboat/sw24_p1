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

#define ACCELERATION pow(1.2,2)
/*************************************************/


//*********************STRUCTS********************/

typedef struct  {
    char route[NAME_LENGTH + 1];
    double time;
}route_time;

/*************************************************/


/*****************PROTOTYPES**********************/

double get_travel_time(double dist, double speed, double time_factor);
double convertKMHtoMS(double kmh);

/*************************************************/


int main(void) {
    printf("Minutter fra KBH til RING ved 180km/t %lf minutter\n", get_travel_time(KBH_RING_D, MAX_SPEED_1, TIME_FACTOR));

    return 0;
}

/*
  *Variable distance
    *calculate funktion
    *tid, længde, acceleration, hastighed
*/


double get_travel_time(double dist, double speed, double time_factor) {
    // (distance / start hast) + (distance / max hastighed) + (distance / sluthastighed)

    double time = (KBH_RING_D / MAX_SPEED_1) * TIME_FACTOR;
    return time;
}

double placeholderFunction( double distance, double start_speed,
                            double max_speed, double end_speed,
                            double acceleration, double deceleration) {

    //convert km/h to m/s
    double m_per_s=convertKMHtoMS(max_speed);

    //return the time
    return m_per_s/acceleration;

    /*
     *if toget ikke kan nå top speed indenfor strækket
     *så en linjestykke om det
     *
     *else regn accerelation og deceleration af toget
     *
     *tilføj tiden det tager til travel_time variablen
     *returnere det
     */

}

double convertKMHtoMS(double kmh) {
    return kmh*1000/3600;
}





