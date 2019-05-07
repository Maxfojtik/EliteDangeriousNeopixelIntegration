void astr()//asteriod crack
{
  if (notificationVar % 5 == 0)
  {
    for (int i = 0; i < strip.numPixels(); i++)
    {
      if (random(2) == 1)
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(cRed, cGreen, cBlue));
      }
    }
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 1000)
  {
    notification = 0;
  }
}
