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

TEST_CASE ("Validate generated datastream is as expected")
{
    int data = 0;
    int *RandomNo = &data;
    
#if (UNITTEST) 
    set_success_stub(true);
#endif 
    
    //If test case fails make sure txt file are deleted before running tests/ delete manually if required  
    remove("data.txt");
    remove("verify.txt");  
  
    //Generate a dummy verify.txt file to be compared with data.txt
    FILE *fptr2 = fopen("verify.txt", "a");
    bool iSReadSuccessfull_temp = GenRandomParameter(RandomNo);
  
    /*Print one dataset*/
    for (int Par_Counter = 0; Par_Counter < NoOfPar; Par_Counter++)
    {
      //Print to file Temperature/StateOfCharge parameter
      fprintf(fptr2, "%d", *RandomNo);
      // Print delimiter which is semicolon
      fprintf(fptr2, "%c", 59);
    }
    //Newline
    fprintf(fptr2, "\n");  
    //Close file
    fclose(fptr2);

    //Call function under test
    GenerateDataStream();
  
    //Expected Output 
#if (UNITTEST) 
    //Open the 2 files and compare first dataset to see the data generated and written is as expected
    FILE * fptr1 = fopen("data.txt", "r");
    fptr2 = fopen("verify.txt", "r");

    //Verify one parameter set of file i.e. temp;soc;\n which is the fiel format
    char ch_1, ch_2;
    ch_1 = fgetc(fptr1);
    ch_2 = fgetc(fptr2);
    
  for (;!feof(fptr2);  ch_1 = fgetc(fptr1), ch_2 = fgetc(fptr2))
    {
      REQUIRE(ch_1 == ch_2);
    }

    fclose(fptr1);
    fclose(fptr2);
 #endif 
  
    remove("data.txt");
    remove("verify.txt");
}//END OF TEST_CASE

//Added test case to validate that sender main functionality and also for coverage
TEST_CASE ("Validate sender main function")
{
  bool successIfTrue = false;//Boolean to verify if the function Sendermain has executed successfully
  
  // Creating data.txt file so that we verify file is deleted at the end by function Delete_DataLogFile() inside 
  // Sendermain()
   FILE * fptr = fopen("data.txt", "w");
   fclose(fptr);
  
   //Call function under test 
   Sendermain();

  //This action should not be executed since the file is already deleted
  if (remove("data.txt") == 0)
  {
	successIfTrue = false; 
  }
  else // Since the txt file is deleted already  
  {
	successIfTrue = true;
  }
	
  REQUIRE(successIfTrue == true);
}//END_OF_TEST_CASE
