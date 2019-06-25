void material()
{
  notificationVar++;
  if(notificationVar%250>125)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, 250, 80, 0);
    }
  }
  else
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, 0);
    }
  }
  if(notificationVar>=500)
  {
    notification = 0;
  }
}
