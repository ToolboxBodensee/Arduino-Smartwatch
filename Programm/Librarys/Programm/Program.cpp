/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif  
#include "Program.h"

#include <SD.h>
#include <Bitmap.h>
#define TFT_DC 9
#define TFT_CS 10
#define FILE_SIZE 256
#define ABSTAND_BOX 15
#define HOHE_BOX 60
Adafruit_ILI9341 _tft_prog = Adafruit_ILI9341(TFT_CS, TFT_DC);
bool finished=false;
bool pause_b=false;
String name;

Program::Program(String prog)
{
	Serial.begin(9600);
	_tft_prog.begin();
	name=prog;
}
void Program::show()
{
    	char charBuf[10];
    	String("/Programs/"+name+"/ui.acl").toCharArray(charBuf, 50) ;
    	File _prog_info = SD.open(charBuf);
	Serial.println("File loaded");
    	char _prog_txt/*[FILE_SIZE]*/;
    	int file_counter=0;	
    	//while (_prog_info.available()&&file_counter<FILE_SIZE) 
      		_prog_txt/* [file_counter++] */= _prog_info.read();
	Serial.println("File read");
    	int box_count=ABSTAND_BOX, char_count=0, hohe=0, lines=0;
    	int color_fg, color_bg;
    	bool pic=false, checked=false;
	int counter=0;
	Serial.println("Starting UI");
	//Object o;
	_tft_prog.fillScreen(color(_prog_txt));
	//Serial.println(_prog_txt[0]);
    	/*for(int zaehler=0; zaehler<FILE_SIZE; zaehler++)
    	{
		Serial.println("Loopidoop");
                switch(_prog_txt[zaehler])
                {
                   case 'P':
			if(_prog_txt[zaehler+1]==':')
			{
				Serial.println("Background");
				zaehler+=2;
		                 _tft_prog.fillScreen(color(_prog_txt[zaehler]));
			
			}
                        break;
                       
                    case 'B':
			if(_prog_txt[zaehler+1]==':')
			{
				zaehler++;
				counter++;
				Serial.println("Button");
		                color_fg= color(_prog_txt[zaehler+2]);
		                color_bg= color(_prog_txt[zaehler+3]);
	  
		                _tft_prog.fillRoundRect(ABSTAND_BOX, box_count, _tft_prog.width()-(2*ABSTAND_BOX),HOHE_BOX*(int)(_prog_txt[zaehler+1]-'0'),10,color_bg );
		                hohe=HOHE_BOX*(int)(_prog_txt[zaehler+1]-'0')+ABSTAND_BOX;
		                zaehler+=4;
		                for(; _prog_txt[zaehler]!=';'; ++zaehler)
		                {
		                  if(_prog_txt[zaehler]=='\\'&&_prog_txt[zaehler+1]=='n')
		                  {
		                      lines++;
		                      zaehler++;
		                      char_count=0;
		                  }
		                  else
		                  {  
		                    _tft_prog.drawChar(ABSTAND_BOX*2+6*char_count, box_count+ABSTAND_BOX+lines*15, _prog_txt[zaehler],color_fg , color_bg, 1);
		                    char_count++;
		                  }
		                }
		                lines=0;
		                char_count=0;
		                box_count+=hohe;
				//o.saveBoxCount(box_count, counter);
				//o.saveProgCount(zaehler, counter);
		        }        
			break;
		            
		    	case 'C':
			if(_prog_txt[zaehler+1]==':')
			{
				zaehler++;
				counter++;	
				Serial.println("Checkbox");
		                color_fg= color(_prog_txt[zaehler+2]);
		                color_bg= color(_prog_txt[zaehler+3]);
	  
		                _tft_prog.fillRoundRect(ABSTAND_BOX, box_count, _tft_prog.width()-(2*ABSTAND_BOX),HOHE_BOX*(int)(_prog_txt[zaehler+1]-'0'),10,color_bg );
				_tft_prog.fillRect(ABSTAND_BOX*1.5, box_count+ABSTAND_BOX, 10, 10, color_fg);
		                hohe=HOHE_BOX*(int)(_prog_txt[zaehler+1]-'0')+ABSTAND_BOX;
				checked=_prog_txt[zaehler+4]-'0';
				if(checked)
				{
					_tft_prog.drawLine(ABSTAND_BOX*1.5, box_count+ABSTAND_BOX, ABSTAND_BOX*1.5+10, box_count+ABSTAND_BOX+10, color_bg);
					_tft_prog.drawLine(ABSTAND_BOX*1.5, box_count+ABSTAND_BOX+10, ABSTAND_BOX*1.5+10, box_count+ABSTAND_BOX, color_bg);
				}
		                zaehler+=5;
		                for(; _prog_txt[zaehler]!=';'; ++zaehler)
		                {
		                  if(_prog_txt[zaehler]=='\\'&&_prog_txt[zaehler+1]=='n')
		                  {
		                      lines++;
		                      zaehler++;
		                      char_count=0;
		                  }
		                  else
		                  {  
		                    _tft_prog.drawChar(ABSTAND_BOX*2.5+6*char_count, box_count+ABSTAND_BOX+lines*15, _prog_txt[zaehler],color_fg , color_bg, 1);
		                    char_count++;
		                  }
		                }
		                lines=0;
		                char_count=0;
		                box_count+=hohe;
				//o.saveBoxCount(box_count, counter);
				//o.saveProgCount(zaehler, counter);
				
			}
			//break;
			/*case '{':
				Serial.println("Kalmer start");
				for(; _prog_txt[zaehler]!='}'; ++zaehler){Serial.println("Kalmer");}
			break;
                }
   }*/
   Serial.println("UI-Finished");
   _prog_info.close();
}

int Program::color(char value)
{
    switch(value)
    {
	Serial.println("Schleife");
          case  'A': return ILI9341_BLACK;
          case  'U': return ILI9341_BLUE;
          case  'R': return ILI9341_RED;
          case  'G': return ILI9341_GREEN;
          case  'C': return ILI9341_CYAN;
          case  'M': return ILI9341_MAGENTA;
          case  'Y': return ILI9341_YELLOW;
          case  'W': return ILI9341_WHITE;
          default: return  ILI9341_RED;
    }
  
}

void Program::pause()
{
	pause_b=true;
	//while(pause_b){}
}

void Program::play()
{
	pause_b=false;
	run();
}

void Program::run()
{
	/*while(!finished)
	{
		

	}*/
}

void Program::end()
{
	finished=true;
	_tft_prog.fillScreen(ILI9341_BLACK);
}

/*//################################
//#######	Object	##########
//################################
uint16_t boxCountList[32];
uint16_t boxProgList[32];

void Program::Object::saveBoxCount(int boxCount, int box)
{
	boxCountList[box]=	boxCount;
}

uint16_t Program::Object::getBoxCount(int box)
{
	return boxCountList[box];
}

void Program::Object::saveProgCount(int counter, int box)
{
	boxProgList[box]=counter;
}

uint16_t Program::Object::getProgCount(int box)
{
	return boxProgList[box];
}
*/

