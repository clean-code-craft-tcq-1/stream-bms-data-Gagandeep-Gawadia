#pragma once
#define UNITTEST 1
#define NotANum 101 // send as data to signify erroneous data and read was not successful
#define NoOfParamterSet 15
#define NoOfPar 2 

typedef enum  read_status
{
  ErroneousTemp,
  ErroneousSoc,
  ErroneousPars,
  NotErroneous
}read_status;

typedef enum  par_type
{
  Temperature,
  StateOfCharge
}par_type;
