void docked()//docked
{
  if (mode == renderMode)
  {
    if (var3 % 5 == 0)
    {
      int i = random(0, NUM_LEDS);
      if (!leds[i])
      {
        leds[i] = CHSV(random(255), 255, 255);
      }
      else
      {
        leds[i] = CRGB(0, 0, 0);
      }
      readyToSwitch = false;
    }
    var = 0;
  }
  else
  {
    leds[var] = 0;
    leds[NUM_LEDS - var] = 0;
    var = var + 1;
    readyToSwitch = var == NUM_LEDS / 2 + 1;
  }
  var3 = var3 + 1;
}
