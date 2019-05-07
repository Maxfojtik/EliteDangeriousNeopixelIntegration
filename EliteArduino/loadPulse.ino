void loadPulse()//pulse while game loads
{
  if (var3 % 2 == 0)
  {
    if (var > 254 || var < 1)
    {
      var2 = !var2;
    }
    var = var + (var2 * 2 - 1);
    for (int i = 0; i < strip.numPixels(); i++)
    {
      int red = 250;
      int green = 80;
      float multi = var/255.0;
      strip.setPixelColor(i, strip.Color(red*multi, green*multi, 0));
    }
  }
  readyToSwitch = var == 0;
  var3 = var3 + 1;
}
