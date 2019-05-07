void prospect()//launch prospect drone
{
  /*if (notificationVar % 5 == 0 && notificationVar > 2500)
  {*/
    float pos = (notificationVar*2) / 500.0 * strip.numPixels();
    for (int i = 0; i < strip.numPixels(); i++)
    {
      if (abs(pos - i) < 2)
      {
        int bright = 127-abs(pos - i)*63;
        strip.setPixelColor(i, strip.Color(bright, bright, bright));
      }
      else
      {
        //strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
    //}
  }
  notificationVar = notificationVar + 1;
  //if (notificationVar > 3500)
  if (notificationVar > 500)
  {
    notification = 0;
  }
}
