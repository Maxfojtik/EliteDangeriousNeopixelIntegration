package EliteComms;

import java.awt.Color;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.fazecast.jSerialComm.SerialPort;

/*
 * @author Maxwell Fojtik
 */

public class MicroConnection
{
	static SerialPort commPort;
	static BufferedReader input;
	static BufferedWriter output;
	static boolean connected = false;
	static int redIn = 250;
	static int greenIn = 80;
	static int blueIn = 0;
	static Color shieldsColor = new Color(84, 131, 188);
	static Color morphColor(Color in) throws XMLStreamException, ParserConfigurationException, SAXException, IOException
	{
		float[][] matrix = {
			{1,0,0},
			{0,1,0},
			{0,0,1}
		};
        // Setup a new eventReader
        File xmlFile = new File("C:\\Users\\"+System.getProperty("user.name")+"\\AppData\\Local\\Frontier Developments\\Elite Dangerous\\Options\\Graphics\\GraphicsConfiguration.xml");
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
    	DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
    	Document doc = dBuilder.parse(xmlFile);
    	String redVal = doc.getElementsByTagName("MatrixRed").item(0).getTextContent();
    	String greenVal = doc.getElementsByTagName("MatrixGreen").item(0).getTextContent();
    	String blueVal = doc.getElementsByTagName("MatrixBlue").item(0).getTextContent();
    	String[] redParts = redVal.trim().split(",");
    	for(int i = 0; i < redParts.length; i++)
    	{
    		matrix[0][i] = Float.parseFloat(redParts[i].trim());
    	}
    	String[] greenParts = greenVal.trim().split(",");
    	for(int i = 0; i < greenParts.length; i++)
    	{
    		matrix[1][i] = Float.parseFloat(greenParts[i].trim());
    	}
    	String[] blueParts = blueVal.trim().split(",");
    	for(int i = 0; i < blueParts.length; i++)
    	{
    		matrix[2][i] = Float.parseFloat(blueParts[i].trim());
    	}
		int redOut = (int) (in.getRed()*matrix[0][0]+in.getGreen()*matrix[1][0]+in.getBlue()*matrix[2][0]);
		int greenOut = (int) (in.getRed()*matrix[0][1]+in.getGreen()*matrix[1][1]+in.getBlue()*matrix[2][1]);
		int blueOut = (int) (in.getRed()*matrix[0][2]+in.getGreen()*matrix[1][2]+in.getBlue()*matrix[2][2]);
		if(redOut>255)
		{
			redOut = 255;
		}
		if(greenOut>255)
		{
			greenOut = 255;
		}
		if(blueOut>255)
		{
			blueOut = 255;
		}
		if(redOut<0)
		{
			redOut = 0;
		}
		if(greenOut<0)
		{
			greenOut = 0;
		}
		if(blueOut<0)
		{
			blueOut = 0;
		}
		return new Color(redOut, greenOut, blueOut);
	}
	public MicroConnection()
	{
		tryConnection();
	}
	static void tryConnection()
	{
		Frame.print("Trying to connect");
		System.out.println("Trying to connect");
		connected = false;
		SerialPort[] ports = SerialPort.getCommPorts();
		for(int i = 0; i < ports.length; i++)
		{
			try
			{
				SerialPort attemptPort = ports[i];
				Frame.print("Trying "+attemptPort.getDescriptivePortName());
				//System.out.println("Trying "+attemptPort.getDescriptivePortName());
				attemptPort.openPort();
				InputStreamReader ISR = new InputStreamReader(attemptPort.getInputStream());
				input = new BufferedReader(ISR);
				output = new BufferedWriter(new OutputStreamWriter(attemptPort.getOutputStream()));
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				output.write("PING\n");
				output.flush();
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				if(input.ready())
				{
					String str = input.readLine();
					if(str.equals("pingElite"))
					{
						commPort = attemptPort;
						connected = true;
						try
						{
							Color c = morphColor(new Color(redIn, greenIn, blueIn));
							sendEvent("R:"+(c.getRed()));
							sendEvent("G:"+(c.getGreen()));
							sendEvent("B:"+(c.getBlue()));
							
							Color sc = morphColor(shieldsColor);
							sendEvent("SR:"+(sc.getRed()));
							sendEvent("SG:"+(sc.getGreen()));
							sendEvent("SB:"+(sc.getBlue()));
						}
						catch(Exception e)
						{
							e.printStackTrace();
						}
						break;
					}
				}
				input.close();
				output.close();
				attemptPort.closePort();
			}
			catch(Exception e) {}
		}
		if(connected)
		{
			Frame.print("CONNECTED");
			System.out.println("CONNECTED TO SERIAL");
			TaskbarIcon.setConnection(true);
		}
		else
		{
			TaskbarIcon.setConnection(false);
		}
	}
	static void disconnect()
	{
		if(commPort!=null)
		{
			commPort.closePort();
		}
	}
	static boolean sendEvent(String event)
	{
		if(connected)
		{
			Frame.print("<-"+event);
			System.out.println("<-"+event);
			try {
				output.write(event+"\n");
				output.flush();
				Thread.sleep(100);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		TaskbarIcon.setConnection(false);
		tryConnection();
		return false;
	}
}
