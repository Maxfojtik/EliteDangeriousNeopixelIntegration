void autoDock()//auto docking computer
{
  if (mode == renderMode)
  {
    if (var3 % 30 == 0)
    {
      for (int i = 0; i < strip.numPixels(); i++)
      {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + var) & 255));
      }
      var = var + 1;
      readyToSwitch = false;
    }
  }
  else if (var3 % 10 == 0)
  {
    strip.setPixelColor(var2, 0, 0, 0);
    strip.setPixelColor(strip.numPixels() - var2, 0, 0, 0);
    var2 = var2 + 1;
    readyToSwitch = var2 == strip.numPixels() / 2 + 1;
  }
  var3 = var3 + 1;
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
