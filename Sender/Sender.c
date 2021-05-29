#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Sender.h"
#include "Generate_data.h"

/* Function is used to read from a file :
*  Format of the file is temp;soc;\n
*  e.g. 50;50;
*       50;50;
*       ..so on */

read_status readDataFromFile(int* par, FILE *fptr)
{
  read_status current_status = NotErroneous;

  if(  (fptr != NULL)
     && (par != NULL)
    )
  {
    char ch;
    
    //Read first parameter temperature as mentioned in the format of file to be read
    fscanf(fptr, "%d", &par[Temperature]);

    //Avoid delimiter do not save 
    ch = fgetc(fptr);

    //Read second parameter soc as mentioned in the format of file to be read
    fscanf(fptr, "%d", &par[StateOfCharge]);

    /* After the 2 parameters were read we could choose to not read further but since the file pointer
     * needs to point to next line location where the next set of parameter will be read we fetch data till new line*/

     // Avoid delimiter  
    ch = fgetc(fptr);
    //Avoid new line character and drop it as well
    ch = fgetc(fptr);

  }
  else
  {
    current_status = ErroneousPars;
  }
  return current_status;
}

/* Function used to print data in the format as expected to console*/

void printToConsole(int temp ,int  soc) 
{
  printf("%d;%d;\n",temp, soc);
}

/*Reading the data and print to console as expected by Sender */
void Streamdata()
{
  //Open file to be read
  FILE *fptr = fopen("data.txt", "r");

  //Parameters to read
  int  parameterset[2] = { 0 };
  //Parameters to write into console
  int temp_write = 0, soc_write = 0;


  read_status current_status = NotErroneous;
  
  //Print to console the format once at the beginning we can avoid if this is not expected
  // and choose to not specify
  printf("Temperature;Soc;\n");

  /* We are reading one set each time and running the loop for NoOfParamterSet -> 15 parameter set as expected in the problem statement
  *  readDataFromFile is called to read */
  //Since the demand of the project was to read NoOfParamterSet -> 15 parameter set we are running loop
  for (int Par_Counter = 0; Par_Counter < NoOfParamterSet;Par_Counter++)
  {
    current_status = readDataFromFile(parameterset, fptr);

    if (current_status == ErroneousPars)
    {
      temp_write = NotANum;
      soc_write = NotANum;
    }
    else if (current_status == NotErroneous)
    {
      temp_write = parameterset[Temperature];
      soc_write = parameterset[StateOfCharge];
    }

    printToConsole(temp_write, soc_write);
    delay(1);
  }
  fclose(fptr);

}

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

void Sendermain()
{
  GenerateDataStream();
  Streamdata();
  Delete_DataLogFile();
 
}
