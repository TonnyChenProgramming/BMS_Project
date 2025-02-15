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

    // **Voltage and Temperature Line**
    ssd1306_SetCursor(2, 2);
    sprintf(buffer, "                 "); // Clear previous text
    ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 2);
    sprintf(buffer, "V: %.2fV  T: %.1fC", voltage, temperature);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Current and Power Line**
    ssd1306_SetCursor(2, 12);
    sprintf(buffer, "                  ");
    ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 12);
    sprintf(buffer, "I: %.2fA P: %.2fW", current, power);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **SOC and SOH Line**
    ssd1306_SetCursor(2, 22);
    sprintf(buffer, "                ");
    ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 22);
    snprintf(buffer, sizeof(buffer), "SOC: %d%%  SOH: %d%%", soc, soh);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Charging/Discharging Status**
    ssd1306_SetCursor(2, 32);
    sprintf(buffer, "                ");
    ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 32);
    sprintf(buffer, "Status: %s", status);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Time Remaining**
    ssd1306_SetCursor(2, 42);
    sprintf(buffer, "                ");
    ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 42);
    sprintf(buffer, "Time Left: %dh %dm", hours, minutes);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Update OLED screen**
    ssd1306_UpdateScreen();
}
