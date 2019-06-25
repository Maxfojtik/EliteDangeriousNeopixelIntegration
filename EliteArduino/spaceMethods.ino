void normalSpace()//all the space methods like hyper space, witch space and normal space. kinda named wrong, sorry
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
void starthyper()
{
  var3 = 4-(var2/40);
  if(var3<-8)
  {
    var3 = -8;
    mode = 6;
  }
  var2++;

  spaceSpeed = var3;
  
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
void startsuper()
{
  var3 = 1+(var2/120);
  if(var3>=4)
  {
    var3 = 4;
    mode = 5;
  }
  var2++;

  spaceSpeed = var3;
  space();
  spot = spot + spaceSpeed;
  var = 1260;
}
void space()
{
  readyToSwitch = true;
  float off = (spot + 0.0) / 20;
  for (int i = 0; i < strip.numPixels() / 2 + 1; i++)
  {
    float val = ((sin((i - off) / 2) + 1) / 2);
    if (var / 20 - 3 > i)
    {
      strip.setPixelColor(i, strip.Color((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val)));
      strip.setPixelColor(strip.numPixels() - i, strip.Color((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val)));
    }
    else
    {
      /*strip.setPixelColor(i, 0);
        strip.setPixelColor(strip.numPixels()-i, 0);*/
    }
  }
}
