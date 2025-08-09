# ESP32 OTA + Telegram Bot + LCD 1602 I2C

Цей проєкт дозволяє **керувати оновленням прошивки ESP32 через GitHub Releases** за допомогою команди в **Telegram-боті**, а також відображати статус на LCD 1602 I2C та вбудованому світлодіоді.

## 📦 Функціонал
- **OTA-оновлення з GitHub**: команда `/update` в Telegram запускає завантаження останньої прошивки з GitHub Releases.
- **Миттєве підтвердження**: після команди `/update` бот одразу відповідає, що оновлення почалося.
- **Інформація про пристрій**: команда `/info` показує:
  - Назву Wi-Fi (SSID)
  - IP адрес
  - Версію прошивки
  - Рівень сигналу RSSI  
  Інформація надсилається в Telegram і виводиться на LCD.
- **WiFiManager**: перше налаштування Wi-Fi через вебпортал.
- **LCD 1602 I2C**: відображення статусу роботи, версії прошивки, процесу оновлення.
- **Вбудований світлодіод**:
  - моргає при старті (тест),
  - може використовуватись для індикації OTA.

## 📂 Структура проєкту
```

include/  
secrets.h.example  
src/  
main.cpp  
lcd_display.*  
led_control.*  
wifi_setup.*  
telegram_api.*  
ota_update.*  
platformio.ini  
.github/  
workflows/  
build-release.yml

```

## ⚙️ Налаштування

1. Створити Telegram-бота через [@BotFather](https://t.me/BotFather) та зберегти:
   - `TG_BOT_TOKEN`
   - `TG_CHAT_ID`

2. Скопіювати конфігурацію:
   ```bash
   cp include/secrets.h.example include/secrets.h
   ```

і заповнити поля у `secrets.h`.

3. Налаштувати GitHub Actions:
    
    - Додати Secrets у репозиторій:
        
        - `TG_BOT_TOKEN`
            
        - `TG_CHAT_ID`
            
4. Встановити PlatformIO:
    
    ```bash
    pip install platformio
    ```
    

## 🚀 Швидкий старт

```bash
# Клонування репозиторію
git clone https://github.com/dz-vadim/esp32-ota-telegram.git && cd esp32-ota-telegram

# Встановлення PlatformIO
pip install platformio

# Повне очищення пам'яті і прошивка
pio run -e esp32dev -t erase -t upload

# Або тільки прошивка без очищення
pio run -e esp32dev -t upload

# Моніторинг серійного порту
python -m platformio device monitor
# або
pio device monitor
```

## 🚀 Використання

Після першого запуску:

- Плата підніме WiFiManager портал (`ESP32-Setup`).
    
- Підключитися і ввести дані Wi-Fi.
    
- На LCD з’явиться IP адреса.
    
- У Telegram прийде повідомлення:
    
    ```
    ✅ Device online. FW v<номер>
    WiFi: <SSID>
    IP: <адреса>
    Send /info or /update
    ```
    

Команди в Telegram:

- `/info` — показує інформацію про плату у Telegram і на LCD.
    
- `/update` — запускає OTA оновлення з GitHub Releases.
    

## 🔌 Підключення LCD 1602 I2C до ESP32

|LCD 1602 I2C|ESP32|
|---|---|
|GND|GND|
|VCC|3.3V або 5V|
|SDA|GPIO 21|
|SCL|GPIO 22|

## 🔄 Як працює OTA

1. GitHub Actions збирає прошивку та публікує її в **Releases**.
    
2. ESP32 при отриманні команди `/update` звертається за файлом `firmware.bin` з останнього релізу.
    
3. Якщо оновлення успішне:
    
    - LCD показує `Update OK / Rebooting...`
        
    - пристрій перезавантажується з новою прошивкою.
        
4. Якщо оновлень немає або помилка — надсилається повідомлення в Telegram.
    

## 🛠 Залежності

- `tzapu/WiFiManager`
    
- `marcoschwartz/LiquidCrystal_I2C`
    
- `bblanchon/ArduinoJson`
    

## 📌 Примітки

- На більшості ESP32 вбудований LED підключений до GPIO2.
    
- LCD розрахований на 16×2 символи.
    
- Якщо після OTA команда `/update` повторюється — переконайтеся, що `Preferences` зберігають `lastId`.