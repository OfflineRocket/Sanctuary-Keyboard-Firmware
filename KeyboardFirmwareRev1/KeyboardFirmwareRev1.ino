
//Libraries used
#include <SimpleRotary.h>
#include <BleKeyboard.h>
#include <EEPROM.h>
//#include <KeyboardOutputCallbacks.h>

#include <FastLED.h>


#define OFF 0
#define ON 1


//Pin Definitions
#define Row1 2
#define Row2 4
#define Row3 13
#define Row4 12
#define Row5 14
#define Row6 27
#define Row7 26
#define Row8 25
#define Row9 33
#define Row10 32
#define Row11 23

#define Col1 5
#define Col2 36
#define Col3 39
#define Col4 34
#define Col5 35
#define Col6 19
#define Col7 18
#define Col8 17
#define Col9 16

#define Rotary1 15
#define Rotary2 22

//Matrix setup

#define NumRows 11
#define NumCols 9

//LED definitions

#define DataPin 21
#define LedType WS2812
#define ColorOrder GRB
#define NumLeds 93

//Setup memory for LEDs
CRGB leds[NumLeds];

//Setup keyboard
BleKeyboard Kbd("Santuary","Lego_Rocket",100);

SimpleRotary rotary(Rotary1,Rotary2,40);

//Keyboard Layout
int Layer1[NumRows][NumCols] = {
  {KEY_ESC,       KEY_F1,       KEY_F2,       KEY_F3,       KEY_F4,       KEY_F5,       KEY_F6,       ' '   ,       2 /*KEY_MEDIA_PLAY_PAUSE*/ },
  {'`'    ,       '1'   ,       '2'   ,       '3'   ,       '4'   ,       '5'   ,       '6'   ,       '7'   ,       '8' },
  {KEY_TAB,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u'   ,       'i' },
  {KEY_CAPS_LOCK, 'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j'   ,       'k' },
  {KEY_LEFT_SHIFT,'z'   ,       'x'   ,       'c'   ,       'v'   ,       'b'   ,       'n'   ,       'm'   ,       ',' },
  {KEY_LEFT_CTRL, ' '   , KEY_LEFT_GUI, KEY_LEFT_ALT,       ' '   ,       ' '   ,       1   ,       ' '   ,       ' ' },

  {' '    ,        '9'   , KEY_HOME    ,     KEY_INSERT,   KEY_BACKSPACE,    '=' ,       '-'   ,       '0'   ,       '9' },
  {' '    ,       '6'   , KEY_END     , KEY_DELETE  ,       '\\'  ,       ']'   ,       '['   ,       'p'   ,       'o' },
  {' '    ,       '3'   ,       '2'   ,       '1'   ,       KEY_RETURN   , KEY_RETURN  ,       '\''  ,       ';'   ,       'l' },
  {' '    , KEY_RETURN , KEY_UP_ARROW,   '0'   , KEY_RIGHT_SHIFT ,   ' '   ,       ' '   ,       '/'   ,       '.'   },
  {' '    , KEY_RIGHT_ARROW  , KEY_DOWN_ARROW  , KEY_LEFT_ARROW  , KEY_RIGHT_CTRL  ,  ' '   , KEY_RIGHT_GUI  , KEY_RIGHT_ALT}

  
};

int PressedCheck[NumRows][NumCols] = { 0 };










//Borrowed from : https://github.com/Cemu0/ESP32_USBHOST_TO_BLE_KEYBOARD/blob/main/src/USBHIDBootBLEKbd.cpp
const int maxdevice = 3;
uint8_t MACAddress[maxdevice][6] = 
{
  {0x35, 0xAF, 0xA4, 0x07, 0x0B, 0x66},
  {0x31, 0xAE, 0xAA, 0x47, 0x0D, 0x61},
  {0x31, 0xAE, 0xAC, 0x42, 0x0A, 0x31},
  // ...
};

void changeID()
{
    //Serial.println("changing MAC...");
    int deviceChose = EEPROM.read(0);
    deviceChose++;
    if(deviceChose >= maxdevice)
        EEPROM.write(0,0);
    else
        EEPROM.write(0,deviceChose);
    EEPROM.commit();
        //lmao
    esp_sleep_enable_timer_wakeup(1);
    esp_deep_sleep_start(); 
}

//End of Borrowing








/*
char Layer1[2][7] = {
  {0xB1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7},
  {0xB3, 0x71,  0x77,  0x65,  0x72,  0x74,  0x79}
};*/
/*int Layer1[2][7] = {
  {177, 194, 195, 196, 197, 198, 199},
  {179, 113,  0x77,  0x65,  0x72,  0x74,  0x79}
};*/

//Rows to scan
int Rows[NumRows] = {Row1, Row2 , Row3, Row4, Row5, Row6, Row7, Row8, Row9, Row10, Row11};
int Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9};
//Keep track of scanned row
int a = 0;
uint8_t gHue = 0;

byte RDir, PrevRDir;

void setup() {
  //Defining Row pins as outputs
  //TODO simplify and use a loop instead
  pinMode(Row1,OUTPUT);
  pinMode(Row2,OUTPUT);
  pinMode(Row3,OUTPUT);
  pinMode(Row4,OUTPUT);
  pinMode(Row5,OUTPUT);
  pinMode(Row6,OUTPUT);
  pinMode(Row7,OUTPUT);
  pinMode(Row8,OUTPUT);
  pinMode(Row9,OUTPUT);
  pinMode(Row10,OUTPUT);
  pinMode(Row11,OUTPUT);
  

  
  //Set default state
  //TODO simplify and use a loop
  digitalWrite(Row1,LOW);
  digitalWrite(Row2,LOW);
  digitalWrite(Row3,LOW);
  digitalWrite(Row4,LOW);
  digitalWrite(Row5,LOW);
  digitalWrite(Row6,LOW);
  digitalWrite(Row7,LOW);
  digitalWrite(Row8,LOW);
  digitalWrite(Row9,LOW);
  digitalWrite(Row10,LOW);
  digitalWrite(Row11,LOW);

  //Pin mode for the 
  //TODO simplify and use a loop
  pinMode(Col1,INPUT_PULLDOWN);
  pinMode(Col2,INPUT_PULLDOWN);
  pinMode(Col3,INPUT_PULLDOWN);
  pinMode(Col4,INPUT_PULLDOWN);
  pinMode(Col5,INPUT_PULLDOWN);
  pinMode(Col6,INPUT_PULLDOWN);
  pinMode(Col7,INPUT_PULLDOWN);
  pinMode(Col8,INPUT_PULLDOWN);
  pinMode(Col9,INPUT_PULLDOWN);

  //Rotary Encoder pin definitions
  //pinMode(Rotary1,INPUT);
  //pinMode(Rotary2,INPUT);

  //Fast LED setup
  FastLED.addLeds<LedType,DataPin,ColorOrder>(leds, NumLeds);
  FastLED.setBrightness(50);
  //Serial.begin(115200);

  //Begin bluetooth keyboard, without keyboard will not appear or connect
  Kbd.begin();
}

void loop() {
  //Code repeated
  //Check if the keyboard is connected, if so, scan the 
  if(Kbd.isConnected())
  {
    //Initialize new Row to scan
    digitalWrite(Rows[a],HIGH);

    
    //Check columns
    int ColCnt = 0;

    //Repeat until all columns are scanned
    while(ColCnt <= (NumCols - 1))
    {
      //Check state of current position, and make sure it was previously off
      if(digitalRead( Cols[ColCnt] ) == HIGH && PressedCheck[a][ColCnt] == OFF)
      {
        //Switch based on the key pressed, allows for unique functions other than alphanumerics
        switch(Layer1[a][ColCnt])
        {
          //Tactile switch, change the ID of the bluetooth, so you can connect to another device
          case 1:
            changeID();
            break;
          //Rotary encoder button, play pause not an int
          case 2:
            Kbd.press(KEY_MEDIA_PLAY_PAUSE);
          //All other buttons are pressed through the Layer array
          default:
            Kbd.press( Layer1[a][ColCnt] );
        }
        //Assign the current key as ON, so it doesn't constantly press the button
        PressedCheck[a][ColCnt] = ON;   
        //Serial.print( Layer1[a][ColCnt] );
      }

      //Otherwise, check if the switch was released
      else if(digitalRead( Cols[ColCnt] ) == LOW && PressedCheck[a][ColCnt] == ON)
      {
        //Switch based on the switch released
        switch(Layer1[a][ColCnt])
        {
          //Nothing for the tactile switch
          case 1:
            break;
          //Release the rotary encoder button
          case 2:
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);
          //Release all other keys on the keyboard
          default:
            Kbd.release( Layer1[a][ColCnt] );
        }
        //Let the keyboard know it's off, and to not constantly release keys that aren't released
        PressedCheck[a][ColCnt] = OFF;
      }
      //Increase column to scan
      ColCnt++;
    }
    //Kbd.releaseAll();
  }

  //Reset back to original row to scan
  digitalWrite(Rows[a],LOW);
  //Increase row outputted
  a++;
  //Loop back to original row if out of the number of rows
  if(a >= (NumRows))
  {
    a = 0;
  }

  //Check Rotary Encoder once a cycle
  
  RDir = rotary.rotate();
  switch(RDir)
  {
    case 1:
      if(PrevRDir != RDir)
      {
        Kbd.release(KEY_MEDIA_VOLUME_UP);
      }
      Kbd.press(KEY_MEDIA_VOLUME_DOWN);
      PrevRDir = 1;
      break;
    case 2:
      if(PrevRDir != RDir)
      {
        Kbd.release(KEY_MEDIA_VOLUME_DOWN);
      }
      Kbd.press(KEY_MEDIA_VOLUME_UP);
      PrevRDir = 2;
      break;
    default:
      switch(PrevRDir)
      {
        case 1:
          Kbd.release(KEY_MEDIA_VOLUME_DOWN);
          break;
        case 2:
          Kbd.release(KEY_MEDIA_VOLUME_UP);
          break;
      }
      PrevRDir = 0;
      break;
  }


  //Every 25 milliseconds refresh LEDs
  EVERY_N_MILLISECONDS(25) 
  {
    gHue++;
    fill_rainbow( leds, NumLeds, gHue, 7);
    FastLED.show();
  }

  //Delay so it's not too fast
  delay(1);
}


/*
void LedMode (int Select)
{
  switch(Select)
  {
    case 1:
      gHue++;
      fill_rainbow(leds, NumLeds, gHue, 7);
      break;
    case 2:
      fill_solid(leds, NumLeds, CRGB::Cyan);      
      break;
    default:
    
  }
}*/
