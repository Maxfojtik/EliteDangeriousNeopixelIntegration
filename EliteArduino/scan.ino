void scan(int stage)//0 = 0. 1 = 1. 2 = 2. 3 = clean. 4 = wanted, scan animation, used to be 3 stages, then converted to 2
{
  float pos = 0;
  if(stage<3)
  {
    if(notificationVar<1000)
    {
      /*if(stage == 0)
      {
        pos = (notificationVar) / 1000.0 * strip.numPixels()/3;
      }
      if(stage == 1)
      {
        pos = (notificationVar) / 1000.0 * strip.numPixels()/3+strip.numPixels()/3;
      }
      if(stage == 2)
      {
        pos = (notificationVar) / 1000.0 * strip.numPixels()/3+strip.numPixels()/3*2;
      }*/
      if(stage == 0)
      {
        pos = (notificationVar) / 1000.0 * strip.numPixels()/2;
      }
      if(stage == 1)
      {
        pos = (notificationVar) / 1000.0 * strip.numPixels()/2+strip.numPixels()/2;
      }
    }
    else
    {
      if(stage == 0)
      {
        pos = strip.numPixels()/2;
      }
      if(stage == 1)
      {
        pos = strip.numPixels();
      }
    }
    for (int i = 0; i < strip.numPixels(); i++)
    {
      if (i<pos)
      {
        strip.setPixelColor(i, strip.Color(127, 127, 127));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 65));
      }
    }
  }
  else
  {
    if(stage==4)
    {
      for (int i = 0; i < strip.numPixels(); i++)
      {
        if (notificationVar%255>127 || notificationVar>1000)
        {
          strip.setPixelColor(i, strip.Color(255, 0, 0));
        }
        else
        {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
      }
    }
    else
    {
      for (int i = 0; i < strip.numPixels(); i++)
      {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      }
    }
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 3000)
  {
    notification = 0;
  }
}
