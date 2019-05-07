void capital()//capital ship warp in
{
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if (notificationVar%1000>500 || notificationVar%333>111)
    {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    if (notificationVar > 20000)
    {
      notification = 0;
    }
  }
  notificationVar++;
}
