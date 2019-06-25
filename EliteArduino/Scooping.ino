void scooping()
{
  readyToSwitch = true;
  spot -= 4;
  float off = (spot + 0.0) / 20;
  for (int i = 0; i < strip.numPixels(); i++)
  {
    float val = ((sin((i - off) / 2) + 1) / 2);
    strip.setPixelColor(strip.numPixels()-i, strip.Color((int)(cRed*val), (int)(cGreen*val), (int)(cBlue*val)));
  }
}
