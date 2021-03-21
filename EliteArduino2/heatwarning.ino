void heatWarning()//unused
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (var % 10 > 5)
    {
      leds[i] = CRGB(255, 0, 0);
    }
    else
    {
      leds[i] = CRGB(0, 0, 0);
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
