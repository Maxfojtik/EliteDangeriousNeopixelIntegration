#include <FastLED.h>


//#####CONFIG VALUES

#define DATA_PINL 3
#define DATA_PINR 4
#define NUM_LEDS 46
#define BRIGHTNESS 255

//#####END CONFIG


CRGB leds[NUM_LEDS];

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
void setup() {
  Serial.begin(9600);
  LEDS.addLeds<WS2812, DATA_PINL, GRB>(leds, NUM_LEDS);
  LEDS.addLeds<WS2812,DATA_PINR,GRB>(leds, NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
//  FastLED.setMaxPowerInVoltsAndMilliamps(5, 100);
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
int numSteps = 300;
float oldCRed = 0;
float oldCGreen = 0;
float oldCBlue = 0;
int stepCounter = 0;

int spaceSpeed = 4;
float sRed = 255;
float sGreen = 255;
float sBlue = 255;

boolean wasConnected = false;

boolean demo = 0;
long lastSwitch = 0;
boolean demoNotifications = false;
int lastNoti = -1;
long lastFrame = 0;

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
      if(lastNoti>23)
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
  if(millis()-lastFrame>16)
  {
//    Serial.println(millis()-lastFrame);
    lastFrame = millis();
    render();
  }
}

void parse(String thing)//CARGO
{
  digitalWrite(13, statusLed);
  statusLed = !statusLed;
  if (thing == "PING")
  {
    Serial.println(F("pingElite"));
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 255, 0);
    }
    LEDS.show();
    delay(100);
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 0, 0);
    }
    LEDS.show();
  }
  else if (thing.equals(F("Startup")))
  {
    mode = 1;
  }
  else if (thing.equals(F("MainMenu")))
  {
    mode = 3;
  }
  else if (thing.equals(F("LoadGame")))
  {
    mode = 2;
  }
  else if (thing.equals(F("Docked")))
  {
    mode = 3;
  }
  else if (thing.equals(F("Undocked")))
  {
    if (mode == 3)
    {
      spot = 0;
    }
    mode = 4;
    spaceSpeed = 4;
  }
  else if (thing.equals(F("SupercruiseEntry")))
  {
    mode = 5;
    spaceSpeed = 8;
  }
  else if (thing.equals(F("Hyper")))
  {
    mode = 6;
    spaceSpeed = -16;
  }
  else if (thing.equals(F("DockingRequested")))
  {
    mode = 7;
  }
  else if (thing.equals(F("DockingGranted")))
  {
    mode = 8;
  }
  else if (thing.equals(F("DockingDenied")))
  {
    mode = 9;
  }
  else if (thing.equals(F("HeatWarning")))
  {
    mode = 10;
  }
  else if (thing.equals(F("AutoDock")))
  {
    mode = 11;
  }
  else if (thing.equals(F("LaunchSRV")))
  {
    mode = 12;
  }
  else if (thing.equals(F("StartHyper")))
  {
    var3 = 0;
    var2 = 0;
    mode = 13;
  }
  else if (thing.equals(F("StartSuper")))
  {
    var3 = 0;
    var2 = 0;
    mode = 14;
  }
  else if (thing.equals(F("StationServices")))
  {
    var2 = 0;
    mode = 16;
  }
  else if (thing.equals(F("OutStationServices")))
  {
    mode = 3;
  }
  else if (thing.equals(F("AsteroidCracked")))
  {
    notification = 2;
    notificationVar = 0;
  }
  else if (thing.equals(F("Shutdown")))
  {
    color = 0;
    mode = 0;
  }
  else if (thing.equals(F("Prospector")))
  {
    notification = 3;
    notificationVar = 0;
  }
  else if (thing.equals(F("Collection")))
  {
    notification = 4;
    notificationVar = 0;
  }
  else if (thing.equals(F("ScanStage0")))
  {
    //notificationVar = 0;
    //notification = 5;
  }
  else if (thing.equals(F("ScanStage1")))
  {
    notificationVar = 0;
    notification = 6;
  }
  else if (thing.equals(F("ScanStage2")))
  {
    notificationVar = 0;
    notification = 7;
  }
  else if (thing.equals(F("ScanStageC")))
  {
    notificationVar = 0;
    notification = 8;
  }
  else if (thing.equals(F("ScanStageW")))
  {
    notificationVar = 0;
    notification = 9;
  }
  else if (thing.equals(F("ScanCanceled")))
  {
    if(notification > 4 && notification < 10)
    {
      notification = 0;
    }
  }
  else if (thing.equals(F("TouchP")))
  {
    notificationVar = 0;
    notification = 10;
  }
  else if (thing.equals(F("TouchC")))
  {
    notificationVar = 0;
    notification = 11;
  }
  else if (thing.equals(F("ProspectedAsteroid")))
  {
    notificationVar = 0;
    notification = 12;
  }
  else if (thing.substring(0, 5).equals(F("Cargo")))
  {
    notification = 1;
    notificationVar = 0;
    amount = thing.substring(6).toFloat();
  }
  else if (thing.substring(0, 1).equals("R"))
  {
    cRed = thing.substring(2).toFloat();
  }
  else if (thing.substring(0, 1).equals("G"))
  {
    cGreen = thing.substring(2).toFloat();
  }
  else if (thing.substring(0, 1).equals("B"))
  {
    cBlue = thing.substring(2).toFloat();
  }
  else if (thing.substring(0, 2).equals("SR"))
  {
    sRed = thing.substring(3).toFloat();
  }
  else if (thing.substring(0, 2).equals("SG"))
  {
    sGreen = thing.substring(3).toFloat();
  }
  else if (thing.substring(0, 2).equals("SB"))
  {
    sBlue = thing.substring(3).toFloat();
  }
  else if (thing.equals(F("Capital")))
  {
    notificationVar = 0;
    notification = 14;
  }
  else if (thing.substring(0, 6).equals(F("Health")))
  {
    notification = 13;
    notificationVar = -1;
    amount = thing.substring(7).toFloat();
  }
  else if (thing.substring(0, 6).equals(F("HealtH")))
  {
    amountH = thing.substring(7).toFloat();
  }
  else if (thing.equals(F("ShieldsUp")))
  {
    notificationVar = 0;
    notification = 15;
  }
  else if (thing.equals(F("ShieldsDown")))
  {
    notificationVar = 0;
    notification = 16;
  }
  else if (thing.equals(F("OverH")))
  {
    notificationVar = 0;
    notification = 17;
  }
  else if (thing.equals(F("CancelN")))
  {
    notificationVar = 0;
    notification = 0;
  }
//  else if (thing.equals(F("Station")))
//  {
//    notificationVar = 0;
//    notification = 18;
//  }
  else if (thing.equals(F("FSSDiscoveryScan")))
  {
    notificationVar = 0;
    notification = 19;
  }
  else if (thing.equals(F("JetConeBoost")))
  {
    notificationVar = 0;
    notification = 20;
  }
  else if (thing.equals(F("Scooping")))
  {
    mode = 15;
  }
  else if (thing.equals(F("MaterialCollected")))
  {
    notificationVar = 0;
    notification = 21;
  }
  else if (thing.equals(F("WingJoin")))
  {
    notificationVar = 0;
    notification = 22;
  }
  else if (thing.equals(F("Ounty")))
  {
    notificationVar = 0;
    notification = 23;
  }
  else if (thing.equals(F("Demo")))
  {
    demo = !demo;
  }
  else if (thing.startsWith(F("AAS")))//Arrived At Star
  {
    oldCRed = cRed;
    oldCGreen = cGreen;
    oldCBlue = cBlue;
    uint32_t color = colorFromClass(thing.substring(3));
    Serial.println(color);
    cBlue = (color)&0xFF;
    cGreen = (color>>8)&0xFF;
    cRed = (color>>16)&0xFF;
    Serial.println(cRed);
    Serial.println(cGreen);
    Serial.println(cBlue);
    cRedSpeed = (oldCRed-cRed)/numSteps;
    cGreenSpeed = (oldCGreen-cGreen)/numSteps;
    cBlueSpeed = (oldCBlue-cBlue)/numSteps;
    stepCounter = numSteps+700;
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
    else if (renderMode == 16)
    {
      stationServices();
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
    Serial.println(notification);
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
    else if (notification == 22)
    {
      wingJoin();
    }
    else if (notification == 23)
    {
      bounty();
    }
  }
  LEDS.show();
}
uint32_t colorToInt(uint8_t red, uint8_t green, uint8_t blue) {
  return (red << 16) | (green << 8) | blue;
}
uint32_t colorFromClass(String star)
{
  if(star=="O")
  {
    return colorToInt(165, 200, 255);
  }
  else if(star=="B")
  {
    return colorToInt(127, 165, 248);
  }
  else if(star=="A")
  {
    return colorToInt(255, 255, 255);
  }
  else if(star=="F")
  {
    return colorToInt(255, 226, 65);
  }
  else if(star=="G")
  {
    return colorToInt(255, 226, 0);
  }
  else if(star=="K")
  {
    return colorToInt(255, 127, 0);
  }
  else if(star=="M")
  {
    return colorToInt(255, 104, 74);
  }
  else if(star=="A_BlueWhiteSuperGiant")
  {
    return colorToInt(234, 238, 244);
  }
  else if(star=="F_WhiteSuperGiant")
  {
    return colorToInt(252, 240, 133);
  }
  else if(star=="K_OrangeGiant")
  {
    return colorToInt(242, 205, 97);
  }
  else if(star=="M_RedGiant")
  {
    return colorToInt(255, 104, 74);
  }
  else if(star=="M_RedSuperGiant")
  {
    return colorToInt(253, 112, 68);
  }
  else if(star=="AeBe")
  {
    return colorToInt(255, 249, 190);
  }
  else if(star=="TTS")
  {
    return colorToInt(254, 174, 92);
  }
  else if(star=="C")
  {
    return colorToInt(187, 14, 43);
  }
  else if(star=="CH")
  {
    return colorToInt(187, 14, 43);
  }
  else if(star=="CHd")
  {
    return colorToInt(187, 14, 43);
  }
  else if(star=="CJ")
  {
    return colorToInt(252, 127, 62);
  }
  else if(star=="CN")
  {
    return colorToInt(248, 159, 64);
  }
  else if(star=="CS")
  {
    return colorToInt(248, 159, 64);
  }
  else if(star=="MS")
  {
    return colorToInt(252, 144, 69);
  }
  else if(star=="S")
  {
    return colorToInt(255, 191, 88);
  }
  else if(star=="W")
  {
    return colorToInt(208, 244, 250);
  }
  else if(star=="WC")
  {
    return colorToInt(208, 244, 250);
  }
  else if(star=="WN")
  {
    return colorToInt(208, 244, 250);
  }
  else if(star=="WNC")
  {
    return colorToInt(254, 154, 78);
  }
  else if(star=="WO")
  {
    return colorToInt(208, 244, 250);
  }
  else if(star=="H")
  {
    return colorToInt(25, 25, 25);
  }
  else if(star=="SupermassiveBlackHole")
  {
    return colorToInt(25, 25, 25);
  }
  else if(star=="N")
  {
    return colorToInt(51, 107, 254);
  }
  else if(star.startsWith("D"))
  {
    return colorToInt(255, 255, 255);
  }
  else if(star=="L")
  {
    return colorToInt(255, 0, 0);
  }
  else if(star=="T")
  {
    return colorToInt(89, 13, 46);
  }
  else if(star=="Y")
  {
    return colorToInt(65, 8, 50);
  }
  else if(star=="X")
  {
    return colorToInt(218, 5, 120);
  }
  return 0;
}
