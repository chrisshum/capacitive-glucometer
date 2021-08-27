void start_screen() {
      tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(4);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(0, 0);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(2);  // start up sequence, sets text parameters

    if (TFT_BL > 0) { // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
        pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
        digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    }

    tft.setSwapBytes(true); // corrects endianness, 
    tft.pushImage(0, 0,  240, 135, ttgo);
    espDelay(500);

    tft.setRotation(0);
    tft.fillScreen(TFT_RED);
    espDelay(100);
    tft.fillScreen(TFT_BLUE);
    espDelay(100);
    tft.fillScreen(TFT_GREEN);
    espDelay(100);
    // display start up screen 
    button_init(); // sets up button press parameters 

    
 
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Press Right", tft.width() / 2, tft.height() /2 -96 );
    tft.drawString("Blood Sugar", tft.width() / 2, tft.height() / 2 - 64 );
    tft.drawString("Hold Left", tft.width() / 2, tft.height() / 2 + 64);
    tft.drawString("Deep Sleep", tft.width() / 2, tft.height() / 2 + 96 );
    tft.setTextDatum(TL_DATUM); 
    // sets up main menu directions 

}
