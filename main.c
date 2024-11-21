#include <stdio.h>

#include "model_input.h"

int main(void) {
    ModelData model_data = get_model_data();
    printf("test distance: %lf\n", model_data.connections[0].distance);
    printf("test max speed: %lf\n", model_data.connections[0].max_speed);
    return 0;
}
