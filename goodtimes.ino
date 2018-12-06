int greenLED = D0;
int redLED = D1;
int switch1 = D5;
int switch2 = D6;
int buzzer = A4;
int isSwitchPressed = 0;
int startTime;
int stopTime;
int escapedTime;
int mean, range;
int count=0;
int increment =0;
int maxescaped=0, minescaped = 2147483647;
int16_t values[3000];

int resets(String command) {
 isSwitchPressed = 0;
 startTime = 0;
 stopTime = 0;
 escapedTime = 0;
 mean =0 ;
 range =0;
 count=0;
 increment =0;
 return 0;
}

int RollBack(String command) {
   if(sizeof(values) > 1){
   int tempmax =0, tempmin=0, temprange =0, sumvalue =0, tempincr=0;
   for(int k=0;k<count-2;k++)
   {
       sumvalue = sumvalue + values[k]; 
       tempincr = tempincr + 1;
       
    if(tempmax < values[k])
    {
        tempmax = values[k];
    }
    if(tempmin > values[k])
    {
        tempmin = values[k];
    }
   }
   mean = sumvalue/tempincr;
   range = tempmax - tempmin;
   escapedTime = values[count-2];
    Serial.printf("mean:= %d\t range:%d\t recent: %d\n",mean,range,escapedTime);
   }
   return 0; 
}

void setup() {
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(switch2, INPUT_PULLUP);
    pinMode(buzzer, AN_INPUT);
    Serial.begin(9600);
    Particle.function("resetStat", resets);
    Particle.function("rollback", RollBack);
    Particle.variable("recent", escapedTime);
    Particle.variable("mean", mean);
    Particle.variable("range", range);
    Particle.variable("val", values);
    digitalWrite(redLED, HIGH);
}

void loop() {
if(digitalRead(switch1) == LOW && isSwitchPressed == 0)
{
   // digitalWrite(greenLED, HIGH);
    delay(rand() % 1000 + 1000);
    startTime = millis();
//    digitalWrite(greenLED, LOW);
    isSwitchPressed = 1;
    tone(buzzer, 3000, 200);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    
}
if(digitalRead(switch1) == HIGH && isSwitchPressed == 1)
{
    isSwitchPressed = 0;
}
if(digitalRead(switch2) == LOW && isSwitchPressed == 0)
{
   // digitalWrite(greenLED, HIGH);
    delay(rand() % 1000 + 1000);
    stopTime = millis();
    escapedTime = stopTime - startTime;
    Serial.printf("EscapedTime:= %d\n",escapedTime);
//    digitalWrite(greenLED, LOW);
    isSwitchPressed = 1;
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    delay(1000);
    Serial.printf("Count: = %d\n", count);
    values[count] = escapedTime;
    count = count + 1;
        Serial.printf("Values: = %d\n", values[0]);

    increment = increment + escapedTime;
    
    if(maxescaped < escapedTime)
    {
        maxescaped = escapedTime;
    }
    if(minescaped > escapedTime)
    {
        minescaped = escapedTime;
    }
}
if(digitalRead(switch2) == HIGH && isSwitchPressed == 1)
{
    isSwitchPressed = 0;
    mean = (increment/count);
    range = maxescaped - minescaped;
}
}