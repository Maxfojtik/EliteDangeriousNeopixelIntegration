void granted()//docking granted
{
  if (mode == renderMode)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 255, 0);
    }
    readyToSwitch = false;
    var = 0;
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
}
