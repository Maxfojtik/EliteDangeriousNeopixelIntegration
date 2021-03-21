void jetConeBoost()
{
  space();
  spaceSpeed = notificationVar/50+4;
  spot = spot + spaceSpeed;
  var = 1260;
  if(notificationVar>400)
  {
    notification = 0;
  }
  notificationVar++;
}
