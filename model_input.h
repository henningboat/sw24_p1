#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "structs.h"
ModelData get_model_data(void);
const Station* get_station_by_name(char* name, const ModelData* model_data);

#endif