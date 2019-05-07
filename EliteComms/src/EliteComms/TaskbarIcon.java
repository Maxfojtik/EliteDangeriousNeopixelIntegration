package EliteComms;

import java.awt.AWTException;

import java.awt.Image;
import java.awt.SystemTray;
import java.awt.TrayIcon;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

/*
 * @author Maxwell Fojtik
 */

public class TaskbarIcon 
{
	static BufferedImage loadImage(String string) throws IOException
	{
		try {
			System.out.println("Loading image: " + string); 
			BufferedImage bufImg = ImageIO.read(TaskbarIcon.class.getResource(string));
		    BufferedImage convertedImg = new BufferedImage(bufImg.getWidth(), bufImg.getHeight(), BufferedImage.TYPE_INT_ARGB);
		    convertedImg.getGraphics().drawImage(bufImg, 0, 0, null);
		    return convertedImg;
	    } catch(IllegalArgumentException e) {
			throw new IOException();
		}
	}
	static boolean elite = false;
	static boolean connection = false;
	static void setElite(boolean state)//0 = disconnected, 1 = connected, connected but eliteClosed = 3, disconnected but eliteOpen = 4
	{
		elite = state;
		updateTray();
	}
	static void setConnection(boolean state)//0 = disconnected, 1 = connected, connected but eliteClosed = 3, disconnected but eliteOpen = 4
	{
		connection = state;
		updateTray();
	}
	static void updateTray()
	{
		if(connection && elite)
		{
			trayIcon.setImage(imgs[1]);
		}
		else if(!connection && elite)
		{
			trayIcon.setImage(imgs[3]);
		}
		else if(connection && !elite)
		{
			trayIcon.setImage(imgs[2]);
		}
		else
		{
			trayIcon.setImage(imgs[0]);
		}
	}
	static Image[] imgs;
	static TrayIcon trayIcon;
	public TaskbarIcon() throws IOException, AWTException
	{
		SystemTray tray = SystemTray.getSystemTray();
	    Image CC = loadImage("/CC.png");//1
	    Image CD = loadImage("/CD.png");//3
	    Image DD = loadImage("/DD.png");//0
	    Image DC = loadImage("/DC.png");//2
	    imgs = new Image[] {DD,CC,DC,CD};
	    trayIcon = new TrayIcon(DD, "");
	    trayIcon.setImageAutoSize(true);
	    tray.add(trayIcon);
	    trayIcon.addMouseListener(new MouseAdapter() 
    	{
    	    public void mouseClicked(MouseEvent e) 
    	    {
    	        if (e.getButton() == MouseEvent.BUTTON1) 
    	        {
    	        	
    	        }
    	        if (e.getButton() == MouseEvent.BUTTON3) 
    	        {
    	        	MicroConnection.disconnect();
            		tray.remove(trayIcon);
        			System.exit(0);
    	        }
    	    }
    	});        
	}
}
