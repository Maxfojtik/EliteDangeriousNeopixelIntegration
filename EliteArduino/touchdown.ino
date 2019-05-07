void touch(boolean player)//touchdown
{
  if(notificationVar==0)
  {
    color = Wheel(random(0,255));
  }
  float bright = notificationVar/20.0;
  if(notificationVar>20)
  {
    bright = (2020.0-notificationVar)/2000;
  }
  if(player)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, cRed*bright, cGreen*bright, cBlue*bright);
    }
  }
  else
  {
    uint8_t r = color >> 16;
    uint8_t g = color >> 8;
    uint8_t b = color;
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, r*bright, g*bright, b*bright);
    }
  }
  if(notificationVar>2020)
  {
    notification = 0;
  }
  notificationVar++;
}
