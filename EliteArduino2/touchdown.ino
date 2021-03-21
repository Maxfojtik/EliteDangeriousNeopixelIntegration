byte touchHue;
void touch(boolean player)//touchdown
{
  if(notificationVar==0)
  {
    touchHue = random(0,255);
  }
  float bright = notificationVar/20.0;
  if(notificationVar>20)
  {
    bright = (2020.0-notificationVar)/2000;
  }
  if(player)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(cRed*bright, cGreen*bright, cBlue*bright);
    }
  }
  else
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(touchHue, 255, bright*255);
    }
  }
  if(notificationVar>2020)
  {
    notification = 0;
  }
  notificationVar++;
}
