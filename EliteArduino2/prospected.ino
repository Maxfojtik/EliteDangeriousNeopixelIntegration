void prospected()//asteroid prospected
{
  if(notificationVar==0)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0);
    }
  }
  int i = notificationVar/70;
  int bright = 1;
  leds[NUM_LEDS/2-i] = CRGB(cRed*bright, cGreen*bright, cBlue*bright);
  leds[NUM_LEDS/2+i] = CRGB(cRed*bright, cGreen*bright, cBlue*bright);
  if(i>5)
  {
    leds[NUM_LEDS/2-(i-6)] = 0;
    leds[NUM_LEDS/2+(i-6)] = 0;
  }
  if(i>NUM_LEDS/2)
  {
    notification = 0;
  }
  notificationVar++;
}
