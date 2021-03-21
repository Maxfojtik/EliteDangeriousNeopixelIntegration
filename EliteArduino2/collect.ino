void collect()//collector limpet launch
{
    int pos = (int)((notificationVar) / 1000.0 * NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (abs(pos - i) < 2)
      {
        int bright = 127-abs(pos - i)*63;
        leds[i] = CRGB(bright, bright, 0);
      }
      else if (pos - i == -4)
      {
        leds[i] = CRGB(255, 0, 0);
      }
  }
  notificationVar = notificationVar + 4;
  //if (notificationVar > 3500)
  if (notificationVar > 1000)
  {
    notification = 0;
  }
}
