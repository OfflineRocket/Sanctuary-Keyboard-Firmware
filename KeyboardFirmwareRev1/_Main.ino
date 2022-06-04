////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//    Firmware for the Sanctuary Keyboard                                                         //
//    Designed by: Foster Phillips, Lego_Rocket on many social media                              //
//    Primarily used to run the firmware behind the Sanctuary                                     //
//    Keyboard and kits to be sold at one point                                                   //
//      Firmware will be open source - hardware will be closed source                             //
//    This File is the last to compile - it is the main computing for the keyboard                //
//      This is to allow the seperation of variables, to change the matrix easier                 //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

//Setup, onces once on boot
void setup() {
  
  //Battery voltage reading pin
  pinMode(0,INPUT);

  //Initialize row output pin and set default state
  for(int i = 0; i < NumRows; i++)
  {
    pinMode(Rows[i],OUTPUT);  
    digitalWrite(Rows[i],LOW);
  }

  //Initialize column pins as input, with Pulldown (if available - certain pins need hardware pulldown)
  for(int i = 0; i < NumCols; i++)
  {
    pinMode(Cols[i],INPUT_PULLDOWN);
  }
  
  //Fast LED setup
  FastLED.addLeds<LedType,DataPin,ColorOrder>(leds, NumLeds);
  FastLED.setBrightness(40);

  //Adapted from GitHub, alongside the MAC address code
    //Allows the keyboard to connect to multiple devices, and "remembers" what device it was connected to
  EEPROM.begin(4);                                      //Begin EEPROM, allow us to store
  int deviceChose = EEPROM.read(0);                     //Read selected address from storage
  esp_base_mac_addr_set(&MACAddress[deviceChose][0]);   //Set MAC address based on that stored value

  //Begin bluetooth keyboard, without keyboard will not appear or connect
  Kbd.begin();
}



int RowCnt = 0;                                              //Keep track of scanned row - needs to be outside of the void loop so it isn't reset
int LayerCnt = 0;
//Loops to iterate through all functions
void loop() {
  //Check if the keyboard is connected, if so, scan the matrix
  if(Kbd.isConnected())
  {
    //Initialize new Row to scan
    digitalWrite(Rows[RowCnt],HIGH);

    
    //Check columns
    int ColCnt = 0;

    //Repeat until all columns are scanned
    while(ColCnt <= (NumCols - 1))
    {
      //Check state of current position, and make sure it was previously off
      if(digitalRead( Cols[ColCnt] ) == HIGH && PressedCheck[LayerCnt][RowCnt][ColCnt] == OFF)
      {
        //Switch based on the key pressed, allows for unique functions other than alphanumerics
        switch(Layer1[LayerCnt][RowCnt][ColCnt])
        {
          //Change the ID of the bluetooth, so you can connect to another device
          case 0:
          case 1:
          case 2:
            changeID(Layer1[LayerCnt][RowCnt][ColCnt]);
            break;
          //Rotary encoder button, play pause not an int
          case 3:
            Kbd.press(KEY_MEDIA_PLAY_PAUSE);
            break;
          //All other buttons are pressed through the Layer array
          case 5:
            ESP.restart();
            break;
          case FUNCTION_SW:
            //PressedCheck.fill(OFF);
            Kbd.releaseAll();
            LayerCnt++;
            break;
          case NULL_CON:
            break;
          case NEXT:
            Kbd.press(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case PREV:
            Kbd.press(KEY_MEDIA_PREVIOUS_TRACK);
            break;
          default:
            Kbd.press( Layer1[LayerCnt][RowCnt][ColCnt] );
        }
        //Assign the current key as ON, so it doesn't constantly press the button
        PressedCheck[LayerCnt][RowCnt][ColCnt] = ON;   
        //Serial.print( Layer1[a][ColCnt] );
      }

      //Otherwise, check if the switch was released
      else if(digitalRead( Cols[ColCnt] ) == LOW && PressedCheck[LayerCnt][RowCnt][ColCnt] == ON)
      {
        //Switch based on the switch released
        switch(Layer1[LayerCnt][RowCnt][ColCnt])
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
          case FUNCTION_SW:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            if(LayerCnt > 0)
            {
              LayerCnt--;
            }
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);            
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case NULL_CON:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            if(LayerCnt > 0)
            {
              LayerCnt--;
            }
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);            
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case NEXT:
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            break;
          case PREV:
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            break;
          //Release all other keys on the keyboard
          default:
            Kbd.release( Layer1[LayerCnt][RowCnt][ColCnt] );
        }
        //Let the keyboard know it's off, and to not constantly release keys that aren't released
        PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
      }
      //Increase column to scan
      ColCnt++;
    }
    //Reset back to original row to scan
    digitalWrite(Rows[RowCnt],LOW);
    //Increase row outputted
    RowCnt++;
    //Loop back to original row if out of the number of rows
    if(RowCnt >= (NumRows))
    {
      RowCnt = 0;
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
  }

  //Every 25 milliseconds refresh LEDs
  EVERY_N_MILLISECONDS(25) 
  {
    LedMode(2);
  }
  
  //Delay so it's not too fast
  delay(1);
}
