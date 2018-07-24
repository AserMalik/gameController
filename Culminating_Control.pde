import processing.serial.*;

Serial myPort;
String strIn = "";
String portName = "";
String[] coor ;

  Camera worldCamera;
   float state = 0;
     float previousState = 0;
     float commState = 0;
     float previousCommState = 0;
     float tiltState = 0;
     float keyState = 0;
   float x = 0;
     float y = 0;
     float posX = 0;
     float posY = 0;
   float backholdg = 0;
     float backholdr = 0;
     float backholdb = 0;

void setup(){
  size(800,600);

  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  myPort.buffer(10);
  
  worldCamera = new Camera();
  smooth();
  frameRate(60);
    
}


void draw()
{ 
  strIn = myPort.readStringUntil('\n');   // read it and store it in a string called strIn
      delay(1);
  if (strIn != null)
  {
    delay(1);
      coor = split(strIn, ","); 
      state = float(coor[0]);
      x = float(coor[1]);  
      y = float(coor[2]);
      keyState = float(coor[3]);
      tiltState = float(coor[4]);
  }
    println(state,x,y,keyState,tiltState); 

    translate(-worldCamera.pos.x, -worldCamera.pos.y); 
      worldCamera.draw(); 
  
      rect(25, 25, 25, 25); 
}


class Camera 
{ 
      PVector pos;
      Camera() { 
        pos = new PVector(0, 0); 
               } 


void draw()
{
  
    playerColor();
    
    if (tiltState==1 && state != 0)
    { 
      if (posY > 75){
                  pos.y += 1; 
            }
            if (posY < 75)
            {
                  pos.y -= 1;           
            }
      if (posX > 75){
                  pos.x += 1; 
            }
            if (posX < 75)
            {
                  pos.x -= 1;           
            }      
    } 
  
    if(state == 0)
    {
      previousState=0;
    }
   
    if(state != 0 || x != 0 || y != 0)
    {
       posX=posX+x;
       posY=posY-y;
          maker();             
    }
           
    if(state == 1  && previousState == 0)
    {  
      posX=posX+20*x;
      posY=posY-20*y;
      ellipse(400+posX,300+posY,100,100); 
      previousState=1;    
    }
    
    if(state == 2 && x == 0 && y == 0 && previousState == 1)
    {
      backholdg= random(250);
      backholdr= random(250);
      backholdb= random(250);
      fill(backholdr,backholdg,backholdb);        
      previousState = 2;
    }
   }
}


  void maker()
  {
      clear();         
            background(backholdg,backholdr,backholdb);
            if (posX > 300){
            posX=posX-x;
            returnComm(1);
            }
            if (posX < -300)
            {
            posX=posX-x;
            returnComm(2);            
            }
            /*
            if (posY > 200 || posY < -200){
            posY=posY+y;
            }*/
            ellipse(400+posX,300+posY,100,100);                  
  }
  
  
  void returnComm(int returnValue)
  {
      myPort.write(returnValue);
  }

  void playerColor()
  {
    if (keyState == 1)
    {
      fill(255,0,0);
      rect(25, 25, 25, 25); 
    }
        if (keyState == 2)
    {
      fill(0,255,0);
      rect(50,50,50,50); 
    }
        if (keyState == 3)
    {
      fill(0,0,255);
      rect(75,75,75,75); 
    }
        if (keyState == 4)
    {
      fill(125,125,0);
      rect(100,100,100,100); 
    }
  }