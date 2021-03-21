void showCargo()//show cargo
{
  float pos = NUM_LEDS;   
  if(notificationVar<400)
  {
    pos = (notificationVar/2) / 200.0 * NUM_LEDS;
  } 
  else if(notificationVar>800)
  {
    pos = ((1200-notificationVar)/2) / 200.0 * NUM_LEDS;
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < amount * NUM_LEDS && i<pos)
    {
      if(notificationVar>800 || ((pos)/NUM_LEDS)>amount)
      {
        leds[i] = getColorFromPercent(amount);
      }
      else
      {
        leds[i] = getColorFromPercent((pos)/NUM_LEDS);
      }
    }
    else
    {
      leds[i] = 0;
    }
  }
  notificationVar = notificationVar + 4;
  if (notificationVar > 1200)
  {
    notification = 0;
  }
}
CRGB getColorFromPercent(double percent)
{
  percent = 1-percent;
  double stage = (percent)*2;
  if(stage < 1)//red to yellow
  {
    return CRGB(255,(int) ((stage)*255),0);
  }
  else//yellow to green
  {
    return CRGB(255-(int) ((stage-1)*255),255,0);
  }
}
