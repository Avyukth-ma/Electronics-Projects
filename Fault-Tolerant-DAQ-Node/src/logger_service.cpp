#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <Arduino.h>
#include "system_types.h"

#define EEPROM_DEATH_ADDRESS 0

// --- PRE-MAIN EXECUTION HOOK ---
// This variable survives the C runtime clearing phase
uint8_t mcusr_mirror __attribute__ ((section (".noinit")));

// This function runs immediately upon chip power-up, before setup() or loop()
void get_mcusr(void) __attribute__((naked)) __attribute__((section(".init3")));
void get_mcusr(void) {
  mcusr_mirror = MCUSR; // Capture the hardware reset flags
  MCUSR = 0;            // Clear flags so they are ready for next boot
  wdt_disable();        // Pause watchdog during boot sequence
}
// -------------------------------

void Logger_Check_Previous_Death(void) {
    uint32_t start_time = millis();
    while (!Serial && (millis() - start_time < 5000));

    Serial.println("\n--- BOOT DIAGNOSTICS ---");
    
    // Decode the hardware reset register
    if (mcusr_mirror & (1 << WDRF))  Serial.println("Reset Cause: WATCHDOG BITE (System Hang/Crash)");
    if (mcusr_mirror & (1 << BORF))  Serial.println("Reset Cause: BROWN-OUT (Power dipped below safe levels)");
    if (mcusr_mirror & (1 << EXTRF)) Serial.println("Reset Cause: EXTERNAL RESET (Physical button pressed)");
    if (mcusr_mirror & (1 << PORF))  Serial.println("Reset Cause: POWER-ON RESET (Plugged into power)");
    
    // Read the EEPROM Death Certificate
    uint8_t last_death = eeprom_read_byte((uint8_t*)EEPROM_DEATH_ADDRESS);
    if (last_death == MODE_CRITICAL) {
        Serial.println(">> FATAL ERROR RECOVERY: Previous State was CRITICAL (Voltage Failure)");
        eeprom_write_byte((uint8_t*)EEPROM_DEATH_ADDRESS, MODE_NORMAL);
    } else {
        Serial.println(">> No EEPROM death certificates found.");
    }
    Serial.println("------------------------\n");
}

void Logger_Record_Death(uint8_t mode) {
    eeprom_write_byte((uint8_t*)EEPROM_DEATH_ADDRESS, mode);
}