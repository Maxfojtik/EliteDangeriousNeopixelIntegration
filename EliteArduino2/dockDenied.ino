void denied()//docking deinded
{
  if (mode == renderMode)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(255, 0, 0);
    }
    var = var + 1;
    if (var > 2000)
    {
      mode = 4;
      var = 0;
    }
    readyToSwitch = false;
  }
  else if (var3 % 3 == 0)
  {
    leds[var] = 0;
    leds[NUM_LEDS - var] = 0;
    var = var + 1;
    spot = 0;
    readyToSwitch = var == NUM_LEDS / 2 + 1;
  }
  var3 = var3 + 1;
  readyToSwitch = true;
}
