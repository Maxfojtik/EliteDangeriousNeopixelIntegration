void showc()//show color
{
  for(int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, color);
  }
  readyToSwitch = true;
}
