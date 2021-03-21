void scan(int stage)//0 = 0. 1 = 1. 2 = 2. 3 = clean. 4 = wanted, scan animation, used to be 3 stages, then converted to 2
{
  float pos = 0;
  if(stage<3)
  {
    if(notificationVar<1000)
    {
      /*if(stage == 0)
      {
        pos = (notificationVar) / 1000.0 * NUM_LEDS/3;
      }
      if(stage == 1)
      {
        pos = (notificationVar) / 1000.0 * NUM_LEDS/3+NUM_LEDS/3;
      }
      if(stage == 2)
      {
        pos = (notificationVar) / 1000.0 * NUM_LEDS/3+NUM_LEDS/3*2;
      }*/
      if(stage == 0)
      {
        pos = (notificationVar) / 1000.0 * NUM_LEDS/2;
      }
      if(stage == 1)
      {
        pos = (notificationVar) / 1000.0 * NUM_LEDS/2+NUM_LEDS/2;
      }
    }
    else
    {
      if(stage == 0)
      {
        pos = NUM_LEDS/2;
      }
      if(stage == 1)
      {
        pos = NUM_LEDS;
      }
    }
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (i<pos)
      {
        leds[i] = CRGB(127, 127, 127);
      }
      else
      {
        leds[i] = CRGB(0, 0, 65);
      }
    }
  }
  else
  {
    if(stage==4)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        if (notificationVar%255>127 || notificationVar>1000)
        {
          leds[i] = CRGB(255, 0, 0);
        }
        else
        {
          leds[i] = CRGB(0, 0, 0);
        }
      }
    }
    else
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB(0, 255, 0);
      }
    }
  }
  notificationVar = notificationVar + 4;
  if (notificationVar > 3000)
  {
    notification = 0;
  }
}
