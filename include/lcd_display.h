#pragma once
#include <Arduino.h>

void lcdInit();
void lcdShow(const String &l1, const String &l2);

// --- wrappers used elsewhere ---
void showUpdating();
void showUpdateDone(bool success);
void showWiFiPortal();
void lcdPrint2(const String &l1, const String &l2);