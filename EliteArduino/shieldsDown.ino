void shieldsDown()
{
  if(notificationVar==0)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, sRed, sGreen, sBlue);
    }
  }
  strip.setPixelColor(notificationVar/10, 0);
  strip.setPixelColor(strip.numPixels()-notificationVar/10, 0);
  if(notificationVar/10==strip.numPixels())
  {
    notification = 0;
  }
  notificationVar++;
}
