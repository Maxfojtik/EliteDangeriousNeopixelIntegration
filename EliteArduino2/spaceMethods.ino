void normalSpace()//all the space methods like hyper space, witch space and normal space.
{
  space();
  spot = spot + spaceSpeed;
  if (spot > 1260)
  {
    var = 1260;
  }
  else
  {
    var = var + spaceSpeed;
  }
}
void superCruise()
{
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
void hyper()
{
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
int hyperMemory = 0;
void starthyper()
{
  var3 = 8-(hyperMemory/10);
  if(var3<=-16)
  {
    var3 = -16;
    mode = 6;
    hyperMemory = 0;
  }
  hyperMemory++;
//  Serial.print(var3);
//  Serial.print("\t");
//  Serial.println(var2);
  spaceSpeed = var3;
  
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
void startsuper()
{
  var3 = 4+(hyperMemory/30);
  if(var3>=8)
  {
    var3 = 8;
    mode = 5;
    hyperMemory = 0;
  }
  hyperMemory++;

  spaceSpeed = var3;
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
void space()
{
  readyToSwitch = true;
  float off = (spot + 0.0) / 20;
  for (int i = 0; i < NUM_LEDS / 2 + 1; i++)
  {
    float val = ((sin((i - off) / 2) + 1) / 2);
    if (var / 20 - 3 > i)
    {
      leds[i] = CRGB((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val));
      leds[NUM_LEDS - i] = CRGB((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val));
    }
    else
    {
      /*leds[i] = CRGB(0);
        strip.setPixelColor(NUM_LEDS-i, 0);*/
    }
  }
}
