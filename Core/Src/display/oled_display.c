#include "oled_display.h"  // Include corresponding .h file
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
#include "main.h"

const char* batteryStatusToString(BatteryStatus status) {
    switch (status) {
        case IDLE: return "Idle";
        case CHARGING: return "Charging";
        case FULL: return "Full";
        default: return "Unknown";
    }
}


// OLED Initialization Function
void oled_init(void) {
    ssd1306_Init();
}

// OLED Data Display Function
void oled_display(float voltage,float current, int soc, float power, float temperature,
		int soh, BatteryStatus batteryStatus, int hours, int minutes)
 {
    char buffer[30];
    ssd1306_Fill(Black);
    // **Voltage and Temperature Line**
    //ssd1306_SetCursor(2, 2);
    //sprintf(buffer, "                 "); // Clear previous text
    //ssd1306_WriteString(buffer, Font_6x8, Black);
    if (power<0.5 && batteryStatus==CHARGING)
    {
    	ssd1306_SetCursor(2, 32);
    	ssd1306_WriteString("Initializing", Font_7x10, White);
    	ssd1306_UpdateScreen();
    	return;

    }
    ssd1306_SetCursor(2, 2);
    sprintf(buffer, "V: %.2fV  T: %.1fC", voltage/1000, temperature); // show voltage in V
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Current and Power Line**
    //ssd1306_SetCursor(2, 12);
    //sprintf(buffer, "                 ");
    //ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 12);
    sprintf(buffer, "I: %.2fA P: %.2fW", current/1000, power); // Show current in A
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **SOC and SOH Line**
    //ssd1306_SetCursor(2, 22);
    //sprintf(buffer, "                ");
    //ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 22);
    snprintf(buffer, sizeof(buffer), "SOC: %d%%  SOH: %d%%", soc, soh);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Charging/Discharging Status**
    //ssd1306_SetCursor(2, 32);
    //sprintf(buffer, "                ");
    //ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 32);
    sprintf(buffer, "Status: %s", batteryStatusToString(batteryStatus));
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Time Remaining**
    //ssd1306_SetCursor(2, 42);
    //sprintf(buffer, "                ");
    //ssd1306_WriteString(buffer, Font_6x8, Black);

    ssd1306_SetCursor(2, 42);
    sprintf(buffer, "Time Left: %dh %dm", hours, minutes);
    ssd1306_WriteString(buffer, Font_6x8, White);

    // **Update OLED screen**
    ssd1306_UpdateScreen();
}
