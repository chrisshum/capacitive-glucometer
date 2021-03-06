#include <TFT_eSPI.h>  // graphics library 
#include <SPI.h>   //serial peripheral interface 
#include <Wire.h> // allow for communication with I2C devices this is for the display
#include <Button2.h> // allow for callback function to track single double triple and long clicks
#include "esp_adc_cal.h"  // library to calibrate the analog to digital converter 
#include "bmp.h" // for images, used for startup screen, will soon replace 
#include "BluetoothSerial.h" // bluetooth library, pretty self explanatory 


#ifndef TFT_DISPOFF     // turn off display  with tft.writecommand defining 
#define TFT_DISPOFF 0x28 //0x28 is defined by the tft library as turn off display
#endif

#ifndef TFT_SLPIN       // sleep display 
#define TFT_SLPIN   0x10 //0x10 is defined as sleep in the tft_espi library to sleep 
#endif

// pins for display
#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

// Display backlight control pin
#define TFT_BL          4   
// ADC detection enable port
#define ADC_EN          14  
// pin for battery level 
#define ADC_PIN         34  
// right button 
#define BUTTON_1        35 
// left button 
#define BUTTON_2        0  

// Invoke custom library
TFT_eSPI tft = TFT_eSPI(135, 240);
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

// stores wifi SSIDs and rrsi strength values
char buff[512];

int vref = 1100;
int btnCick = false;


//! Long time delay, it is recommended to use shallow sleep, which can effectively reduce the current consumption
void espDelay(int ms)
{
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}

// multithreading starting two tasks of two cores, task1 is for waveform gen
TaskHandle_t Task1; 

// an object to initialize bluetooth stacks and establish serial communication over bluetooth
BluetoothSerial SerialBT; 

void setup()
{
    // Initialize Bluetooth
    Serial.begin(115200);
    SerialBT.begin("Glucometer"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
    
    // analog resolution giving 4096 steps
    analogReadResolution(12);

    // Setup core 0 for generating sine wave 
    xTaskCreatePinnedToCore(
        Task1code,
        "Task1",
        10000,
        NULL,
        5,
        &Task1,
        0
    );
    // disables core0 task watchdog hangup since we want to run the loop indefinetely      
    disableCore0WDT();

    /*
        ADC_EN is the ADC detection enable port
        If the USB port is used for power supply, it is turned on by default.
        If it is powered by battery, it needs to be set to high level
    */
    pinMode(ADC_EN, OUTPUT); //pin14 on output mode
    digitalWrite(ADC_EN, HIGH); // pin 14 on high

    // Initialize screen
    start_screen();
    
    // Load calibration curve for [something something]
    esp_adc_cal_characteristics_t adc_chars;   // structure storing characteristics of an ADC 
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
    // Check type of calibration value used to characterize ADC val_type will store value
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        vref = adc_chars.vref;
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        
    } else {
        
    }
}

 
//Waveform loop runs on core 0
void Task1code(void * pvParameters){ waveform();}
/* end of single execution code ___________ below are main loop and methods main loop and buttoninit runs___________________
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
*/
void loop()
{
    showVoltage();
    button_loop();
}
