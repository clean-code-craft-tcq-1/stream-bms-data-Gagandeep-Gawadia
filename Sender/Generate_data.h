#pragma once
#include "Type_def.h"

#if (!UNITTEST)
bool GenRandomParameter(int *randomNo);

#else

void set_success_stub(bool ifTrueReadSucess);
bool GenRandomParameter(int *randomNo);

#endif

read_status GenDataSet(int *temp, int *soc);
void GenerateDataStream();
void delay(int number_of_seconds);
void writeDataToFile(int * parameterset);
