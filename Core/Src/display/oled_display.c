#include "oled_display.h"  // Include corresponding .h file
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"

// OLED Initialization Function
void oled_init(void) {
    ssd1306_Init();
}

// OLED Data Display Function
void oled_display(float voltage,float current, int soc, float power, float temperature,
		int soh, char* status, int hours, int minutes)
 {
    char buffer[30];

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

    // Voltage and Temperature Line
        sprintf(buffer, "V: %.2fV  T: %.1fC", voltage, temperature);
        ssd1306_SetCursor(2, 2);
        ssd1306_WriteString(buffer, Font_6x8, White);


        // Current and Power Line
        sprintf(buffer, "I: %.2fA P: %.2fW", current, power);
        ssd1306_SetCursor(2, 12);
        ssd1306_WriteString(buffer, Font_6x8, White);

            // SOC and SOH Line
            snprintf(buffer, sizeof(buffer), "SOC: %d%%  SOH: %d%%", soc, soh);

            ssd1306_SetCursor(2, 22);
            ssd1306_WriteString(buffer, Font_6x8, White);


            // Charging/Discharging Status
            sprintf(buffer, "Status: %s", status);
            ssd1306_SetCursor(2, 32);
            ssd1306_WriteString(buffer, Font_6x8, White);

            // Time Remaining
             sprintf(buffer, "Time Left: %dh %dm", hours, minutes);
             ssd1306_SetCursor(2, 42);
             ssd1306_WriteString(buffer, Font_6x8, White);


            ssd1306_UpdateScreen();

}
