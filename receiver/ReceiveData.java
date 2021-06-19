package receiver;
import java.io.Console;
import java.util.*;


public class ReceiveData {

	public static void main(String[] args) {
		String incomingData ;
		int incomingDataLimit = 15, incomingDataCounter = 0;
		Console consoleReader = System.console();
		int[] singleRecord = new int[2];
		List<Integer> temperature = new ArrayList<Integer>();
		List<Integer> soc = new ArrayList<Integer>();
		while((incomingData = consoleReader.readLine()) != null) {
			if(incomingDataCounter == 0) {
				continue;
			}
			if(incomingDataCounter == incomingDataLimit)
				break;
			
			singleRecord = dataParser(incomingData);
			if(singleRecord == null) {
				System.out.println("Not a valid data");
				System.exit(1);
			}
			temperature.add(singleRecord[0]); 
			soc.add(singleRecord[1]);
			incomingDataCounter++;
		}
		printMaxAndMinValuesInParameter("Temperature", getMaxValueInParameter(temperature),getMinValueInParameter(temperature));
		printMaxAndMinValuesInParameter("SOC", getMaxValueInParameter(soc),getMinValueInParameter(soc));
		printSimpleMovingAverageForParams("Temperature",getSimpleMovingAverageOfLastFiveParamValues(temperature));
		printSimpleMovingAverageForParams("SOC",getSimpleMovingAverageOfLastFiveParamValues(soc));
	}
	
	public static int[] dataParser(String readData) {
		if(readData.contains("null"))
			return null;
		int[] singleRecord = new int[2];
		String[] consoleData = readData.split(";");
		System.out.println(consoleData.length);
		if(consoleData.length < 2) 
			return null;
		singleRecord[0] = Integer.parseInt(consoleData[0]);
		singleRecord[1] = Integer.parseInt(consoleData[1]); 
		return singleRecord;
	}
	
	public static int getMaxValueInParameter(List<Integer>paramList) {
		return Collections.max(paramList);		
	}

	public static int getMinValueInParameter(List<Integer>paramList) {
		return Collections.min(paramList);		
	}
	
	public static void printMaxAndMinValuesInParameter(String paramName, int maxValue, int minValue) {
		System.out.println(paramName + "Maximum Value : "+ maxValue +"\t"+ "Minimum Value : "+ minValue);
	}
	
	public static int getSimpleMovingAverageOfLastFiveParamValues(List<Integer> paramList) {
		System.out.println("from "+ (paramList.size() - 5) + "to "+ (paramList.size() - 1));
		List<Integer> lastFiveValues = paramList.subList(paramList.size() - 5, paramList.size());
		int sum = 0;
		try {
			for(Integer paramValue: lastFiveValues) {
				sum = sum + paramValue;
				System.out.println(paramValue );
			}
		}
		catch(Exception e) {			
		}
		return sum/5;
	}
	
	public static void printSimpleMovingAverageForParams(String paramName, int averageValue) {
		System.out.println("Simple moving average of "+ paramName + "is " + averageValue +"\n");
	}
}
