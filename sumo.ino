void setup() {
  #define lf 8
  #define lb 11
  #define rf 9
  #define rb 10
  #define ltrig 12
  #define lecho 13
  #define rtrig 6
  #define recho 7
  #define range 60

  pinMode(lf, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(ltrig, OUTPUT);
  pinMode(lecho, INPUT);
  pinMode(rtrig, OUTPUT);
  pinMode(recho, INPUT);

  digitalWrite(lf, LOW);
  digitalWrite(rf, LOW);
  digitalWrite(lb, LOW);
  digitalWrite(rb, LOW);
  digitalWrite(ltrig, LOW);
  digitalWrite(rtrig, LOW);
    
  delay(5000);
  while(readDistance(rtrig, recho)>range)
    turnLeft();
}

long readDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  return pulseIn(echoPin, HIGH)/58;
}

void turnLeft()
{
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(rf, HIGH);
}

void turnRight()
{
  digitalWrite(lb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
}

void moveForwards()
{
  digitalWrite(lb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(rf, HIGH);
}

bool lastleft=false, lastright=false;

void loop() {
    if(readDistance(ltrig, lecho)<=range)
    {
      lastleft=true;
      lastright=false;
    }
    if(readDistance(rtrig, recho)<=range)
    {
      lastleft=false;
      lastright=true;
    }
    
    if(lastleft&&readDistance(ltrig, lecho)>range)
    {
      while(readDistance(rtrig, recho)>range)
        turnLeft();
      lastright=true;
      lastleft=false;
    }
    else if(lastright&&readDistance(rtrig, recho)>range)
    {
      while(readDistance(ltrig, lecho)>range)
        turnRight();
      lastleft=true;
      lastright=false;
    }
    moveForwards();
}
