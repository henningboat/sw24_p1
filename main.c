#include <stdio.h>

#include "model_input.h"
#include "path_finding.h"

int main(void) {
    ModelData model_data = get_model_data();

    const Station* a = &model_data.stations[1];
    const Station* b= &model_data.stations[5];

    double result = get_total_travel_time(a,b, &model_data);

    printf("%lf",result/60);

    return 0;
}
