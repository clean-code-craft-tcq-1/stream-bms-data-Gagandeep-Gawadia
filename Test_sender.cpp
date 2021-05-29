#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Sender/Sender.c"
#include "Sender/Generate_data.c"


TEST_CASE("Validate data generated is read") {
  
  int const NumOfTest = 2;
  read_status Output_Current_status;
  FILE * fptr;

  typedef  struct inputmatrix
  {
    bool success_flag;
    int  parameterset[NoOfPar];
    read_status current_status;
  }inputmatrix;

  typedef  struct outputmatrix
  {
    int  parameterset[NoOfPar];
    read_status current_status;
  }outputmatrix;

  inputmatrix test_inputmatrix[] =
                                  { {false, {0,0}, NotErroneous },
                                    {true,  {0,0}, ErroneousSoc },
                                  };



  outputmatrix test_outputmatrix[] =
                                   { { {101,101}, NotErroneous },
                                     { {50,50 }, NotErroneous },
                                   };


  for (int TestCase = 0; TestCase < NumOfTest;TestCase++)
  {

#if (UNITTEST) 
    set_success_stub(test_inputmatrix[TestCase].success_flag);
#endif

    //Deleting any old data log
    Delete_DataLogFile();

    //Helper/Interface function needs to be called to make sure intended file txt is generated
    GenerateDataStream();
   
    fptr = fopen("data.txt", "r");

    for (int Par_Counter = 0; Par_Counter < NoOfParamterSet; Par_Counter++)
    {
      Output_Current_status = test_inputmatrix[TestCase].current_status;

      //Function call under test
      Output_Current_status = readDataFromFile(test_inputmatrix[TestCase].parameterset, fptr);

#if (UNITTEST) 
      	REQUIRE(test_outputmatrix[TestCase].current_status == Output_Current_status);
      	REQUIRE(test_inputmatrix[TestCase].parameterset[Temperature] == test_outputmatrix[TestCase].parameterset[Temperature]);
      	REQUIRE(test_inputmatrix[TestCase].parameterset[StateOfCharge] == test_outputmatrix[TestCase].parameterset[StateOfCharge]);
#endif //(UNITTEST) 
    }
    
    fclose(fptr);
 }//End of test loop

 //Call function under test for NULL pointer
 Output_Current_status = readDataFromFile(NULL, NULL);
 REQUIRE(Output_Current_status == ErroneousPars);

}//End of Test_Case

