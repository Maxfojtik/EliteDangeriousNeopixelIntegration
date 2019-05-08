void showCargo()//show cargo
{
  float pos = strip.numPixels();   
  if(notificationVar<400)
  {
    pos = (notificationVar/2) / 200.0 * strip.numPixels();
  } 
  else if(notificationVar>800)
  {
    pos = ((1200-notificationVar)/2) / 200.0 * strip.numPixels();
  }
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i < amount * strip.numPixels() && i<pos)
    {
      if(notificationVar>800 || ((pos)/strip.numPixels())>amount)
      {
        strip.setPixelColor(i, getColorFromPercent(amount));
      }
      else
      {
        strip.setPixelColor(i, getColorFromPercent((pos)/strip.numPixels()));
      }
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 1200)
  {
    notification = 0;
  }
}
uint32_t getColorFromPercent(double percent)
{
  percent = 1-percent;
  double stage = (percent)*2;
  if(stage < 1)//red to yellow
  {
    return strip.Color(255,(int) ((stage)*255),0);
  }
  else//yellow to green
  {
    return strip.Color(255-(int) ((stage-1)*255),255,0);
  }
}
