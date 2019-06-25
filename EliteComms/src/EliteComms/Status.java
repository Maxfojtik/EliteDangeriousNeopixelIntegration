package EliteComms;

import org.json.JSONObject;

public class Status 
{
	static int status = 0;
	static int oldStatus = 0;
	static int focus = 0;
	static int oldFocus = 0;
	static void update(JSONObject in)
	{
//		System.out.println("STAT UPDATED");
		if(status==0)//wait for proper data
		{
			status = in.getInt("Flags");
			oldStatus = status;
			if(in.has("GuiFocus"))
			{
				focus = in.getInt("GuiFocus");
				oldFocus = focus;
			}
		}
		else
		{
			oldStatus = status;
			status = in.getInt("Flags");
			if(in.has("GuiFocus"))
			{
				oldFocus = focus;
				focus = in.getInt("GuiFocus");
			}
			if(getShields(status)!=getShields(oldStatus))
			{
				if(getShields())
				{
					MicroConnection.sendEvent("ShieldsUp");
				}
				else
				{
					MicroConnection.sendEvent("ShieldsDown");
				}
			}
			if(getOverHeating(status)!=getOverHeating(oldStatus))
			{
				if(getOverHeating())
				{
					MicroConnection.sendEvent("OverH");
				}
				else
				{
					MicroConnection.sendEvent("CancelN");
				}
			}
			if(getScooping(status)!=getScooping(oldStatus))
			{
				if(getScooping())
				{
					MicroConnection.sendEvent("Scooping");
				}
				else
				{
					MicroConnection.sendEvent("SupercruiseEntry");
				}
			}
			if(focus==5 && oldFocus!=5)
			{
				MicroConnection.sendEvent("Station");
			}
		}
	}
	static boolean getBit(int n, int k) {
	    return ((n >> k) & 1)==1;
	}
	static boolean getShields(int stat)
	{
		return getBit(stat, 3);
	}
	static boolean getShields()
	{
		return getBit(status, 3);
	}
	static boolean getOverHeating(int stat)
	{
		return getBit(stat, 20);
	}
	static boolean getOverHeating()
	{
		return getBit(status, 20);
	}
	static boolean getScooping(int stat)
	{
		return getBit(stat, 11);
	}
	static boolean getScooping()
	{
		return getBit(status, 11);
	}
}
