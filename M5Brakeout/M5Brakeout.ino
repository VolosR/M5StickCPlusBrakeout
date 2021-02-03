#include <M5StickCPlus.h>
#include "Wire.h"
#define JOY_ADDR 0x38

#include "bmp.h"
#define TFT_GREY 0x5AEB
#define lightblue 0x2D18
#define orange 0xFB60
#define purple 0xFB9B
float ys=1;

int8_t xj,yj,bj;

float x=random(30,100); //coordinates of ball
float y=70;
int ny=y;  //coordinates of previous position
int nx=x;

float px=45; //67 je sredina    pozicija igrača
int   pxn=px;
int vrije[2]={1,-1};
int enx[16]={8,33,58,83,108,8,33,58,83,108,22,47,72,97,47,72};
int eny[16]={37,37,37,37,37,45,45,45,45,45,53,53,53,53,61,61};
int enc[16]={TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_GREEN,TFT_GREEN,TFT_GREEN,TFT_GREEN,TFT_GREEN,orange,orange,orange,orange,lightblue,lightblue};
int score=0;
int level=1;
float amount[4]={0.25,0.50,0.75,1};
float xs=amount[random(4)]*vrije[random(2)];
int fase=0;
void setup(void) {
  
  M5.begin();
  Wire.begin(0, 26, 100000);
  M5.Lcd.setRotation(2);
  pinMode(37,INPUT_PULLUP);
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.pushImage(0, 0,  135, 240, bootlogo);
  
  }

float xstep=1;
int spe=0;
int pom=0;
int gameSpeed=7000;
void loop() {

  check();
  if(fase==0)
  {
    
    if(xj>10 || xj<-10)
     {
      if(pom==0){
      M5.Lcd.fillScreen(TFT_BLACK);
   M5.Lcd.drawLine(0,17,0,240,TFT_GREY);
   M5.Lcd.drawLine(0,17,135,17,TFT_GREY);
   M5.Lcd.drawLine(134,17,134,240,TFT_GREY);



   M5.Lcd.setCursor(3, 3, 2);
  
   M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);  M5.Lcd.setTextSize(1);

         M5.Lcd.setCursor(0, 0, 2);
         M5.Lcd.println("SCORE "+String(score));

    M5.Lcd.setCursor(99, 0, 2);
    M5.Lcd.println("LVL"+String(level));
    fase=fase+1;
    pom=1;
      }
      
      }else {pom=0;}
    }

if(fase==1){

        if(y!=ny){ 
        M5.Lcd.fillEllipse(nx, ny, 2, 2, TFT_BLACK);   //brisanje loptice
     ny=y;
     nx=x;
   }
  if(int(px)!=pxn){
  M5.Lcd.fillRect(pxn,234,24,4,TFT_BLACK);     //briasnje igraca
  pxn=px;
  }

  
 // spe=spe+1;

   if(px>=2 && px<=109){
   if(xj>10)
   px=px-1;
   if(xj<-10)
   px=px+1;
   }
   if(px<=3)
   px=4;

     if(px>=108)
   px=107;
   
   if(y>232 && x>px && x<px+24){ ///brisati kasnije
   ys=ys*-1;
   
   xs=amount[random(4)]*vrije[random(2)];

    
   }

   for(int j=0;j<16;j++)
    {
    if(x>enx[j] && x<enx[j]+20 && y>eny[j] && y<eny[j]+5)
      {
         M5.Lcd.fillRect(enx[j],eny[j],20,4,TFT_BLACK);
         enx[j]=400;
         ys=ys*-1;
         xs=amount[random(4)]*vrije[random(2)];
       
         score=score+1;

            M5.Lcd.setCursor(0, 0, 2);
           M5.Lcd.println("SCORE "+String(score));
           

    
    
        }
      }

    if(y<21)
   ys=ys*-1.00;

    if(y>240)
   fase=fase+1;

   

   if(x>=130)
   xs=xs*-1.00;

    if(x<=4)
   xs=xs*-1.00;
    
    
    for(int i=0;i<16;i++)     //draw enemies
    M5.Lcd.fillRect(enx[i],eny[i],20,4,enc[i]);
   
   
   M5.Lcd.fillEllipse(int(x), y, 2, 2, TFT_WHITE); // draw ball

   //if(spe>10){  //change coordinates of ball
   y=y+ys;
   x=x+xs;
   //spe=0;
   //}

   M5.Lcd.fillRect(px,234,24,4,TFT_WHITE);

   if(score==16 || score==33 || score==50 || score==67 || score==84 || score==101|| score==118 || score==135 || score==152 || score==169)
   newLevel();

 delayMicroseconds(gameSpeed);  
   

}
if(fase==2)
{
  
  M5.Lcd.fillScreen(TFT_BLACK);
 



  M5.Lcd.setCursor(13, 103, 2);
  
  M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);  M5.Lcd.setTextSize(1);

  M5.Lcd.println("GAME OVER");
  M5.Lcd.setCursor(13, 123, 4);
  M5.Lcd.println("SCORE:"+String(score));

   M5.Lcd.setCursor(13, 153, 4);
   M5.Lcd.println("LEVEL:"+String(level));

   M5.Lcd.setCursor(13, 123, 4);
   M5.Lcd.println("SCORE:"+String(score));
  delay(30);
  if(digitalRead(37)==0)
  {
  reset();

  }

   }}

void newLevel()
{
  score=score+1;
  delay(3000);
  gameSpeed=gameSpeed-500;
  level=level+1;
  M5.Lcd.setCursor(99, 0, 2);
    M5.Lcd.println("LVL"+String(level));
    y=75;
    ys=1;
    x=random(30,100);
 
  int enx2[16]={8,33,58,83,108,8,33,58,83,108,22,47,72,97,47,72};
   for(int n=0;n<16;n++)
   {
    enx[n]=enx2[n];
    }
  }

  void check()
{
  Wire.beginTransmission(JOY_ADDR);
  Wire.write(0x02); 
  Wire.endTransmission();
  Wire.requestFrom(JOY_ADDR, 3);
  if (Wire.available()) {
    xj = Wire.read();
    yj = Wire.read();
    bj= Wire.read();
               }  }

               void reset()

               {
                score=0;
                fase=0;
                gameSpeed=gameSpeed-500;
                level=1;
  M5.Lcd.setCursor(99, 0, 2);
    M5.Lcd.println("LVL"+String(level));
    y=75;
    ys=1;
    gameSpeed=7000;
    x=random(30,100);
 
  int enx2[16]={8,33,58,83,108,8,33,58,83,108,22,47,72,97,47,72};
   for(int n=0;n<16;n++)
   {
    enx[n]=enx2[n];
    }
                }
