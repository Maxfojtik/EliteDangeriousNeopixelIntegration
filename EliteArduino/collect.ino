void collect()//collector limpet launch
{
    int pos = (int)((notificationVar) / 1000.0 * strip.numPixels());
    for (int i = 0; i < strip.numPixels(); i++)
    {
      if (abs(pos - i) < 2)
      {
        int bright = 127-abs(pos - i)*63;
        strip.setPixelColor(i, strip.Color(bright, bright, 0));
      }
      else if (pos - i == -4)
      {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
  }
  notificationVar = notificationVar + 1;
  //if (notificationVar > 3500)
  if (notificationVar > 1000)
  {
    notification = 0;
  }
}
