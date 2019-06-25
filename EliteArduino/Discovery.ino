void discoveryScan()//asteriod crack
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    float muli = (100-notificationVar)/100.0;
    strip.setPixelColor(i, strip.Color(cRed*muli, cGreen*muli, cBlue*muli));
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 100)
  {
    notification = 0;
  }
}
