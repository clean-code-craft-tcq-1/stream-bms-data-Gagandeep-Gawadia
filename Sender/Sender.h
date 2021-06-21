#pragma once
#include "Type_def.h"

void SenderMain();
void StreamData();
read_status readDataFromFile(int *temp, int *soc, FILE *fptr);
void printToConsole(int temp, int soc);
