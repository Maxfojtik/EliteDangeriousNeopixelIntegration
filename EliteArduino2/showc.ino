void showc()//show color
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(color);
  }
  readyToSwitch = true;
}
