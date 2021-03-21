void astr()//asteriod crack
{
  if (notificationVar % 5 == 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (random(2) == 1)
      {
        leds[i] = CRGB(0, 0, 0);
      }
      else
      {
        leds[i] = CRGB(cRed, cGreen, cBlue);
      }
    }
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 1000)
  {
    notification = 0;
  }
}
