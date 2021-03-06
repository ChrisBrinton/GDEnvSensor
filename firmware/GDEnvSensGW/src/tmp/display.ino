#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/TomThumb.h>
#include <Fonts/PicoPixel.h>
#include "Adafruit_SSD1306.h"
#include "config/global.h"
//
// Display module
//

//Set up I2C for display
#define OLED_RESET 0

Adafruit_SSD1306 display(OLED_RESET);

void displayStartupLogo(){
  display.display();
  delay(2000);
  display.clearDisplay();
}

void displayWifiInfo(char* descr, char* SSID, char* IP){
  display.clearDisplay();
  //clear the double buffer
  memset(display.getBuffer(),0,1024);
  display.setFont(&FreeSans9pt7b);
  display.ssd1306_command(SSD1306_SETSTARTLINE);
  display.setCursor(0,15);
  String tmpStr = String(descr) + String(SSID);
  display.print(tmpStr.c_str());
  display.setCursor(0,31);
  tmpStr = String(IP);
  display.print(tmpStr.c_str());
  display.display();
  delay(8000);
  memset(display.getBuffer(),0,1024);

}

void scrollUp(int numoflines){
  static int line;
  for(int x=0;x<numoflines;x++){
    line++;
    if(line >= 4){
      for (int i=0;i<8;i++){
        delay(50);
        display.ssd1306_command(SSD1306_SETSTARTLINE+i);
      }
      //delay(3000);
      //after the row has scrolled up, copy the 2nd to 4th row into the 1st to 3rd row
      memcpy(display.getBuffer(),display.getBuffer()+128,384);
      //then blank out the 4th row
      memset(display.getBuffer()+384,0,128);
      //then set the start line back to the beginning of the buffer and move the cursor to the start of the new 4th line.
      display.ssd1306_command(SSD1306_SETSTARTLINE);
      display.setCursor(0,24);
      //now it should be safe to display the buffer
      display.display();
    }
  }
}

void scrollUpDB(int numoflines){
  static int line=0;
  static int bufferline=0;
  static int row=0;
  //reset counters. yay for procedural code! j/k
  if(numoflines==-1){
    line=0;
    bufferline=0;
    row=0;
    display.ssd1306_command(SSD1306_SETSTARTLINE);
    return;
  }
  for(int x=0;x<numoflines;x++){
    line++;
    bufferline++;
    if(line > 4){
      for (int i=0;i<8;i++){
        delay(50);
        display.ssd1306_command(SSD1306_SETSTARTLINE | row % 64);
        row++;
      }
      if(bufferline >= 8) {
        bufferline = 0;
        display.setCursor(0,0);
      }
      if(row >= 64){
        row = 0;
      }
    }
    //blank out the row that we just scrolled off
    if(bufferline < 5){
      memset(display.getBuffer()+((bufferline+3)*128),0,128);
    }
    else {
      memset(display.getBuffer()+((bufferline-5)*128),0,128);
    }
  }
}

void BuildCurrentTimePage(int iYOffset) {
  String timeString = "";
  String ampmString = "";
  int hours, centerx;
  hours = hour(now());
  if(hours>12){
    hours = hour(now()) - 12;
  }
  timeString = timeString + String(hours) + ":";
  if(minute(now())<10){
    timeString = timeString + "0";
  }
  timeString = timeString + String(minute(now()));
  if(hour(now())>11){
    ampmString = "PM";
  }
  else{
    ampmString = "AM";
  }
  // do these shenanigans to determine the width of the time we want to print
  // so that we can center it on the screen
  int16_t x1,y1;
  uint16_t w,h;
  int total_w = 0;
  display.setFont(&FreeSans18pt7b);
  display.getTextBounds((char*)timeString.c_str(),0,31,&x1,&y1,&w,&h);
  total_w = w;
  display.setFont(&FreeSans9pt7b);
  display.getTextBounds((char*)ampmString.c_str(),0,31,&x1,&y1,&w,&h);
  total_w = total_w + w;

  centerx = ((SSD1306_LCDWIDTH - total_w-11)/2)-iYOffset;
  display.setCursor(centerx,31);
  display.setFont(&FreeSans18pt7b);
  display.print(timeString.c_str());
  display.setFont(&FreeSans9pt7b);
  display.println(ampmString.c_str());
}


void buildNodeDisplayPage(int iYOffset){
  int16_t x1,y1,iTmpX,iTmpY;
  uint16_t w,h;
  uint8_t iNodeID;
  String tempString = "";
  int iF, iH, iP , iRSSI, iPageOffset;

  iNodeID = nodeList.currentNode();
  //if the day has rolled since the last update time then the age can return a neg number
  //its probablyealthy to clear out the list daily, so clear it for any neg return val.
  //Dont bother to check node SENSORID as thats the onboard sensor
  if(iNodeID != SENSORID) {
    int age = nodeList.getNodeUpdateAge(iNodeID);
    //DEBUG_MSG("Node %i is %i min old\n", iNodeID, age);
    if (age > 60 || age < 0){
      DEBUG_MSG("Node ID: %i is %i min old. Deleting\n" iNodeID, age);
      nodeList.deleteNode(iNodeID);
    }
  }

  iF = int(atof(nodeInfo[nodeList.currentNode()].THP->F.c_str())+.49);
  iH = int(atof(nodeInfo[nodeList.currentNode()].THP->H.c_str())+.49);
  iP = int(atof(nodeInfo[nodeList.currentNode()].THP->P.c_str())+.49);
  iRSSI = int(atof(nodeInfo[nodeList.currentNode()].THP->RSSI.c_str())+.49);

  iPageOffset = -1;

//ID
  iTmpX = 93;
  iTmpY = 6;
  tempString = "ID: " + String(iNodeID);
  display.setFont(&TomThumb);
  display.setCursor(iTmpX,iTmpY+iPageOffset);
  display.print(tempString.c_str());

//Humidity
  iTmpX=133;
  iTmpY=22;
  tempString = "H:" + String(iH);
  display.getTextBounds((char*)tempString.c_str(),0,iTmpY+iPageOffset,&x1,&y1,&w,&h);
  display.setCursor(iTmpX-w,iTmpY+iPageOffset);
  display.print(tempString.c_str());
//Temp
  iTmpX = 125;
  iTmpY = 14;
  display.setFont(&TomThumb);
  tempString = String(iF);
  display.getTextBounds((char*)tempString.c_str(),0,iTmpY+iPageOffset,&x1,&y1,&w,&h);
  display.setCursor(iTmpX-w+4,iTmpY+iPageOffset);
  display.print(tempString.c_str());
  iTmpX = iTmpX;
  display.setCursor(iTmpX,iTmpY-2+iPageOffset);
  tempString = "o";
  display.print(tempString.c_str());
//RSSI (based on where temp ends)
  display.getTextBounds((char*)tempString.c_str(),iTmpX,16+iPageOffset,&x1,&y1,&w,&h);
  iTmpX = iTmpX + w + 0;
  iTmpX = 122;
  iTmpY = 1;
  if(iRSSI>-60){
    display.drawRect(iTmpX+iYOffset,iTmpY+iPageOffset,2,5,WHITE);
  }
  if(iRSSI>-70){
    display.drawRect(iTmpX-3+iYOffset,iTmpY+iPageOffset+1,2,4,WHITE);
  }
  if(iRSSI>-80){
    display.drawRect(iTmpX-6+iYOffset,iTmpY+iPageOffset+2,2,3,WHITE);
  }
  if(iRSSI>-90){
    display.drawRect(iTmpX-9+iYOffset,iTmpY+iPageOffset+3,2,2,WHITE);
  }

  //Battery indicator
  //draw battery shape around indicator
  iTmpX = 111;
  iTmpY = 26;
  display.drawRect(iTmpX+iYOffset,iTmpY+iPageOffset,12,7,WHITE);
  display.drawRect(iTmpX+12+iYOffset,iTmpY+2+iPageOffset,1,3,WHITE);

  float dBAT = atof(nodeInfo[nodeList.currentNode()].THP->BAT.c_str());
  if(dBAT>3.5){
    display.drawRect(iTmpX+8+iYOffset,iTmpY+2+iPageOffset,2,3,WHITE);
  }
  if(dBAT>3.3){
    display.drawRect(iTmpX+5+iYOffset,iTmpY+2+iPageOffset,2,3,WHITE);
  }
  if(dBAT>3.0){
    display.drawRect(iTmpX+2+iYOffset,iTmpY+2+iPageOffset,2,3,WHITE);
  }
  nodeList.nextNode();
}

//This should get called about every second. Cycle through the 4 actions
void displayInfo(){
  #if defined SSD1305_128_32DB //The SSD1305 displays are offset by 4 pixels
    int iYOffset = 4;
  #else
    int iYOffset = 0;
  #endif

  memset(display.getBuffer(),0,512);
  BuildCurrentTimePage(iYOffset);

  buildNodeDisplayPage(iYOffset);

  display.display();
}


void displaySetup () {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextWrap(FALSE);

  displayStartupLogo();

}

void displayLoop(){
  static int lastMillis = 0;
  int nowMillis = millis();
  if(nowMillis > (lastMillis + 2000)){
    displayInfo();
    lastMillis = nowMillis;
  }
}
