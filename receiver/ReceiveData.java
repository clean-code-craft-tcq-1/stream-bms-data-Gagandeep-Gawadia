package receiver;
import java.io.*;
import java.util.*;


public class ReceiveData {

	public static void main(String[] args) {
		String incomingData ;
		int incomingDataLimit = 14, incomingDataCounter = 0;
		int[] singleRecord = new int[2];
		List<Integer> temperature = new ArrayList<Integer>();
		List<Integer> soc = new ArrayList<Integer>();
		try {
			Scanner in = new Scanner(System.in);
			
			//to skip unnecessary statements printed in console by the sender 
			while(true) {
					incomingData = in.nextLine();				
					if(incomingData.equalsIgnoreCase("Temperature;Soc;")) {
						break;
					}
						}
			readSenderDataFromConsole(in, incomingData, incomingDataLimit,incomingDataCounter, singleRecord, temperature, soc);
			printMaxAndMinValuesInParameter("Temperature", getMaxValueInParameter(temperature),getMinValueInParameter(temperature));
			printMaxAndMinValuesInParameter("SOC", getMaxValueInParameter(soc),getMinValueInParameter(soc));
			printSimpleMovingAverageForParams("Temperature",getSimpleMovingAverageOfLastFiveParamValues(temperature));
			printSimpleMovingAverageForParams("SOC",getSimpleMovingAverageOfLastFiveParamValues(soc));
			}
			catch(Exception e) {
				System.err.println(e);
			}
	}
	
	/**
	 * reads the temperature and soc values from sender console
	 * @param in - Scans the console to read data
	 * @param incomingData - stores the data read from console
	 * @param incomingDataLimit - number of data to be read from console
	 * @param incomingDataCounter - initial value of the counter
	 * @param singleRecord - a record of temperature & soc value
	 * @param temperature - stores temperature value read from console
	 * @param soc - stores soc value read from console
	 */
	public static void readSenderDataFromConsole(Scanner in, String incomingData, int incomingDataLimit, int incomingDataCounter, int[] singleRecord, List<Integer> temperature, List<Integer> soc) {
		while(true) {			
			incomingData = in.nextLine();
			if(incomingDataCounter == incomingDataLimit)
				break;
			singleRecord = dataParser(incomingData); 
			if(singleRecord == null) {
				System.out.println("Not a valid data" );
				System.exit(1);
			}
			temperature.add(singleRecord[0]); 
			soc.add(singleRecord[1]);
			incomingDataCounter++;
		}
	}
	
	/**
	 * Process the sender input data read from console 
	 * @param readData - data from console
	 * @return a record of param data from console i.e. temperature & soc
	 */
	public static int[] dataParser(String readData) {
		if(readData.contains("null"))
			return null;
		int[] singleRecord = new int[2];
		String[] consoleData = readData.split(";");
		if(consoleData.length < 2) 
			return null;
		singleRecord[0] = Integer.parseInt(consoleData[0]);
		singleRecord[1] = Integer.parseInt(consoleData[1]); 
		return singleRecord;
	}
	
	/**
	 * Finds the maximum value in the param list 
	 * @param paramList - list of a parameter readings
	 * @return maximum value
	 */
	public static int getMaxValueInParameter(List<Integer>paramList) {
		return Collections.max(paramList);		
	}

	/**
	 * Finds the minimum value in the param list
	 * @param paramList - list of a parameter readings 
	 * @return minimum value
	 */
	public static int getMinValueInParameter(List<Integer>paramList) {
		return Collections.min(paramList);		
	}
	
	/**
	 * Prints maximum and minimum value to the console
	 * @param paramName - paramter name i.e. temperature or soc 
	 * @param maxValue - maximum value in the given param list
	 * @param minValue - minimum value in the given param list
	 */
	public static void printMaxAndMinValuesInParameter(String paramName, int maxValue, int minValue) {
		System.out.println(paramName + " Maximum Value : "+ maxValue +"\t"+ "Minimum Value : "+ minValue);
	}
	
	/**
	 * Calculates the average of last five values in the given param list 
	 * @param paramList - list of a parameter readings
	 * @return average of last five values
	 */
	public static int getSimpleMovingAverageOfLastFiveParamValues(List<Integer> paramList) {
		List<Integer> lastFiveValues = paramList.subList(paramList.size() - 5, paramList.size());
		int sum = 0;
		try {
			for(Integer paramValue: lastFiveValues) {
				sum = sum + paramValue;
			}
		}
		catch(Exception e) {
			System.err.println(e);
		}
		return sum/5;
	}
	
	/**
	 * Prints the average to the console
	 * @param paramName - paramter name i.e. temperature or soc 
	 * @param averageValue - average of last five value in the param list
	 */
	public static void printSimpleMovingAverageForParams(String paramName, int averageValue) {
		System.out.println("Simple moving average of "+ paramName + " is " + averageValue);
	}
}
