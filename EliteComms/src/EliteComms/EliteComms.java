package EliteComms;

import java.awt.AWTException;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.HashMap;

import org.json.JSONArray;
import org.json.JSONObject;
/*
 * @author Maxwell Fojtik
 */
public class EliteComms 
{
	//different granteds based on type of station
	static HashMap<String, String> atri = new HashMap<String, String>();
	static JSONObject lastLine = null;
	static double healthHigh = 1;
	public static void main(String[] args) throws IOException, InterruptedException, AWTException 
	{
		Frame f = new Frame();
		atri.put("Fileheader", "Mode");
		atri.put("MusicTrack", "Mode");
		atri.put("LoadGame", "Mode");
		atri.put("DockingRequested", "Mode");
		atri.put("DockingGranted", "Mode");
		atri.put("DockingDenied", "Mode");
		atri.put("Location", "Mode");
		atri.put("SupercruiseEntry", "Mode");
		atri.put("SupercruiseExit", "Mode");
		atri.put("LaunchDrone", "Notification");
		atri.put("StartJump", "Mode"); 
		atri.put("Docked", "Mode");
		atri.put("HeatWarning", "Notification");
		atri.put("Undocked", "Mode");
		atri.put("Cargo", "Notification");
		atri.put("ModuleBuy", "Loadout");
		atri.put("ShipTargeted", "Notification");
		atri.put("Shutdown", "Mode");
		atri.put("DockSRV", "Mode");
		atri.put("LaunchSRV", "Mode");
		atri.put("Loadout", "Loadout");
		atri.put("AsteroidCracked", "Notification");
		atri.put("Touchdown", "Notification");
		atri.put("ProspectedAsteroid", "Notification");
		atri.put("HullDamage", "Notification");
		new TaskbarIcon();
		MicroConnection teensy = new MicroConnection();
		while(!MicroConnection.connected)
		{
			MicroConnection.tryConnection();
		}
		File fileFolder = new File("C:\\Users\\"+System.getProperty("user.name")+"\\Saved Games\\Frontier Developments\\Elite Dangerous");
		long lastNum = 0;
		while(true)
		{
			File[] files = fileFolder.listFiles();
			File journal = null;
			long newestNum = 0;
			for(int i = 0; i < files.length; i++)
			{
				String fileName = files[i].getName();
				if(fileName.contains("Journal."))
				{
					String jurnNum = fileName.replace("Journal.", "").replace(".01.log", "");
					long num = Long.parseLong(jurnNum);
					if(newestNum<num)
					{
						newestNum = num;
						journal = files[i];
					}
				}
			}
			if(lastNum!=newestNum)
			{
				lastNum = newestNum;
				FileReader reader = new FileReader(journal);
				BufferedReader br = new BufferedReader(reader); 
//				FileReader statusReader = new FileReader(fileFolder.getAbsolutePath()+"/Status.json"); 
				File statusFile = new File(fileFolder.getAbsolutePath()+"/Status.json");
				long lastMod = statusFile.lastModified();
				RandomAccessFile raf = new RandomAccessFile(fileFolder.getAbsolutePath()+"/Status.json", "r");
				raf.seek(0);
				String statusLine = raf.readLine();
				Status.update(new JSONObject(statusLine));
				while(br.ready())
				{
					String st = br.readLine();
					JSONObject line = new JSONObject(st);
					String type = atri.get(line.getString("event"));
					System.out.println(line.get("event"));
					if(type!=null && type.equals("Mode"))
					{
						lastLine = line;
					}
					else if(type!=null && type.equals("Loadout"))
					{
						updateLoadout(line);
					}
					else if(type!=null && type.equals("ModuleBuy"))
					{
						buyModule(line);
					}
				}
				boolean contin = false;
				if(lastLine!=null)
				{
//					System.out.println("<- "+lastLine.get("event"));
					contin = !parse(lastLine);
				}
				while (contin) 
				{
					String st = br.readLine();
					if(st!=null)
					{
						System.out.println(st);
						Frame.print(st);
						JSONObject line = new JSONObject(st);
						boolean brea = parse(line);
						if(brea)
						{
							break;
						}
					}
					else
					{
						if(lastMod!=statusFile.lastModified())
						{
							lastMod = statusFile.lastModified();
							raf.seek(0);
							statusLine = raf.readLine();
							try
							{
								JSONObject line = new JSONObject(statusLine);
								Status.update(line);
							}
							catch(Exception e) 
							{
//								e.printStackTrace();
							}
						}
						else
						{
							Thread.sleep(100);
						}
					}
					if(MicroConnection.input.ready())
					{
						String line = MicroConnection.input.readLine();
						Frame.print("->"+line);
						System.out.println("->"+line);
					}
				} 
				br.close();
				raf.close();
				Frame.print("Detected Shutdown");
				System.out.println("Detected Shutdown");
			}
			else
			{
				Thread.sleep(1000);
			}
		}
	}
	static boolean parse(JSONObject line) throws InterruptedException
	{
		if(lastLine==null)
		{
			lastLine = line;
		}
		if(line.getString("event").equals("Fileheader"))
		{
			TaskbarIcon.setElite(true);
			MicroConnection.sendEvent("Startup");
		}
		if(line.getString("event").equals("Music"))
		{
			parseMusic(line.getString("MusicTrack"));
		}
		if(line.getString("event").equals("LoadGame"))
		{
			MicroConnection.sendEvent("LoadGame");
		}
		if(line.getString("event").equals("DockingRequested"))
		{
			MicroConnection.sendEvent("DockingRequested");
		}
		if(line.getString("event").equals("DockingGranted"))
		{
			MicroConnection.sendEvent("DockingGranted");
		}
		if(line.getString("event").equals("DockingDenied"))
		{
			MicroConnection.sendEvent("DockingDenied");
		}
		if(line.getString("event").equals("DockingCancelled"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(line.getString("event").equals("DockingTimeout"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(line.getString("event").equals("Location"))
		{
			if(!line.getBoolean("Docked"))
			{
				MicroConnection.sendEvent("Undocked");
			}
		}
		if(line.getString("event").equals("SupercruiseEntry"))
		{
			MicroConnection.sendEvent("SupercruiseEntry");
		}
		if(line.getString("event").equals("ProspectedAsteroid"))
		{
			MicroConnection.sendEvent("ProspectedAsteroid");
		}
		if(line.getString("event").equals("SupercruiseExit"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(line.getString("event").equals("Touchdown"))
		{
			if(!lastLine.getString("event").equals("EngineerProgress"))
			{
				if(line.getBoolean("PlayerControlled"))
				{
					MicroConnection.sendEvent("TouchP");
				}
				else
				{
					MicroConnection.sendEvent("TouchC");
				}
			}
		}
		if(line.getString("event").equals("LaunchDrone") && line.getString("Type").equals("Prospector"))
		{
			Thread.sleep(2500);
			MicroConnection.sendEvent("Prospector");
		}
		if(line.getString("event").equals("LaunchDrone") && line.getString("Type").equals("Collection"))
		{
			Thread.sleep(2500);
			MicroConnection.sendEvent("Collection");
		}
		if(line.getString("event").equals("StartJump"))
		{
//			Thread.sleep(5000);
			if(line.getString("JumpType").equals("Hyperspace"))
			{
				MicroConnection.sendEvent("StartHyper");
			}
			else if(line.getString("JumpType").equals("Supercruise"))
			{
				MicroConnection.sendEvent("StartSuper");
			}
		}
		if(line.getString("event").equals("Docked"))
		{
			MicroConnection.sendEvent("Docked");
		}
		if(line.getString("event").equals("HeatWarning"))
		{
			//MicroConnection.sendEvent("HeatWarning");
		}
		if(line.getString("event").equals("Undocked"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(line.getString("event").equals("Cargo"))
		{
			if(!lastLine.getString("event").equals("LaunchDrone"))
			{
				if(line.getString("Vessel").equals("SRV"))
				{
					MicroConnection.sendEvent("Cargo:"+(line.getInt("Count")/(2.0)));
				}
				else if(line.getString("Vessel").equals("Ship"))
				{
					MicroConnection.sendEvent("Cargo:"+(line.getInt("Count")/(cargoSpace)));
				}
			}
		}
		if(line.getString("event").equals("ModuleBuy"))
		{
			buyModule(line);
		}
		if(line.getString("event").equals("ShipTargeted"))
		{
			if(line.getBoolean("TargetLocked"))
			{
				if(line.has("ScanStage"))
				{
					if(line.getInt("ScanStage")==0)
					{
						MicroConnection.sendEvent("ScanStage0");
					}
					if(line.getInt("ScanStage")==1)
					{
						MicroConnection.sendEvent("ScanStage1");
					}
					if(line.getInt("ScanStage")==2)
					{
						MicroConnection.sendEvent("ScanStage2");
					}
					if(line.getInt("ScanStage")==3 && line.getString("LegalStatus").equals("Wanted"))
					{
						MicroConnection.sendEvent("ScanStageW");
					}
					else if(line.getInt("ScanStage")==3)
					{
						MicroConnection.sendEvent("ScanStageC");
					}
				}
			}
			else
			{
				MicroConnection.sendEvent("ScanCanceled");
			}
		}
		if(line.getString("event").equals("Shutdown"))
		{
			TaskbarIcon.setElite(false);
			MicroConnection.sendEvent("Shutdown");
			return true;
		}
		if(line.getString("event").equals("Loadout"))
		{
			updateLoadout(line);
		}
		if(line.getString("event").equals("DockSRV"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(line.getString("event").equals("LaunchSRV"))
		{
			MicroConnection.sendEvent("LaunchSRV");
		}
		if(line.getString("event").equals("HullDamage"))
		{
			MicroConnection.sendEvent("HealtH:"+healthHigh);
			MicroConnection.sendEvent("Health:"+line.getDouble("Health"));
			healthHigh = line.getDouble("Health");
		}
		if(line.getString("event").equals("Died"))
		{
			MicroConnection.sendEvent("HealtH:"+healthHigh);
			MicroConnection.sendEvent("Health:0.0");
		}
		if(line.getString("event").equals("Resurrect"))
		{
//			healthHigh = 1.0;
		}
		if(line.getString("event").equals("AsteroidCracked"))
		{
			Thread.sleep(2800);
			MicroConnection.sendEvent("AsteroidCracked");
		}
		lastLine = line;
		return false;
	}
	static void buyModule(JSONObject in)
	{
		if(in.has("SellItem"))
		{
			cargoSpace = cargoSpace - getSpaceFromName(in.getString("SellItem").replace("$", "").replace("_name;", ""));
		}
		cargoSpace = cargoSpace + getSpaceFromName(in.getString("BuyItem").replace("$", "").replace("_name;", ""));
		System.out.println("Cargo Space: "+cargoSpace);
	}
	static int getSpaceFromName(String name)
	{
		int am = 2;
		for(int i = 1; i < 11; i++)
		{
			if(name.toLowerCase().equals("int_cargorack_size"+i+"_class1"))
			{
				return am;
			}
			am = am * 2;
		}
		return 0;
	}
	static float cargoSpace = 0;
	static void updateLoadout(JSONObject in)
	{
		if(in.has("Modules"))
		{
			cargoSpace = 0;
			JSONArray modules = in.getJSONArray("Modules");
			for(int i = 0; i < modules.length(); i++)
			{
				//System.out.println(modules.getJSONObject(i).getString("Item"));
				cargoSpace = cargoSpace + getSpaceFromName(modules.getJSONObject(i).getString("Item"));
			}
			System.out.println("Cargo Space: "+cargoSpace);
		}
		if(in.has("HullHealth"))
		{
			healthHigh = in.getDouble("HullHealth");
		}
	}
	static void parseMusic(String track)
	{
		if(track.equals("MainMenu"))
		{
			MicroConnection.sendEvent("MainMenu");
		}
		if(track.equals("DestinationFromSupercruise"))
		{
			MicroConnection.sendEvent("Undocked");
		}
		if(track.equals("Supercruise"))
		{
			MicroConnection.sendEvent("SupercruiseEntry");
		}
		if(track.equals("DestinationFromHyperspace"))
		{
			MicroConnection.sendEvent("SupercruiseEntry");
		}
		if(track.equals("DockingComputer"))
		{
			MicroConnection.sendEvent("AutoDock");
		}
		if(track.equals("Combat_CapitalShip"))
		{
			MicroConnection.sendEvent("Capital");
		}
		else
		{
			if(lastLine.getString("event").equals("Music") && lastLine.getString("MusicTrack").equals("DockingComputer"))
			{
				MicroConnection.sendEvent("Undocked");
			}
		}
		if(track.equals("NoTrack") && lastLine.getString("event").equals("Undocked"))
		{
			MicroConnection.sendEvent("Undocked");
		}
	}
}
