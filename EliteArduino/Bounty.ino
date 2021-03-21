void bounty()//asteriod crack
{
  float muli = 0;
  if(notificationVar < 150)
  {
    muli = notificationVar/20.0;
  }
  if(notificationVar >= 150)
  {
    muli = 1.0-(notificationVar-150)/50.0;
  }
  if(muli>.5)
  {
    muli = .5;
  }
  if(muli<0)
  {
    muli = 0;
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(sRed*muli, sGreen*muli, sBlue*muli);
  }
  notificationVar = notificationVar + 1;
  if (notificationVar > 200)
  {
    notification = 0;
  }
}
