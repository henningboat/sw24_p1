#include <stdio.h>

#include "model_input.h"

int main(void) {
    ModelData model_data = get_model_data();
    printf("test %lf", model_data.connections[0].distance);
    return 0;
}
