void discoveryScan()//asteriod crack
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    float muli = (100-notificationVar)/100.0;
    leds[i] = CRGB(cRed*muli, cGreen*muli, cBlue*muli);
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 100)
  {
    notification = 0;
  }
}
