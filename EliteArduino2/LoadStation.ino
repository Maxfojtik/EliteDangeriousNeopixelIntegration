const int numSections = NUM_LEDS/4;
int splits[numSections];//where they split
int speeds[numSections];//speed of each should be equal to split nubers
int brights[numSections];//brightness of each should be equal to split nubers
int times[numSections];//brightness of each should be equal to split nubers
int minSize = NUM_LEDS/numSections/2;
int goodTime = -1;
int closestSplit(int split)
{
  int min = 10000;
  int mini = 0;
  for(int i = 0; i < numSections-1; i++)
  {
    if(abs(split-splits[i])<min && splits[i]!=-1)
    {
      min = abs(split-splits[i]);
      mini = i;
    }
  }
  return splits[mini];
}
// qsort requires you to create a sort function
int sort_ace(const void *cmp1, const void *cmp2)
{
  // Need to cast the void * to int *
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  // The comparison
  return a < b ? -1 : (a > b ? 1 : 0);
  // A simpler, probably faster way:
  //return b - a;
}
void stationServices()//docked
{
  if(var2!=-1)
  {
    loadStation();
  }
  else
  {
    if (var3 % 5 == 0)
    {
      int i = random(0, NUM_LEDS);
      if (!leds[i])
      {
        leds[i] = CRGB(cRed, cGreen, cBlue);
      }
      else
      {
        leds[i] = CRGB(0, 0, 0);
      }
      readyToSwitch = false;
    }
    var = 0;
  }
  readyToSwitch = true;
  var3 = var3 + 1;
}
void loadStation()
{
  if(var2==0)//just starting
  {
    for(int i = 0; i < numSections; i++)
    {
      splits[i] = -1;
      brights[i] = 0;
      speeds[i] = random(5,10);
      times[i] = random(1,100);
      goodTime = -1;
    }
    for(int i = 0; i < numSections-1; i++)
    {
      int ran = -1;
      while(abs(closestSplit(ran)-ran)<minSize || ran<minSize || ran>(NUM_LEDS-minSize) || ran==-1)
      {
        ran = random(0,NUM_LEDS);
      }
      splits[i] = ran;
    }
    int splits_length = sizeof(splits) / sizeof(splits[0]);
    // qsort - last parameter is a function pointer to the sort function
    qsort(splits, splits_length, sizeof(splits[0]), sort_ace);
    for(int i = 0; i < numSections-1; i++)
    {
      splits[i] = splits[i+1];
    }
  }
  boolean good = true;
  if(var2%2==0)
  {
    for(int i = 0; i < numSections; i++)
    {
      if(times[i]<=var2)
      {
        brights[i] = brights[i]+speeds[i];
      }
      if(brights[i]>=255)
      {
        brights[i] = 255;
      }
      else
      {
        good = false;
      }
  //    Serial.print(brights[i]);
  //    Serial.print(" ");
  //    Serial.print(speeds[i]);
  //    Serial.print("\t");
    }
  }
  else
  {
    good = false;
  }
  if(good && goodTime==-1)
  {
    goodTime = millis();
  }
//  Serial.print("\n");
  for(int i = 0; i < numSections-1; i++)
  {
//    Serial.print(splits[i]);
//    Serial.print("\t");
  }
//  Serial.print("\n");
  int splitNum = 0;
  for(int i = 0; i < NUM_LEDS; i++)
  {
    if(splitNum<numSections && i==splits[splitNum])
    {
      splitNum++;
    }
//    Serial.print(i);
//    Serial.print("\t");
//    Serial.print(splitNum);
//    Serial.print("\t");
//    Serial.println(brights[splitNum]);
    leds[i] = CRGB(cRed*brights[splitNum]/255.0, cGreen*brights[splitNum]/255.0, cBlue*brights[splitNum]/255.0);
  }
  var2++;
  if(millis()-goodTime>200 && goodTime!=-1)
  {
    var2 = -1;
  }
}
