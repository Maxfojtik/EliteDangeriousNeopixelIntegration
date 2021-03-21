void requested()//request dock
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 255, 255);
  }
  readyToSwitch = true;
}
