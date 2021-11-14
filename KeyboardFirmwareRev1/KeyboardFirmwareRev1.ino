////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//    Firmware for the Sanctuary Keyboard                                                         //
//    Designed by: Foster Phillips, Lego_Rocket on many social media                              //
//    Primarily used to run the firmware behind the Sanctuary                                     //
//    Keyboard and kits to be sold at one point                                                   //
//      Firmware will be open source - hardware will be closed source                             //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

//Libraries used
#include <SimpleRotary.h>     //Used for the rotary encoder, just need to receive the simple direction
#include <BleKeyboard.h>      //Primary heavyweight for sending keystrokes
#include <EEPROM.h>           //Used for storage of MAC address selection
#include <FastLED.h>          //Used for LEDs on keyboards - only applicable to certain Sanctuary mdoels

//TODO Cleanup pin definitions and startup
  //Move to another file
  
//Define on and off values
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

//Rotary Pin Definitions
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
BleKeyboard Kbd("Sanctuary","Lego_Rocket",100);

//Setup media rotary encoder
SimpleRotary rotary(Rotary1,Rotary2,40);

//Keyboard Layout
  //TODO add seperate layers (probably easiest just to have a 3d array)
int Layer1[NumRows][NumCols] = {
  {KEY_ESC,       KEY_F1,       KEY_F2,       KEY_F3,       KEY_F4,       KEY_F5,       KEY_F6,       ' '   ,       3 /*KEY_MEDIA_PLAY_PAUSE*/ },
  {'`'    ,       '1'   ,       '2'   ,       '3'   ,       '4'   ,       '5'   ,       '6'   ,       '7'   ,       '8' },
  {KEY_TAB,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u'   ,       'i' },
  {KEY_CAPS_LOCK, 'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j'   ,       'k' },
  {KEY_LEFT_SHIFT,'z'   ,       'x'   ,       'c'   ,       'v'   ,       'b'   ,       'n'   ,       'm'   ,       ',' },
  {KEY_LEFT_CTRL, ' '   , KEY_LEFT_GUI, KEY_LEFT_ALT,       ' '   ,       ' '   ,       ' '   ,       ' '   ,       ' ' },

  {' '    ,        '9'   , KEY_HOME    ,     KEY_INSERT,   KEY_BACKSPACE,    '=' ,       '-'   ,       '0'   ,       '9' },
  {' '    ,       '6'   , KEY_END     , KEY_DELETE  ,       '\\'  ,       ']'   ,       '['   ,       'p'   ,       'o' },
  {' '    ,       2   ,       1   ,       0   ,       KEY_RETURN   , KEY_RETURN  ,       '\''  ,       ';'   ,       'l' },
  {' '    , KEY_RETURN , KEY_UP_ARROW,   5   , KEY_RIGHT_SHIFT ,   ' '   ,       ' '   ,       '/'   ,       '.'   },
  {' '    , KEY_RIGHT_ARROW  , KEY_DOWN_ARROW  , KEY_LEFT_ARROW  , KEY_RIGHT_CTRL  ,  ' '   , KEY_RIGHT_GUI  , KEY_RIGHT_ALT}

  
};

//Array to check if a key is currently pressed - Initiate everything to 0
  //TODO change from int - really inefficient
int PressedCheck[NumRows][NumCols] = { 0 };








//Adapted from : https://github.com/Cemu0/ESP32_USBHOST_TO_BLE_KEYBOARD/blob/main/src/USBHIDBootBLEKbd.cpp
//Primarily stores the selected MAC address in EEPROM storage
const int maxdevice = 3;
uint8_t MACAddress[maxdevice][6] = 
{
  {0x35, 0xAF, 0xA4, 0x07, 0x0B, 0x66},
  {0x31, 0xAE, 0xAA, 0x47, 0x0D, 0x61},
  {0x31, 0xAE, 0xAC, 0x42, 0x0A, 0x31}
  
};

//Basically just change the selected ID and reset - MAC address can only be changed before the keyboard start, so write to store selection, until changed again
  //Take in device number, and set the EEPROM to the selected - selects what address to shift to, instead of iterating to that address
void changeID(int DevNum)
{
    //Serial.println("changing MAC...");

    //Make sure the selection is valid
    if(DevNum < maxdevice)
    {
      //Write and commit to storage, reset ESP 32
      EEPROM.write(0,DevNum);
      EEPROM.commit();
      //esp_reset();
      esp_sleep_enable_timer_wakeup(1);
      esp_deep_sleep_start(); 
    }
}
//End of Borrowing

//Function prototyping
void LedMode (int Select);


//Rows to scan
  //TODO make more memory efficient
int Rows[NumRows] = {Row1, Row2 , Row3, Row4, Row5, Row6, Row7, Row8, Row9, Row10, Row11};
int Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9};
//Keep track of scanned row
int a = 0;
uint8_t gHue = 0;

byte RDir, PrevRDir;


// Setup code, setup pin definitions, LEDs, MAC address selections, and starting the keyboard
void setup() {
  //Defining Row pins as outputs
  //TODO simplify and use a loop instead
  pinMode(0,INPUT);
  
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

  //Fast LED setup
  FastLED.addLeds<LedType,DataPin,ColorOrder>(leds, NumLeds);
  FastLED.setBrightness(40);

  //Adapted from the Github above too
    //Allows the keyboard to connect to multiple devices, and "remembers" what device it was connected to
  EEPROM.begin(4);                                      //Begin EEPROM, allow us to store
  int deviceChose = EEPROM.read(0);                     //Read selected address from storage
  esp_base_mac_addr_set(&MACAddress[deviceChose][0]);   //Set MAC address based on that stored value

  //Begin bluetooth keyboard, without keyboard will not appear or connect
  Kbd.begin();
}



//Loops to iterate through all functions
void loop() {
  //Check if the keyboard is connected, if so, scan the matrix
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
          case 0:
          case 1:
          case 2:
            changeID(Layer1[a][ColCnt]);
            break;
          //Rotary encoder button, play pause not an int
          case 3:
            Kbd.press(KEY_MEDIA_PLAY_PAUSE);
            break;
          //All other buttons are pressed through the Layer array
          case 5:
            ESP.restart();
            break;
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
          case 2:
          case 0:
            break;
          //Release the rotary encoder button
          case 3:
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);
            break;
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
    //Reset back to original row to scan
    digitalWrite(Rows[a],LOW);
    //Increase row outputted
    a++;
    //Loop back to original row if out of the number of rows
    if(a >= (NumRows))
    {
      a = 0;
    }
    //Kbd.releaseAll();
  
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
  }

  //Every 25 milliseconds refresh LEDs
  EVERY_N_MILLISECONDS(25) 
  {
    LedMode(2);
  }
  //Delay so it's not too fast
  delay(1);
}


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
      break;
  }
  FastLED.show();
}
