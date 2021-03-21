void capital()//capital ship warp in
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    if (notificationVar%1000>500 || notificationVar%333>111)
    {
      leds[i] = CRGB(255, 0, 0);
    }
    else
    {
      leds[i] = CRGB(0, 0, 0);
    }
    if (notificationVar > 20000 || (demoNotifications && notificationVar > 2000))
    {
      notification = 0;
    }
  }
  notificationVar++;
}
