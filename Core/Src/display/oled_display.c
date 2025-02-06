#include "oled_display.h"  // Include corresponding .h file
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"

// OLED Initialization Function
void oled_init(void) {
    ssd1306_Init();
}

// OLED Data Display Function
void oled_display(float voltage,float current, float soc, float power)
 {
    char buffer[10];

    //for debugging
    //printf("Checking OLED at I2C Address: 0x%X\n", (SSD1306_I2C_ADDR << 1));

    //if (HAL_I2C_IsDeviceReady(&hi2c1, (SSD1306_I2C_ADDR << 1), 10, 1000) == HAL_OK)
    //{
        //printf("OLED Found at 0x3C!\n");
    //}
    //else
    //{
        //printf("OLED NOT Found! Check Wiring!\n");
    //}

    ssd1306_Fill(Black);

        // Print Voltage
            sprintf(buffer, "V: %.2fV", voltage);
            ssd1306_SetCursor(2, 2);
            ssd1306_WriteString(buffer, Font_6x8, White);

            // Print Current
            sprintf(buffer, "I: %.2fA", current);
            ssd1306_SetCursor(2, 12);
            ssd1306_WriteString(buffer, Font_6x8, White);

            // Print State of Charge (SOC)
            sprintf(buffer, "SOC: %.1f%%", soc);
            ssd1306_SetCursor(2, 22);
            ssd1306_WriteString(buffer, Font_6x8, White);

            // Print Power
            sprintf(buffer, "P: %.2fW", power);
            ssd1306_SetCursor(2, 32);
            ssd1306_WriteString(buffer, Font_6x8, White);

            ssd1306_UpdateScreen();

}
