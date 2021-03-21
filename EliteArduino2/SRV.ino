void SRV()//animation for SRV
{
  float pos = (var/300.0)*NUM_LEDS;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (abs(pos - i) < (NUM_LEDS/15))
    {
      int bright = (63*4)-abs(pos - i)*63;
      leds[i] = CRGB(bright, bright, bright);
    }
    else
    {
      leds[i] = CRGB(0, 0, 0);
    }
  }
  var = var + var2;
  if(var2==0)
  {
    var2 = 1;
  }
  if(var>300.0 || var<0)
  {
    var2 = -var2;
    var = var + var2;
    readyToSwitch = true;
  }
  else
  {
    readyToSwitch = false;
  }
}
