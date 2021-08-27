void button_init() // loop that begins in setup event handlers, if button loops are initialized 
{
    btn2.setLongClickHandler([](Button2 & b) {
        btnCick = false;
        int r = digitalRead(TFT_BL);
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.setTextSize(2);
        tft.drawString("Press again",  tft.width() / 2, tft.height() / 2 - 32 );
        tft.drawString("to wake up",  tft.width() / 2, tft.height() / 2 );
        espDelay(4000);
        digitalWrite(TFT_BL, !r); // display backlight off just opposite of the digital read 

        tft.writecommand(TFT_DISPOFF); // display screen draw off
        tft.writecommand(TFT_SLPIN);  // microcontroller off 
        //After using light sleep, you need to disable timer wake, because here use external IO port to wake up
        esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
        // esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // right button used to wake up 
        delay(200);
        esp_deep_sleep_start();
    });
    btn1.setPressedHandler([](Button2 & b) {
        btnCick = true;
    });

}


void button_loop()
{
    btn1.loop(); // checks state of button 1
    btn2.loop(); // checks state of button 2 
    // depending on what event is pressed will execute code in the button_init() then goes back to the main loop 
}
