void wingJoin()
{
  notificationVar++;
//  uint32_t wingColor = (notificationVar%200)<100 ? strip.Color(sRed/5, sGreen/5, sBlue/5) : 0; cant use in the conversion from adafruit to custom driver
  for(int i = 0; i < NUM_LEDS; i++)
  {
    if(notificationVar%200<100)
    {
      leds[i] = CRGB(sRed/5, sGreen/5, sBlue/5);
    }
    else
    {
      leds[i] = 0;
    }
  }
  if(notificationVar>300)
  {
    notification = 0;
  }
}
