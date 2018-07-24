  int joyPin1 = A0;                 // slider variable connecetd to analog pin 0
  int joyPin2 = A1;                 // slider variable connecetd to analog pin 1
  int tiltPin = 6;
  int pushPin = 13;
  
  int ledPins[] = {2,3,4};
  
  int row[] = {8,9};
  int col[] = {10,11};
  int i,j;
  int col_scan;
  int key = 0;
  
  int value1 = 0;                  // variable to read the value from the analog pin 0
  int value2 = 0;                  // variable to read the value from the analog pin 1
  int tiltValue = 0;
  int x = 0;
  int y = 0;
  int tilt = 0;
  int previousState = 0;

  int interval = 1000;
  unsigned long previousMillis = 0;


void setup() {
   Serial.begin(9600);
    pinMode(pushPin, INPUT);
    pinMode(tiltPin, INPUT);
    digitalWrite(pushPin, HIGH);

    for(i=0;i<=1;i++)
    {
    pinMode(row[i],OUTPUT);
    pinMode(col[i],INPUT);
    digitalWrite(col[i],HIGH);
    }
  }

/* data translator */
int treatValue(int data) {
   return (data * 9 / 1024 - 4);
  }
int treatValue2(int data) {
   return (data * 9 / 1024 - 4);
  }
int treatValue3(int data) {
   return (data);
  }


void loop() {
 /* reader */
   value1 = analogRead(joyPin1);   
   delay(20);             
   value2 = analogRead(joyPin2);
   delay(20);
   tiltValue = digitalRead(tiltPin);
   delay(10);
   x = treatValue(value2);
   y = treatValue2(value1);
   tilt = treatValue3(tiltValue);
   push();


/* processing sensor */
int input = Serial.read();
    switch (input)
    {
      case 1:
        if(input == 1)
        {
          tone(5, 440, 15);
          indicate();
        }
      case 2:
        if(input == 2)
        {
          tone(5, 220, 15);
          indicate();
        }        
    }


/* keypad */

for(i=0;i<=1;i++)
  {
    digitalWrite(row[0],HIGH);
     digitalWrite(row[1],HIGH);
        digitalWrite(row[i],LOW);
          
       for(j=0;j<=1;j++)
       {
        col_scan=digitalRead(col[j]);
        if(col_scan==LOW)
        {
          keypress(i,j);
          delay(10);
        }
       }
  }
}

void indicate(){
      pinMode(2,OUTPUT);  //LED 1
      pinMode(4,OUTPUT); 
      pinMode(3,INPUT);
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      delay(3);

     
      pinMode(2,OUTPUT);
      pinMode(4,OUTPUT); //  LED 2
      pinMode(3,INPUT);
      digitalWrite(2,HIGH);
      digitalWrite(4,LOW);
            delay(3);
       
   
      pinMode(2,INPUT);
      pinMode(4,OUTPUT);  //LED 4
      pinMode(3,OUTPUT);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
            delay(3);
     
  
      pinMode(2,INPUT);
      pinMode(4,OUTPUT); // LED 3
      pinMode(3,OUTPUT);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
            delay(3);
 

      pinMode(2,OUTPUT); // LED 6
      pinMode(4,INPUT); 
      pinMode(3,OUTPUT);
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
            delay(3);


      pinMode(2,OUTPUT);
      pinMode(4,INPUT); 
      pinMode(3,OUTPUT);
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
            delay(3);
}
 
 
  void push()
{
    unsigned long currentMillis = millis();
    int Z = digitalRead(pushPin);

    
     if (Z==1)/* if stick no pressed */
     {
        Serial.print("0");
        Serial.print(",");
        Serial.print(x, DEC);
        Serial.print(",");
        Serial.print(y, DEC);
        printKey();
        tiltSense();
          previousMillis = currentMillis;
    }
    if (Z==0 && (currentMillis - previousMillis) < interval)
    /* if stick is pressed and it has been less than 100 ms */
    {      
        Serial.print("1");
        Serial.print(",");
        Serial.print(x, DEC);
        Serial.print(",");
        Serial.print(y, DEC); 
        printKey();
        tiltSense();
      
    }
    if (Z==0 && (currentMillis - previousMillis) >= interval)
    {
        Serial.print(2);
        Serial.print(",");
        Serial.print(x, DEC);
        Serial.print(",");
        Serial.print(y, DEC);
        printKey();
        tiltSense();     
    } 
    delay(5);
    pinMode(2,OUTPUT);  //LED 1
      pinMode(4,OUTPUT); 
      pinMode(3,INPUT);
      digitalWrite(2,HIGH);
      digitalWrite(4,LOW);
      delay(3);
}


  void tiltSense()
  {
    if (tiltValue == 1)
    {
      Serial.print(",");
      Serial.println("0");
    }
    if (tiltValue == 0)
    {
      Serial.print(",");
      Serial.println("1");
    }
  }


  void keypress(int i, int j)
{  
  if(i==0 && j==0){
    key = 1; // a
  }
  if(i==0 && j==1){
    key = 2; //b
  }
  if(i==1 && j==0){
    key = 3; //3
  }
  if(i==1 && j==1){   
    key = 4; //6
  }
}


  void printKey()
  {
    Serial.print(",");
    Serial.print(key);
  }

