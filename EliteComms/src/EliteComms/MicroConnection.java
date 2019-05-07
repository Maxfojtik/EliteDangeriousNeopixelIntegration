package EliteComms;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

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
	public MicroConnection()
	{
		tryConnection();
	}
	static void tryConnection()
	{
		System.out.println("Trying to connect");
		connected = false;
		SerialPort[] ports = SerialPort.getCommPorts();
		for(int i = 0; i < ports.length; i++)
		{
			try
			{
				SerialPort attemptPort = ports[i];
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
