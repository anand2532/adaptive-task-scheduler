#ifndef DATA_FUSION_H
#define DATA_FUSION_H

#include "FreeRTOS.h"
#include "task.h"

// Data fusion task function
void dataFusionTask(void *pvParameters);

#endif // DATA_FUSION_H