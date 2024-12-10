#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "structs.h"
ModelData get_model_data(char* model_data_path);
const Station* get_station_by_name(char* name, const ModelData* model_data);

#endif