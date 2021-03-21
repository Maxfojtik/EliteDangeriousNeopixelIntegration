void material()
{
  notificationVar = notificationVar + 4;
  if(notificationVar%250>125)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(250, 80, 0);
    }
  }
  else
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = 0;
    }
  }
  if(notificationVar>=500)
  {
    notification = 0;
  }
}
