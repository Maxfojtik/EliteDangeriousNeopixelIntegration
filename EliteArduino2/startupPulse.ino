void startupPulse()//pulse to do while game is starting
{
  if (var > 254 || var < 1)
  {
    var2 = !var2;
  }
  var = var + (var2 * 2 - 1)*2;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(var / 2, var / 2, var / 2);
  }
  readyToSwitch = var == 0;
}
