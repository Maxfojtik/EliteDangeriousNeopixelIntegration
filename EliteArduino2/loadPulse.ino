void loadPulse()//pulse while game loads
{
  if (var > 254 || var < 1)
  {
    var2 = !var2;
  }
  var = var + (var2 * 2 - 1) * 3;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    int red = 250;
    int green = 80;
    float multi = var/255.0;
    leds[i] = CRGB(red*multi, green*multi, 0);
  }
  readyToSwitch = var == 0;
}
