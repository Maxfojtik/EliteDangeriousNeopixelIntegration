void shieldsDown()
{
  if(notificationVar==0)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(sRed, sGreen, sBlue);
    }
  }
  leds[notificationVar/10] = 0;
  leds[NUM_LEDS-notificationVar/10] = 0;
  if(notificationVar/10==NUM_LEDS)
  {
    notification = 0;
  }
  notificationVar++;
}
