void overHeat()
{
  float val = (sin(notificationVar/20.0f)+1)/2;
  for(int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 255*val, 0, 0);
  }
  notificationVar++;
}
