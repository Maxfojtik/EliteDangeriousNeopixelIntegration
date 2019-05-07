void heatWarning()//unused
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (var % 10 > 5)
    {
      strip.setPixelColor(i, 255, 0, 0);
    }
    else
    {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  var = var + 1;
  if (var > 2000)
  {
    mode = 4;
    readyToSwitch = true;
    return;
  }
}
