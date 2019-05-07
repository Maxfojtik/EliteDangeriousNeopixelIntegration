void denied()//docking deinded
{
  if (mode == renderMode)
  {
    for (int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, 255, 0, 0);
    }
    var = var + 1;
    if (var > 2000)
    {
      mode = 4;
      var = 0;
    }
    readyToSwitch = false;
  }
  else if (var3 % 15 == 0)
  {
    strip.setPixelColor(var, 0, 0, 0);
    strip.setPixelColor(strip.numPixels() - var, 0, 0, 0);
    var = var + 1;
    spot = 0;
    readyToSwitch = var == strip.numPixels() / 2 + 1;
  }
  var3 = var3 + 1;
  readyToSwitch = true;
}
