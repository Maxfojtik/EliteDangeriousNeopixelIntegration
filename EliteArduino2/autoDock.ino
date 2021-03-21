void autoDock()//auto docking computer
{
  if (mode == renderMode)
  {
    if (var3 % 3 == 0)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CHSV(((i * 256 / NUM_LEDS) + var) & 255, 255, 255);
      }
      var = var + 1;
      readyToSwitch = false;
    }
  }
  else if (var3 % 3 == 0)
  {
    leds[var2] = 0;
    leds[NUM_LEDS - var2] = 0;
    var2 = var2 + 1;
    readyToSwitch = var2 == NUM_LEDS / 2 + 1;
  }
  var3 = var3 + 1;
}
