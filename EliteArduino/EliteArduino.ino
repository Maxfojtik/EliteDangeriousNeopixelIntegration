#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUMPIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(127);
  pinMode(13, OUTPUT);
  digitalWrite(13, false);
}

String complied = "";
int color = 0;
int var = 0;
int var2 = 0;
int var3 = 0;
int mode = 0;
int renderMode = 0;
int spot = 0;
float amount = 0;
float amountH = 0;
int notification = 0;
int notificationVar = 0;
boolean readyToSwitch = false;
boolean statusLed = false;
float cRed = 0;
float cGreen = 0;
float cBlue = 255;

float cRedSpeed = 0;
float cGreenSpeed = 0;
float cBlueSpeed = 0;
int numSteps = 100;
float oldCRed = 0;
float oldCGreen = 0;
float oldCBlue = 0;
int stepCounter = 0;

int spaceSpeed = 4;
float sRed = 255;
float sGreen = 255;
float sBlue = 255;

boolean demo = 0;
long lastSwitch = 0;
boolean demoNotifications = false;
int lastNoti = -1;
void loop()
{
  if (!Serial)
  {
    color = 0;
    mode = 0;
  }
  else
  {
    if (Serial.available() > 0)
    {
      int proc = Serial.read();
      if (proc != 10)
      {
        complied += char(proc);
      }
      else
      {
        parse(complied);
        complied = "";
      }
    }
  }
  if(demo && millis()-lastSwitch>1000)
  {
    lastSwitch = millis();
    if(!demoNotifications)
    {
      mode++;
    }
    if(mode>15)
    {
      if(!demoNotifications)
      {
        mode = 4;
        spot = 1000;
        demoNotifications = true;
        amount = .5f;
        amountH = .75f;
      }
    }
  }
  if(demoNotifications)
  {
    Serial.println(notification);
    if(notification==0)
    {
      lastNoti++;
      if(lastNoti>18)
      {
        lastNoti = 0;
        mode = 0;
        demoNotifications = false;
      }
      else
      {
        notificationVar = 0;
        notification = lastNoti;
      }
    }
  }
  render();
}

void parse(String thing)//CARGO
{
  digitalWrite(13, statusLed);
  statusLed = !statusLed;
  if (thing == "PING")
  {
    Serial.println("pingElite");
  }
  if (thing.equals("Startup"))
  {
    mode = 1;
  }
  if (thing.equals("MainMenu"))
  {
    mode = 3;
  }
  if (thing.equals("LoadGame"))
  {
    mode = 2;
  }
  if (thing.equals("Docked"))
  {
    mode = 3;
  }
  if (thing.equals("Undocked"))
  {
    if (mode == 3)
    {
      spot = 0;
    }
    mode = 4;
    spaceSpeed = 1;
  }
  if (thing.equals("SupercruiseEntry"))
  {
    mode = 5;
    spaceSpeed = 4;
  }
  if (thing.equals("Hyper"))
  {
    mode = 6;
    spaceSpeed = -8;
  }
  if (thing.equals("DockingRequested"))
  {
    mode = 7;
  }
  if (thing.equals("DockingGranted"))
  {
    mode = 8;
  }
  if (thing.equals("DockingDenied"))
  {
    mode = 9;
  }
  if (thing.equals("HeatWarning"))
  {
    mode = 10;
  }
  if (thing.equals("AutoDock"))
  {
    mode = 11;
  }
  if (thing.equals("LaunchSRV"))
  {
    mode = 12;
  }
  if (thing.equals("StartHyper"))
  {
    mode = 13;
  }
  if (thing.equals("StartSuper"))
  {
    mode = 14;
  }
  if (thing.equals("AsteroidCracked"))
  {
    notification = 2;
    notificationVar = 0;
  }
  if (thing.equals("Shutdown"))
  {
    color = 0;
    mode = 0;
  }
  if (thing.equals("Prospector"))
  {
    notification = 3;
    notificationVar = 0;
  }
  if (thing.equals("Collection"))
  {
    notification = 4;
    notificationVar = 0;
  }
  if (thing.equals("ScanStage0"))
  {
    //notificationVar = 0;
    //notification = 5;
  }
  if (thing.equals("ScanStage1"))
  {
    notificationVar = 0;
    notification = 6;
  }
  if (thing.equals("ScanStage2"))
  {
    notificationVar = 0;
    notification = 7;
  }
  if (thing.equals("ScanStageC"))
  {
    notificationVar = 0;
    notification = 8;
  }
  if (thing.equals("ScanStageW"))
  {
    notificationVar = 0;
    notification = 9;
  }
  if (thing.equals("ScanCanceled"))
  {
    if(notification > 4 && notification < 10)
    {
      notification = 0;
    }
  }
  if (thing.equals("TouchP"))
  {
    notificationVar = 0;
    notification = 10;
  }
  if (thing.equals("TouchC"))
  {
    notificationVar = 0;
    notification = 11;
  }
  if (thing.equals("ProspectedAsteroid"))
  {
    notificationVar = 0;
    notification = 12;
  }
  if (thing.substring(0, 5).equals("Cargo"))
  {
    notification = 1;
    notificationVar = 0;
    amount = thing.substring(6).toFloat();
  }
  if (thing.substring(0, 1).equals("R"))
  {
    cRed = thing.substring(2).toFloat();
  }
  if (thing.substring(0, 1).equals("G"))
  {
    cGreen = thing.substring(2).toFloat();
  }
  if (thing.substring(0, 1).equals("B"))
  {
    cBlue = thing.substring(2).toFloat();
  }
  if (thing.substring(0, 2).equals("SR"))
  {
    sRed = thing.substring(3).toFloat();
  }
  if (thing.substring(0, 2).equals("SG"))
  {
    sGreen = thing.substring(3).toFloat();
  }
  if (thing.substring(0, 2).equals("SB"))
  {
    sBlue = thing.substring(3).toFloat();
  }
  if (thing.equals("Capital"))
  {
    notificationVar = 0;
    notification = 14;
  }
  if (thing.substring(0, 6).equals("Health"))
  {
    notification = 13;
    notificationVar = -1;
    amount = thing.substring(7).toFloat();
  }
  if (thing.substring(0, 6).equals("HealtH"))
  {
    amountH = thing.substring(7).toFloat();
  }
  if (thing.equals("ShieldsUp"))
  {
    notificationVar = 0;
    notification = 15;
  }
  if (thing.equals("ShieldsDown"))
  {
    notificationVar = 0;
    notification = 16;
  }
  if (thing.equals("OverH"))
  {
    notificationVar = 0;
    notification = 17;
  }
  if (thing.equals("CancelN"))
  {
    notificationVar = 0;
    notification = 0;
  }
  if (thing.equals("Station"))
  {
    notificationVar = 0;
    notification = 18;
  }
  if (thing.equals("FSSDiscoveryScan"))
  {
    notificationVar = 0;
    notification = 19;
  }
  if (thing.equals("JetConeBoost"))
  {
    notificationVar = 0;
    notification = 20;
  }
  if (thing.equals("Scooping"))
  {
    mode = 15;
  }
  if (thing.equals("MaterialCollected"))
  {
    notificationVar = 0;
    notification = 21;
  }
  if (thing.equals("Demo"))
  {
    demo = !demo;
  }
  if (thing.startsWith("AAS"))//Arrived At Star
  {
    oldCRed = cRed;
    oldCGreen = cGreen;
    oldCBlue = cBlue;
    uint32_t color = colorFromClass(thing.substring(3));
    cBlue = (color)&0xFF;
    cGreen = (color>>8)&0xFF;
    cRed = (color>>16)&0xFF;
    cRedSpeed = (oldCRed-cRed)/numSteps;
    cGreenSpeed = (oldCGreen-cGreen)/numSteps;
    cBlueSpeed = (oldCBlue-cBlue)/numSteps;
    stepCounter = numSteps+500;
  }
}
void render()
{
  if(stepCounter>0)
  {
    stepCounter--;
    if(stepCounter<numSteps)
    {
      cRed = cRed+cRedSpeed;
      cGreen = cGreen+cGreenSpeed;
      cBlue = cBlue+cBlueSpeed;
    }
  }
  else
  {
    if(oldCRed!=0 || oldCGreen!=0 || oldCBlue!=0)
    {
      cRed = oldCRed;
      cGreen = oldCGreen;
      cBlue = oldCBlue;
      oldCRed = 0;
      oldCGreen = 0;
      oldCBlue = 0;
    }
  }
  if (notification == 0)
  {
    if (renderMode == 0)
    {
      showc();
    }
    else if (renderMode == 1)
    {
      startupPulse();
    }
    else if (renderMode == 2)
    {
      loadPulse();
    }
    else if (renderMode == 3)
    {
      docked();
    }
    else if (renderMode == 4)
    {
      normalSpace();
    }
    else if (renderMode == 5)
    {
      superCruise();
    }
    else if (renderMode == 6)
    {
      hyper();
    }
    else if (renderMode == 7)
    {
      requested();
    }
    else if (renderMode == 8)
    {
      granted();
    }
    else if (renderMode == 9)
    {
      denied();
    }
    else if (renderMode == 10)
    {
      //heatWarning();
    }
    else if (renderMode == 11)
    {
      autoDock();
    }
    else if (renderMode == 12)
    {
      SRV();
    }
    else if (renderMode == 13)
    {
      starthyper();
    }
    else if (renderMode == 14)
    {
      startsuper();
    }
    else if (renderMode == 15)
    {
      scooping();
    }
    if (readyToSwitch && mode != renderMode)
    {
      Serial.print("Mode to ");
      Serial.println(mode);
      Serial.flush();
      renderMode = mode;
      var = 0;
      var2 = 0;
      var3 = 0;
    }
  }
  else
  {
    if (notification == 1)
    {
      showCargo();
    }
    else if (notification == 2)
    {
      astr();
    }
    else if (notification == 3)
    {
      renderMode = 4;
      mode = 4;
      normalSpace();
      prospect();
    }
    else if (notification == 4)
    {
      renderMode = 4;
      mode = 4;
      normalSpace();
      collect();
    }
    else if (notification == 5)
    {
      notification = 0;
      //scan(0);
    }
    else if (notification == 6)
    {
      scan(0);
    }
    else if (notification == 7)
    {
      scan(1);
    }
    else if (notification == 8)
    {
      scan(3);
    }
    else if (notification == 9)
    {
      scan(4);
    }
    else if (notification == 10)
    {
      touch(true);
    }
    else if (notification == 11)
    {
      touch(false);
    }
    else if (notification == 12)
    {
      prospected();
    }
    else if (notification == 13)
    {
      showHealth();
    }
    else if (notification == 14)
    {
      capital();
    }
    else if (notification == 15)
    {
      shieldsUp();
    }
    else if (notification == 16)
    {
      shieldsDown();
    }
    else if (notification == 17)
    {
      overHeat();
    }
    else if (notification == 18)
    {
      loadStation();
    }
    else if (notification == 19)
    {
      discoveryScan();
    }
    else if (notification == 20)
    {
      jetConeBoost();
    }
    else if (notification == 21)
    {
      material();
    }
  }
  strip.show();
}
uint32_t colorFromClass(String star)
{
  if(star=="O")
  {
    return strip.Color(165, 200, 255);
  }
  else if(star=="B")
  {
    return strip.Color(127, 165, 248);
  }
  else if(star=="A")
  {
    return strip.Color(255, 255, 255);
  }
  else if(star=="F")
  {
    return strip.Color(255, 226, 65);
  }
  else if(star=="G")
  {
    return strip.Color(255, 226, 0);
  }
  else if(star=="K")
  {
    return strip.Color(255, 127, 0);
  }
  else if(star=="M")
  {
    return strip.Color(255, 104, 74);
  }
  else if(star=="A_BlueWhiteSuperGiant")
  {
    return strip.Color(234, 238, 244);
  }
  else if(star=="F_WhiteSuperGiant")
  {
    return strip.Color(252, 240, 133);
  }
  else if(star=="K_OrangeGiant")
  {
    return strip.Color(242, 205, 97);
  }
  else if(star=="M_RedGiant")
  {
    return strip.Color(255, 104, 74);
  }
  else if(star=="M_RedSuperGiant")
  {
    return strip.Color(253, 112, 68);
  }
  else if(star=="AeBe")
  {
    return strip.Color(255, 249, 190);
  }
  else if(star=="TTS")
  {
    return strip.Color(254, 174, 92);
  }
  else if(star=="C")
  {
    return strip.Color(187, 14, 43);
  }
  else if(star=="CH")
  {
    return strip.Color(187, 14, 43);
  }
  else if(star=="CHd")
  {
    return strip.Color(187, 14, 43);
  }
  else if(star=="CJ")
  {
    return strip.Color(252, 127, 62);
  }
  else if(star=="CN")
  {
    return strip.Color(248, 159, 64);
  }
  else if(star=="CS")
  {
    return strip.Color(248, 159, 64);
  }
  else if(star=="MS")
  {
    return strip.Color(252, 144, 69);
  }
  else if(star=="S")
  {
    return strip.Color(255, 191, 88);
  }
  else if(star=="W")
  {
    return strip.Color(208, 244, 250);
  }
  else if(star=="WC")
  {
    return strip.Color(208, 244, 250);
  }
  else if(star=="WN")
  {
    return strip.Color(208, 244, 250);
  }
  else if(star=="WNC")
  {
    return strip.Color(254, 154, 78);
  }
  else if(star=="WO")
  {
    return strip.Color(208, 244, 250);
  }
  else if(star=="H")
  {
    return strip.Color(25, 25, 25);
  }
  else if(star=="SupermassiveBlackHole")
  {
    return strip.Color(25, 25, 25);
  }
  else if(star=="N")
  {
    return strip.Color(51, 107, 254);
  }
  else if(star.startsWith("D"))
  {
    return strip.Color(255, 255, 255);
  }
  else if(star=="L")
  {
    return strip.Color(255, 0, 0);
  }
  else if(star=="T")
  {
    return strip.Color(89, 13, 46);
  }
  else if(star=="Y")
  {
    return strip.Color(65, 8, 50);
  }
  else if(star=="X")
  {
    return strip.Color(218, 5, 120);
  }
  return 0;
}
