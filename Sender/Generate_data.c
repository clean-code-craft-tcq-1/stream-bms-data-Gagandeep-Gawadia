
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Generate_data.h"

/*Helper functions are written in the file to create the required data set to be streamed and send to console*/

#if (!UNITTEST)
bool GenRandomParameter(int *randomNo)
{
  //In real scenario if the pointer was NULL i.e. some communication error
  // we return false which signifies read error.
  //Random numbers are generated between 0-100 (%100) and that is why for any error
  // data is symbolized by NotANum --> 101

  if (randomNo != NULL)
  {
    *randomNo = rand() % 100;
    return true;
  }
  else
  {
    return false;
  }
}
#else
int success_stub;

//To stub communication failure we clear the flag ifTrueReadSucess
//i.e. ifTrueReadSucess == false signifies the read process failed.

void set_success_stub(bool ifTrueReadSucess)
{
  success_stub = ifTrueReadSucess;
}

bool GenRandomParameter(int *randomNo)
{
  *randomNo = 50;
  return success_stub;
}
#endif


/* Function to introduce wait cycles or delay in seconds
* delay(1) --> wait of 1 sec before execution of next command*/

void delay(int number_of_seconds)
{
  // Converting time into milli_seconds
  int milli_seconds = 1000 * number_of_seconds;

  // Storing start time
  clock_t start_time = clock();

  // looping till required time is not achieved
  // which is begin time + wait time in milliseconds 
  while (clock() < start_time + milli_seconds);
}

read_status GenDataSet(int *temp, int *soc)
{

  read_status current_status = NotErroneous;
  //In real scenario we would read from sensor intsead of calling function random number generator 
  //and we could have communication errors to realize the same, function return indicates if the 
  // read was successfull 

  bool iSReadSuccessfull_temp = GenRandomParameter(temp);
  bool iSReadSuccessfull_soc = GenRandomParameter(soc);

  //Signifies communication error while reading from sensor and in such scenarios we send 
  //NotANum to signify there was error while reading from sensor 
  if ((!iSReadSuccessfull_temp) && (!iSReadSuccessfull_temp))
  {
    current_status = ErroneousPars;
  }
  //Signifies communication error while reading from sensor 
  else if ((!iSReadSuccessfull_soc))
  {
    current_status = ErroneousSoc;
  }
  else if (!iSReadSuccessfull_temp)
  {
    current_status = ErroneousTemp;
  }
  return current_status;
}

void writeDataToFile(int * parameterset)
{
  FILE *fptr;

  /* Open file and get the pointer to same, file is either present or created.
  * The program deletes the file at the end so that everytime sender is run
  * we write to an empty newfile otherwise it will append at the end of the last dataset.
  * In any case if the program aborts or the file is not deleted we can do it ourself
  * and the file will be generated as we begin the program. */

  fptr = fopen("data.txt", "a");
  if (fptr != NULL)
  {
    /* Write both the parameters to file and this will be used to read
    *  and print on console:
    *  Format of the generated file temp;soc;\n
    *  e.g. 50;50;
    *       50;50;
    *       ..so on at one time 15 parameter set is generated*/

    /*Print one dataset*/

    for (int Par_Counter = 0; Par_Counter < NoOfPar; Par_Counter++)
    { 
      //Print to file Temperature/StateOfCharge parameter
       fprintf(fptr, "%d", parameterset[Par_Counter]);
      // Print delimiter which is semicolon
       fprintf(fptr, "%c", 59);
    }
    
    //Newline as we print one one set in each line
    fprintf(fptr, "\n");

    //Close file
    fclose(fptr);
  }
  else
  {
    // Remark : This statement cannot be tested
    printf("ERROR: Cannot write to data.txt");
  }
}

/* Function is used to generate the required data stream which has to be sent by sender functionality to console
*  The function does 2 jobs:
*  Firstly, Create each parameter data set using function GenDataSet() comprising of temperature and soc and
*  then generate stream by looping and as expected we are generating 15 (NoOfParamterSet) set.
*  Secondly, create a file and save the generated stream of data to be read by sender  */
void GenerateDataStream()
{
  // Data will be streaming continuously and we are generating 15 dataset to
  // represent the same which will be genrated at delay of 1 sec set using delay function
  for (int ParSet_counter = 0; ParSet_counter < NoOfParamterSet; ParSet_counter++)
  {
    int par1 = 0, par2 = 0;
    // These are the 2 parameters temp and soc used to monitor battery.
    // The pointers are sent to read the data in case of any error while generating data NotANum is written as data.
    int *temp = &par1, *soc = &par2;

    read_status current_status = NotErroneous;
    current_status = GenDataSet(temp, soc);

    int parameterset[NoOfPar];
    parameterset[Temperature]= *temp;
    parameterset[StateOfCharge] = *soc;

    switch (current_status)
    {
    case ErroneousPars:
    {
      parameterset[Temperature]   = NotANum;
      parameterset[StateOfCharge] = NotANum;
      break;
    }
    case ErroneousSoc:
    {
      parameterset[Temperature]   = *temp;
      parameterset[StateOfCharge] = NotANum;
      break;
    }
    case ErroneousTemp:
    {
      parameterset[Temperature]   = NotANum;
      parameterset[StateOfCharge] = *soc;
      break;
    }
    }

    //Generating file format of streaming data
    writeDataToFile(parameterset);

  }//Looping for dataset
}// End of function GenerateDataStream()

 /* We delete the txt file to be created everytime we run sender
 * so that when we generate new data stream it written from beginning of the file
 * and not append the old data. */
void Delete_DataLogFile()
{
  if (remove("data.txt") == 0)
    printf("Text file deleted successfully");
  else
    printf("Unable to delete the txt file");
}
