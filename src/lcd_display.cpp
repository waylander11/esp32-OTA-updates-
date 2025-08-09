#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_display.h"
#include "secrets.h"

#ifndef LCD_I2C_ADDR
#define LCD_I2C_ADDR 0x27
#endif
#ifndef LCD_COLS
#define LCD_COLS 16
#endif
#ifndef LCD_ROWS
#define LCD_ROWS 2
#endif

static LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);
static bool lcdReady = false;

static void ensureInit() {
  if (!lcdReady) {
    lcd.init();
    lcd.backlight();
    lcdReady = true;
  }
}

void lcdInit() {
  ensureInit();
}

void lcdShow(const String &l1, const String &l2) {
  ensureInit();
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
}

// ---- wrappers (compat layer) ----
void showUpdating()          { lcdShow("Updating...", "Please wait"); }
void showUpdateDone(bool ok) { lcdShow(ok ? "Update OK" : "Update FAIL",
                                       ok ? "Rebooting..." : "Check logs"); }
void showWiFiPortal()        { lcdShow("WiFi Portal", "Connect & config"); }
void lcdPrint2(const String &l1, const String &l2) { lcdShow(l1, l2); }