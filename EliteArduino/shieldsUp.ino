void shieldsUp()
{
  if(notificationVar==0)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, 0);
    }
  }
  strip.setPixelColor(strip.numPixels()/2+notificationVar/10, sRed, sGreen, sBlue);
  strip.setPixelColor(strip.numPixels()/2-notificationVar/10, sRed, sGreen, sBlue);
  if(strip.numPixels()/2+notificationVar/10==strip.numPixels())
  {
    notification = 0;
  }
  notificationVar++;
}
