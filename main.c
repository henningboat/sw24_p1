#include <stdio.h>

#include "model_input.h"
#include "path_finding.h"

int main(void) {
    ModelData model_data = get_model_data();

    const Station* a = get_station_by_name("Hamburg C", &model_data);
    const Station* b = get_station_by_name("Ringsted", &model_data);

    double result = get_total_travel_time(a,b, &model_data);

    printf("%lf",result/60);

    return 0;
}
