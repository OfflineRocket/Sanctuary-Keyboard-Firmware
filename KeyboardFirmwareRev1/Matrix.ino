//Rows to scan, and Columns to read (definitions in SanctuaryHardware
short Rows[NumRows] = {Row1, Row2 , Row3, Row4, Row5, Row6, Row7, Row8, Row9, Row10, Row11};
short Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9};


//  Layer 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Layer1[NumLayers][NumRows][NumCols] = 
{
  {
    {KEY_ESC,       KEY_F1,       KEY_F2,       KEY_F3,       KEY_F4,       KEY_F5,       KEY_F6,       ' '   ,       3   },
    {'`'    ,       '1'   ,       '2'   ,       '3'   ,       '4'   ,       '5'   ,       '6'   ,       '7'   ,       '8' },
    {KEY_TAB,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u'   ,       'i' },
    {KEY_CAPS_LOCK, 'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j'   ,       'k' },
    {KEY_LEFT_SHIFT,'z'   ,       'x'   ,       'c'   ,       'v'   ,       'b'   ,       'n'   ,       'm'   ,       ',' },
    {KEY_LEFT_CTRL, ' '   , KEY_LEFT_GUI, KEY_LEFT_ALT,       ' '   ,       ' '   ,       ' '   ,       ' '   ,       KEY_RIGHT_ALT },
  
    {' '    ,        '9'   , KEY_HOME    ,     KEY_INSERT,   KEY_BACKSPACE,    '=' ,       '-'   ,       '0'   ,       '9' },
    {' '    ,       '6'   , KEY_END     , KEY_DELETE  ,       '\\'  ,       ']'   ,       '['   ,       'p'   ,       'o' },
    {' '    ,       2   ,       1   ,       0   ,       KEY_RETURN   , KEY_RETURN  ,       '\''  ,       ';'   ,       'l' },
    {' '    , KEY_RETURN , KEY_UP_ARROW,   5   , KEY_RIGHT_SHIFT ,   ' '   ,       ' '   ,       '/'   ,       '.'   },
    {' '    , KEY_RIGHT_ARROW  , KEY_DOWN_ARROW  , KEY_LEFT_ARROW  , KEY_RIGHT_CTRL  ,  KEY_RIGHT_GUI  , ' '  , FUNCTION_SW}
  },
  //  Layer 2 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    {KEY_ESC,       KEY_F7,       KEY_F8,       KEY_F9,       KEY_F10,       KEY_F11,       KEY_F12,       ' '   ,       3   },
    {'`'    ,       '1'   ,       '2'   ,       '3'   ,       '4'   ,       '5'   ,       '6'   ,       '7'   ,       '8' },
    {KEY_TAB,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u'   ,       'i' },
    {KEY_CAPS_LOCK, 'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j'   ,       'k' },
    {KEY_LEFT_SHIFT,'z'   ,       'x'   ,       'c'   ,       'v'   ,       'b'   ,       'n'   ,       'm'   ,       ',' },
    {KEY_LEFT_CTRL, ' '   , KEY_LEFT_GUI, KEY_LEFT_ALT,       ' '   ,       ' '   ,       ' '   ,       ' '   ,       ' ' },
  
    {' '    ,        '9'   , KEY_HOME    ,     KEY_INSERT,   KEY_BACKSPACE,    '=' ,       '-'   ,       '0'   ,       '9' },
    {' '    ,       '6'   , KEY_END     , KEY_DELETE  ,       '\\'  ,       ']'   ,       '['   ,       'p'   ,       'o' },
    {' '    ,       2   ,       1   ,       0   ,       KEY_RETURN   , KEY_RETURN  ,       '\''  ,       ';'   ,       'l' },
    {' '    , KEY_RETURN , KEY_UP_ARROW,   5   , KEY_RIGHT_SHIFT ,   ' '   ,       ' '   ,       '/'   ,       '.'   },
    {' '    , NEXT  , KEY_DOWN_ARROW  , PREV  , KEY_RIGHT_CTRL  ,  KEY_RIGHT_GUI   , ' '  , NULL_CON}
  },
  //  Layer 3 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    {KEY_ESC,       KEY_F1,       KEY_F2,       KEY_F3,       KEY_F4,       KEY_F5,       KEY_F6,       ' '   ,       3   },
    {'`'    ,       '1'   ,       '2'   ,       '3'   ,       '4'   ,       '5'   ,       '6'   ,       '7'   ,       '8' },
    {KEY_TAB,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u'   ,       'i' },
    {KEY_CAPS_LOCK, 'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j'   ,       'k' },
    {KEY_LEFT_SHIFT,'z'   ,       'x'   ,       'c'   ,       'v'   ,       'b'   ,       'n'   ,       'm'   ,       ',' },
    {KEY_LEFT_CTRL, ' '   , KEY_LEFT_GUI, KEY_LEFT_ALT,       ' '   ,       ' '   ,       ' '   ,       ' '   ,       ' ' },
  
    {' '    ,        '9'   , KEY_HOME    ,     KEY_INSERT,   KEY_BACKSPACE,    '=' ,       '-'   ,       '0'   ,       '9' },
    {' '    ,       '6'   , KEY_END     , KEY_DELETE  ,       '\\'  ,       ']'   ,       '['   ,       'p'   ,       'o' },
    {' '    ,       2   ,       1   ,       0   ,       KEY_RETURN   , KEY_RETURN  ,       '\''  ,       ';'   ,       'l' },
    {' '    , KEY_RETURN , KEY_UP_ARROW,   5   , KEY_RIGHT_SHIFT ,   ' '   ,       ' '   ,       '/'   ,       '.'   },
    {' '    , KEY_RIGHT_ARROW  , KEY_DOWN_ARROW  , KEY_LEFT_ARROW  , KEY_RIGHT_CTRL  ,  KEY_RIGHT_GUI   , ' '  , ' '}
  }
};

//Array to check if a key is currently pressed - Initiate everything to 0
short PressedCheck[NumLayers][NumRows][NumCols] = { OFF };
