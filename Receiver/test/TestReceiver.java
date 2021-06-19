package test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import main.ReceiveData;

public class TestReceiver {
	List<Integer> paramList; 
	ReceiveData receiveData;
	
	@Before
	public void executedBeforeEach() {
		paramList = new ArrayList<Integer>(Arrays.asList(50,80,30,20,60));
		receiveData = new ReceiveData();
	}
	
	@Test
	public void givenParamList_whenContainsValue_thenReturnMaxValue() {
		assertEquals(80, receiveData.getMaxValueInParameter(paramList));
	}
	
	@Test
	public void givenParamList_whenContainsValue_thenReturnMinValue() {
		assertEquals(20, receiveData.getMinValueInParameter(paramList));
	}	
	
	@Test
	public void givenParamList_whenContainsFiveValues_thenReturnSimpleMovingAverage() {
		assertEquals(48, receiveData.getSimpleMovingAverageOfLastFiveParamValues(paramList));
	}
	
	@Test
	public void givenSingleRecord_whenContainsNull_thenReturnNull() {
		assertNull(receiveData.dataParser("null;null;"));
	}

	@Test
	public void givenReadings_whenEmpty_thenReturnNull() {
		assertNull(receiveData.dataParser(";;"));
	}
	
}
