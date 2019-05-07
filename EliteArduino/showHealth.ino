void showHealth()//show health, requires two communications to do correctly
{
  float pos = amountH * strip.numPixels();   
  if (notificationVar > 1200)
  {
    notification = 0;
    pos = -1;
  }
  else if(notificationVar>800)
  {
    pos = amount * strip.numPixels();
  } 
  else if(notificationVar>400)
  {
    pos = (200 - (notificationVar/2-200)) / 200.0 * strip.numPixels();
    if(pos>amountH * strip.numPixels())
    {
      pos = amountH * strip.numPixels();
    }
    if(pos < amount * strip.numPixels())
    {
      pos = amount * strip.numPixels();
    }
    notificationVar = notificationVar + 1;
  } 
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i<pos)
    {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  notificationVar = notificationVar + 1;
}
