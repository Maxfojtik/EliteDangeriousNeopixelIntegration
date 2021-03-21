void prospect()//launch prospect drone
{
  /*if (notificationVar % 5 == 0 && notificationVar > 2500)
  {*/
    float pos = (notificationVar*2) / 500.0 * NUM_LEDS;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (abs(pos - i) < 2)
      {
        int bright = 127-abs(pos - i)*63;
        leds[i] = CRGB(bright, bright, bright);
      }
      else
      {
        //leds[i] = CRGB(strip.Color(0, 0, 0));
      }
    //}
  }
  notificationVar = notificationVar + 1;
  //if (notificationVar > 3500)
  if (notificationVar > 500)
  {
    notification = 0;
  }
}
