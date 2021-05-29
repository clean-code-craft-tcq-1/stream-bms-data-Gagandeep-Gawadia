#pragma once
#include "Type_def.h"

void SenderMain();
void StreamData();
void Delete_DataLogFile();
read_status readDataFromFile(int *temp, int *soc, FILE *fptr);
void printToConsole(int temp, int soc);