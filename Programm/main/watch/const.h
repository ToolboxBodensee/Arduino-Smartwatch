//Some defines to enable/disable some features (mainly for Debugging Reasons)
#define TOUCH                       //Enable/Disable Touchscreen
//#define BLUETOOTH                 //Enable/Disable Bluetooth
#define EE_USE                      //Enable/Disable EEPROM
#define DEBUG                       //Enable/Disable Debug via Hardware-Serial		

//Some defines which debugging values to show (you first have to enable DEBUG)
//It is only possible to print one value at a time (if you enable more the first one is taken)
//#define RAM_DEBUG					//Show the amount of free ram left (in bytes)
//#define TIMOUT_DEBUG				//Show the timout counter value (in millis)
//#define STOPPED_DEBUG				//Show if the Watch is stopped/running

//TFT
#define TFT_DC 9                    //TFT SPI Data/Command Pin
#define TFT_CS 10                   //TFT SPI Chip-Select Pin
#define ROTATION 1	 				//Rotation of the Screen

//Touchscreen
#ifdef TOUCH
#define STMPE_CS 8                  //Touchscreen SPI Chip-Select Pin
#define TOUCH_PIN 3
//Some Values to map the Touch-Coordinates to the Screen-Coordinates
#define TS_MINX 150                 //Touchscreen minimum x-Value
#define TS_MINY 130                 //Touchscreen minimum y-Value
#define TS_MAXX 3800                //Touchscreen maximum x-Value
#define TS_MAXY 4000                //Touchscreen maximum y-Value
//Values for detecting long presses (Time=LONGPRESS_TIME*TOUCH_DELAY)
#define LONGPRESS_TIME 100          //Touchscreen Longpress-Time (in millis)
#define SWIPE_DIST 50
#define TOUCH_DELAY 5              	//The delay to check again if their are errors with the touch
#endif

//Bluetooth
#ifdef BLUETOOTH
#define ADAFRUITBLE_REQ 6           //BLE SPI Chip-Select Pin
#define ADAFRUITBLE_RDY 2           //BLE-Ready Hardware Interrupt. This should be an interrupt pin, on Uno thats #2 or #3 but #3 is used by the Touchscreen
#define ADAFRUITBLE_RST 7           //BLE Reset Pin. For reseting the Module.
#endif

//Some 16-bit RGB-Color-Definitions (the Screen uses 18-bit colors but the Library only 16-bit)
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define LightBlue       0x0019      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F

//Color-Definitions for the UI to have a consistency in Design just change those Values to have a completly different Style!
#define BACKGROUND_COLOR Blue      //The Background-color of the Title-Bar
#define CLOCK_COLOR White           //The Text-color of the Clock      
#define TITLE_COLOR LightGrey       //The Text-color of the Title (for example "Watch") and the color of the page indicator dots
#define WALL_COLOR Navy         //The color of the background (Wallpaper)
//You can also load a real picture of the SD-Card but it is much slower and the SD needs an buffer of 512 Bytes plus about 160 Bytes of Buffer for the Picture (even more if you want to make it faster)
//Another Problem is that the Library uses about 6k of Program-Flash (you can't use a picture if you want to use all other features)

//Just some values for the Position of some UI-Elements
#define CLOCK_X 24+20                  //The x-Position of the Clock
#define CLOCK_Y 48+20                  //The y-Position of the Clock
#define RECT_DIST 20				//The distance of the Rectangle from the edges
#define ROUND 16					//The size of the round part

//Some Font-Sizes
#define CLOCK_SIZE 5                //The Font-Size of the Clock
#define STOP_SIZE 3                 //The Font-Size of the Stopwatch
#define NOTIFICATION_SIZE 2 		//The Font-Size of the Notification

#define MAX_PAGE 2                  //The maximum count of pages (means that there are (2*MAX_PAGE+1) Pages)

#define EE_BOOL 0x00                //The EEPROM-Address if a time is saved in the EEPROM (just 1 bit)
#define EE_HOUR 0x01                //The EEPROM-Address of the Hour
#define EE_MINUTE 0x02              //The EEPROM-Address of the Minute

#define SECOND_OVERFLOW 973         //The number of Timer-Interrupt-Overflows per Second

#define LOW_BRIGHTNESS 80			//Lowest Brightness

#define TIMEOUT 60 					//Seconds after the last interaction which the screen turns off

#define TEXT_COUNT 18 				//How many characters to save (limits the lenght of a notification)

//Some Hardware related Stuff (used in main)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);  //TFT-Class
#ifdef TOUCH
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS); //Touchscreen-Class
#endif

//Bluetooth
#ifdef BLUETOOTH
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);  //BLE-Class
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED; //Bluetooth-Connection Status
#endif