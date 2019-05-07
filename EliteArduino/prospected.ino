void prospected()//asteroid prospected
{
  if(notificationVar==0)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
    strip.setPixelColor(i, 0);
    }
  }
  int i = notificationVar/70;
  int bright = 1;
  strip.setPixelColor(strip.numPixels()/2-i, cRed*bright, cGreen*bright, cBlue*bright);
  strip.setPixelColor(strip.numPixels()/2+i, cRed*bright, cGreen*bright, cBlue*bright);
  if(i>5)
  {
    strip.setPixelColor(strip.numPixels()/2-(i-6), 0);
    strip.setPixelColor(strip.numPixels()/2+(i-6), 0);
  }
  if(i>strip.numPixels()/2)
  {
    notification = 0;
  }
  notificationVar++;
}
