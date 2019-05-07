void startupPulse()//pulse to do while game is starting
{
  if (var3 % 3 == 0)
  {
    if (var > 254 || var < 1)
    {
      var2 = !var2;
    }
    var = var + (var2 * 2 - 1);
    for (int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(var / 2, var / 2, var / 2));
    }
  }
  readyToSwitch = var == 0;
  var3 = var3 + 1;
}
