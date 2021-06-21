package receiver;

//import static org.junit.jupiter.api.AssertNull;
import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

//import BeforeEach 
import org.junit.jupiter.api.*;

import receiver.ReceiveData;
public class TestReceiver {

  List<Integer> paramList;
  ReceiveData receiveData;

  @BeforeEach
  public void executedBeforeEach() {
    this.paramList = new ArrayList<Integer>(Arrays.asList(50, 80, 30, 20, 60));
    this.receiveData = new ReceiveData();
  }

  @Test
  public void givenParamList_whenContainsValue_thenReturnMaxValue() {
    assertEquals(80, ReceiveData.getMaxValueInParameter(this.paramList));
  }

  @Test
  public void givenParamList_whenContainsValue_thenReturnMinValue() {
    assertEquals(20, ReceiveData.getMinValueInParameter(this.paramList));
  }

  @Test
  public void givenParamList_whenContainsFiveValues_thenReturnSimpleMovingAverage() {
    assertEquals(48, ReceiveData.getSimpleMovingAverageOfLastFiveParamValues(this.paramList));
  }

  @Test
  public void givenSingleRecord_whenContainsNull_thenReturnNull() {
    assertNull(ReceiveData.dataParser("null;null;"));
  }

  @Test
  public void givenReadings_whenEmpty_thenReturnNull() {
    assertNull(ReceiveData.dataParser(";;"));
  }

}
