void showHealth()//show health, requires two communications to do correctly
{
  float pos = amountH * NUM_LEDS;   
  if (notificationVar > 1200)
  {
    notification = 0;
    pos = -1;
  }
  else if(notificationVar>800)
  {
    pos = amount * NUM_LEDS;
  } 
  else if(notificationVar>400)
  {
    pos = (200 - (notificationVar/2-200)) / 200.0 * NUM_LEDS;
    if(pos>amountH * NUM_LEDS)
    {
      pos = amountH * NUM_LEDS;
    }
    if(pos < amount * NUM_LEDS)
    {
      pos = amount * NUM_LEDS;
    }
    notificationVar = notificationVar + 1;
  } 
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i<pos)
    {
      leds[i] = CRGB(255, 0, 0);
    }
    else
    {
      leds[i] = CRGB(0, 0, 0);
    }
  }
  notificationVar = notificationVar + 1;
}
