void requested()//request dock
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 255, 255, 255);
  }
  readyToSwitch = true;
}
