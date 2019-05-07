void docked()//docked
{
  if (mode == renderMode)
  {
    if (var3 % 30 == 0)
    {
      int pixel = random(0, strip.numPixels());
      uint32_t color = strip.getPixelColor(pixel);
      if (color == 0)
      {
        strip.setPixelColor(pixel, Wheel(random(255)));
      }
      else
      {
        strip.setPixelColor(pixel, 0, 0, 0);
      }
      readyToSwitch = false;
    }
    var = 0;
  }
  else if (var3 % 10 == 0)
  {
    strip.setPixelColor(var, 0, 0, 0);
    strip.setPixelColor(strip.numPixels() - var, 0, 0, 0);
    var = var + 1;
    readyToSwitch = var == strip.numPixels() / 2 + 1;
  }
  var3 = var3 + 1;
}
