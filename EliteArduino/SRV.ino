void SRV()//animation for SRV
{
  float pos = (var/2000.0)*strip.numPixels();
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (abs(pos - i) < 4)
    {
      int bright = (63*4)-abs(pos - i)*63;
      strip.setPixelColor(i, strip.Color(bright, bright, bright));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  var = var + var2;
  if(var2==0)
  {
    var2 = 1;
  }
  if(var>2000.0 || var<0)
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
