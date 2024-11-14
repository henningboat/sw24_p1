#include <stdio.h>
#include <math.h>



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

struct route_time {
    char route[NAME_LENGTH + 1];
    double time;
};
typedef struct route_time route_time;

double time_speed_1(double dist, double speed, double time_factor);
double time_speed_2(double dist, double speed, double time_factor);

int main(void) {
    double time_arr[5];
    for(int i = 0; i < 6; i++) {

    }
    //time_speed_1(KBH_RING_D, MAX_SPEED_1);
    printf("Minutter fra KBH til RING ved 180km/t %lf minutter\n", time_speed_1(KBH_RING_D, MAX_SPEED_1, TIME_FACTOR));
    //time_speed_2(KBH_RING_D, MAX_SPEED_1, &time);
    printf("\nMinutter fra KBH til RING ved 200km/t %lf minutter\n", time_speed_2(KBH_RING_D, MAX_SPEED_1, TIME_FACTOR));
    return 0;
}

/*
  *Variable distance
    *calculate funktion
    *tid, længde, acceleration, hastighed
*/

void distance(char a, char b, double *distance ) {

    if(a == 'a' && b == 'b') {
        *distance = 30;
    }else if(a == 'b' && b=='c') {
        *distance = 20;
    }
}

double time_speed_1(double dist, double speed, double time_factor) {

    double time = (KBH_RING_D / MAX_SPEED_1) * TIME_FACTOR;
    return time;
}

double time_speed_2(double dist, double speed, double time_factor) {
    double time = (KBH_RING_D / MAX_SPEED_2) * TIME_FACTOR;
    return time;
}



/*void sfsf() {
    double totalTime;

    //String cityName;
    //String cityName2;

    for{
        if() {

            time()
        }
    }

}*/