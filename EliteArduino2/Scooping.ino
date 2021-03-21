void scooping()
{
  readyToSwitch = true;
  spot -= 4;
  float off = (spot + 0.0) / 20;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    float val = ((sin((i - off) / 2) + 1) / 2);
    leds[NUM_LEDS-i] = CRGB((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val));
  }
}
