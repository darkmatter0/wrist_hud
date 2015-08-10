 
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Bounce.h>
#include <String.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif


#define TEST 0
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8
#define B1 17
#define B2 18
#define B3 19
#define B4 20
#define B5 21

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _rst);
Bounce bouncer1 = Bounce( B1,5 ); 
Bounce bouncer2 = Bounce( B2,5 ); 
Bounce bouncer3 = Bounce( B3,5 ); 
Bounce bouncer4 = Bounce( B4,5 ); 
Bounce bouncer5 = Bounce( B5,5 ); 

String inputString = "";
boolean animateGo = false;
boolean stringComplete = false;
byte selected = 1;
long mtime = 0; 
byte td = 0;

void setup(){
  Serial.begin(115200);
  Serial3.begin(115200);
  inputString.reserve(200);
  tft.begin();
  //initScreen();
  buildMenu();
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);
  pinMode(B5, INPUT_PULLUP);

}

void loop(){
  bouncer1.update();
  bouncer2.update();
  bouncer3.update();
  bouncer4.update();
  bouncer5.update();
  byte v1 = bouncer1.read();
  byte v2 = bouncer2.read();
  byte v3 = bouncer3.read();
  byte v4 = bouncer4.read();
  byte v5 = bouncer5.read();

  if(animateGo){
    
   // animateShiz(" @d4rkm4tter ", " DC801 | palshack.org | /r/defcoin ");
//    animateShiz(" @sebkinne ", " WiFi Pineapple | Hak5 | 8===D ");
   
  }
  if(bouncer1.fallingEdge()){
    if(animateGo){
      animateGo = false;
      buildMenu();
    }else{
     //tft.println("Pressed Button 1");
      selectUpItem();
    }

  }
  if(bouncer2.fallingEdge()){
    if(animateGo) animateGo = false;
    bootup();
//     tft.println("Pressed Button 2");
     if(TEST){
       parseCommands("menu2:BIG THINGS HERE");
     }
  }
  if(bouncer3.fallingEdge()){
  //   tft.println("Pressed Button 3");
    if(animateGo){
      animateGo = false;
      buildMenu();
    }
    else{
       selectNextItem();
    }
     if(TEST){
       parseCommands("time:12:35:22\n");
       parseCommands("menu1:This is so awesome!");
       parseCommands("title:this are epic"); 
     }
  }
  if(bouncer4.fallingEdge()){
    // tft.println("Pressed Button 4");
    animateGo=true;
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextWrap(false); // Don't wrap text to next line
  tft.setTextSize(2);
  tft.setCursor(0, tft.height()-30);
  tft.print("by @d4rkm4tter");
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); // White on black
  tft.setTextSize(5); // large letters
    
  }
  if(bouncer5.fallingEdge()){
     //tft.println("Pressed Button 5");
     selectItem();
     if(selected == 3){
       bashshell();
     }else if(selected == 1){
       sendSpike();
     }else if(selected ==2){
       zeroBug();
     }
     
     
  }
  if(v1 == LOW && v2 == LOW){
//     tft.println("Clear Screen");
     initScreen();
     
      buildMenu();
    //animateGo = true;
  }
  if(Serial3.available()){
    char inChar = (char)Serial3.read();
    //Serial.print(inChar);
    inputString+=inChar;
    if(inChar == '\n'){
      //Serial.print("Event complete: ");
      //Serial.println(inputString);
      stringComplete = true;
      parseCommands(inputString);
//      parse
    }
  }
  /*
  if(v1 == LOW){
      
    }
  }
  if(v2 == LOW){
    tft.println("Pressed Button 2");
  }
  if(v3 == LOW){
    tft.println("Pressed Button 3");
  }
  if(v4 == LOW){
    tft.println("Pressed Button 4");
  }
  if(v5 == LOW){
    tft.println("Pressed Button 5");
  }
  if(v1 == LOW && v2 == LOW){
    initScreen();
  }
  */
}
unsigned long initScreen(){
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(4);
  tft.println("Greetz haxor,\n moar code haz?");
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  return micros()-start;
}

unsigned long buildMenuTest(){
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(1);
  tft.println("Greetz haxor - Menu");
  tft.println("-------------------");
  tft.println("  Item 1");
  tft.println("  Item 2");
  tft.setCursor(0, 5);
  tft.println("  Item at 5");
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  return micros() - start;
}
void bashshell(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1);
  tft.println("root@palshack.org:/# cd hax");
  delay(300);
  tft.println("root@palshack.org:/hax# ./hack_all_the_things.py");
  delay(300);
  tft.println("Hacking all the things");
  tft.println("Usage: [target] [port] [attack]");
  delay(1000);
  tft.println("it worked, you are root");
  delay(300);
  tft.println("~# ");
  delay(2000);
  tft.println("TROLOLOLO");
  tft.println("LOLOOLOLOLO");
  tft.println("LOLOOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");  
  tft.println("LOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
  tft.println("LOL greetz hak5, dualcore, dc801  OLOLOLOLOLOL");  
  delay(4000);
  buildMenu();
}
void sendSpike(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("Better luck next time...");
  tft.setTextSize(3);
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);
  tft.println("SLUG-HEADS");
  delay(4000);
  buildMenu();
}
void zeroBug(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("/# cd hax");
  delay(300);
  tft.println("/# ./zero-bug");
  delay(300);
  tft.println("Zero-Bug is haxing\n all the overlay files\n\n");

  tft.print("Attack started...");
  for(byte i = 0; i<5; i++){
      tft.print(".");
      delay(450);
  }
  tft.println("\nIncoming Response: ");
  tft.setTextColor(ILI9341_RED);
  tft.println("<THEPLAUGE> I stopped you\n  with anti-virus!");
  delay(100);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("\nHAXS FAILED :(");
  delay(4000);
  buildMenu();
}
void bootup(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Darkmatter - CustomBIOS v7, An Epic CORP");
  tft.println("Copyright (C) Never, EBG, INC");    
  tft.println(" ");
  tft.println("Premium MIPS BIOS Revision 1010-0101");
  tft.println(" ");
  tft.println("Main Processor: Teensy(tm) 32");
  delay(500);
  tft.println("Memory Testing: 96152K OK (Installed)");
  delay(200);
  tft.println("Memory information: DDR Epic");
  delay(200);
  tft.println(" ");
  tft.println("Chipset Model: darkmatterCustom");
  delay(200);
  tft.println("Primary IDE Master   :    Your Mom");
  tft.println("Primary IDE Slave    :    Henrich");
  delay(200);
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println("Press F1 to Haxor All the things, DEL to crash");
  tft.println("08/06.15-1337-@d4rkm4tter-009");
  delay(3000);
  buildMenu();

}
unsigned long buildMenu(){
  tft.setRotation(1);
  
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setTextColor(ILI9341_RED); tft.setTextSize(2);
  int x = 0;
  int y = 0;
  tft.setCursor(x,y);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(3);
  tft.print("=hax the planet=");
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(x,y+20);
  tft.setTextSize(2);
  tft.print("-------------------------");
  tft.setCursor(x,y+40);
  tft.setTextColor(ILI9341_RED);
  tft.print("  SEND SPIKE");
  tft.setCursor(x,y+60);
  tft.print("  SEND ZER0-BUG");
  tft.setCursor(x,y+80);
  tft.print("  System Command Shell");
  tft.setCursor(x,y+100);
  tft.print("  DEAUTH");
  tft.setCursor(x,y+120);
  tft.print("  WLAN MON");
  writeText("by @d4rkm4tter", ILI9341_YELLOW, 0, tft.height()-60, 2);
  
  return micros() - start;
}
unsigned long selectItem(){
  int y = 20;
  tft.setCursor(0, y+(20*(selected)));
  tft.setTextColor(ILI9341_BLACK);
  tft.print(">");
  tft.setCursor(0, y+(20*(selected)));
  tft.setTextColor(ILI9341_BLUE);
  tft.print("0");
  delay(300);
  tft.setCursor(0, y+(20*(selected)));
  tft.setTextColor(ILI9341_BLACK);
  tft.print("0");
  tft.setCursor(0, y+(20*(selected)));
  tft.setTextColor(ILI9341_GREEN);
  tft.print(">");
    
}
unsigned long selectUpItem(){
  selected--;
  int y = 20;
  if(selected < 1){
    tft.setCursor(0, y+(20));
    selected = 5;
    tft.setTextColor(ILI9341_BLACK);
    tft.print(">");
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(0, y+(20*5));
    tft.print(">");
  }
  else{
    if(selected<5){
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(0, y+(20*(selected+1)));
      tft.print(">");
    }
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(0, y+(20*selected));
    tft.print(">");
  }
}
unsigned long selectNextItem(){
  selected++;
  int y = 20;
  if(selected > 5){
    tft.setCursor(0, y+(20*(selected-1)));
    selected = 1;
    tft.setTextColor(ILI9341_BLACK);
    tft.print(">");
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(0, y+20);
    tft.print(">");
  }
  else{
    if(selected>1){
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(0, y+(20*(selected-1)));
      tft.print(">");
    }
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(0, y+(20*selected));
    tft.print(">");
  }
}

void animateShiz(String text, String text1){
//  String text = " Twitter @d4rkm4tter "; // sample text
//String text1 = " /r/defcoin  |  palshack.org "; // sample text

const int width = 24; // width of the marquee display (in characters)

// Loop once through the string

for (int offset = 0; offset < text1.length(); offset++)

{

// Construct the string to display for this iteration

String t = "";
String t1 = "";

for (int i = 0; i < width; i++){

t += text.charAt((offset + i) % text.length());
t1 += text1.charAt((offset + i) % text1.length());
}
// Print the string for this iteration

tft.setCursor(0, tft.height()/4-10); // display will be halfway down screen
tft.setTextSize(3);
tft.print(t);

// Short delay so the text doesn't move too fast
if(td==0){
  delay(300);
  td = 1;
}else{
  td = 0;
}
tft.setCursor(0, tft.height()/2-10); // display will be halfway down screen
tft.setTextSize(2);
tft.print(t1);
delay(200);

}
}

//Example case: time;11:20:00
//menu1;Value in the menu

//Function to split commands from params
void parseCommands(String input){
//  Serial.println(input);
  static char inp[50];
  char *cmd, *par, *i;
  input.toCharArray(inp, input.length()+1);
  cmd = strtok_r(inp, ":", &i);
  Serial.print("command: ");
  Serial.print(cmd);
  Serial.print(" = ");
  par = strtok_r(NULL, "\n", &i);
  Serial.println(par);
  funcTree(cmd, par);
  inputString = "";
  stringComplete = false;
}

void funcTree(char *cmd, char *par){
  if(strcmp(cmd, "time")==0){
     writeText(par, ILI9341_YELLOW, (tft.width()/3), tft.height()-20, 2);
  }
  if(strcmp(cmd, "title")==0){
//    char *clr = "";
//    writeText(clr, ILI9341_BLACK, 0, 0, 3);

    writeText(par, ILI9341_BLUE, 0, 0, 3);
    writeText("-------------------------", ILI9341_GREEN, 0, 20, 2);
  }
  if(strcmp(cmd, "menu1")==0){
    writeText(par, ILI9341_RED, 25, 40, 2);
  }
  if(strcmp(cmd, "menu2")==0){
    writeText(par, ILI9341_RED, 25, 60, 2);  
  }
  if(strcmp(cmd, "menu3")==0){
    writeText(par, ILI9341_RED, 25, 80, 2);  
  }
  if(strcmp(cmd, "menu4")==0){
    writeText(par, ILI9341_RED, 25, 100, 2);  
  }
  if(strcmp(cmd, "status")==0){
    writeText(par, ILI9341_YELLOW, 0, tft.height()-60, 2);
  }
}

void writeText(char *t, uint16_t c, uint8_t x, uint8_t y, uint8_t s){
  tft.fillRect(x,y,tft.width(), 20, ILI9341_BLACK);
  tft.setCursor(x,y);
  tft.setTextColor(c);
  tft.setTextSize(s);
  tft.print(t);
}

