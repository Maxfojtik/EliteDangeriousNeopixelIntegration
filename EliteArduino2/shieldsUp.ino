void shieldsUp()
{
  if(notificationVar==0)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0);
    }
  }
  leds[NUM_LEDS/2+notificationVar/2] = CRGB(sRed, sGreen, sBlue);
  leds[NUM_LEDS/2-notificationVar/2] = CRGB(sRed, sGreen, sBlue);
  if(NUM_LEDS/2+notificationVar/2==NUM_LEDS)
  {
    notification = 0;
  }
  notificationVar++;
}
