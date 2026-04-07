A fun electronics project using a D1 Mini (ESP8266) that simulates a countdown timer with lights, sound, and a relay. Purely for visual/audio effect (nothing dangerous).

🎯 Features
⏱️ Countdown from 5 → 0 on OLED display
🔊 Increasing beep pitch as time runs out
💡 Blinking LEDs synced with countdown
⚡ Relay trigger at 0 (for external effect)
🚨 “Boom” sequence:
Fast LED strobe
Siren sound
Display message: * BOOM * (not really)
🧰 Hardware Required
D1 Mini (ESP8266)
SSD1306 OLED display (SPI)
2x LEDs
2x 220Ω resistors
Passive buzzer
Relay module (5V)
Breadboard + jumper wires
Optional: external 5V supply (recommended for relay, since the d1 mini dosent seem to have enough power)
🔌 Wiring
OLED (SPI)
OLED Pin	D1 Mini
VCC	3.3V
GND	GND
SCL	D5 (SCK)
SDA	D7 (MOSI)
DC	D3
CS	D8
RES	D4
LEDs
LED	Connection
LED 1	D0 → resistor → LED → GND
LED 2	D2 → resistor → LED → GND
Buzzer
Pin	Connection
+	D1
-	GND
Relay Module
Pin	Connection
VCC	5V (USB or external PSU)
GND	GND (shared with D1 Mini)
IN	D6

🚀 How It Works
Device powers on
OLED initializes
Countdown begins:
LEDs blink
Buzzer beeps faster + higher pitch
At 0:
Relay is triggered
Boom sequence runs:
Strobe lights
Siren sound
Display message
System resets and repeats
🧠 Key Implementation Details
Custom tone_play() used (ESP8266 has no native tone())
Blocking loops create timing effects
Relay triggered before sound sequence to ensure proper timing

SPI OLED uses:

display.begin(0x00);
🧪 Troubleshooting
Relay LED on but no click
Not enough current → use external 5V
Weak relay module → test directly on PSU
Relay clicks at wrong time
Wrong wireing

Ensure trigger is before boom sequence:

digitalWrite(RELAY_PIN, LOW);
Display not working
Check SPI wiring
Ensure correct init (0x00, not SSD1306_SWITCHCAPVCC)
No sound
Confirm buzzer is passive, not active
🎮 Ideas for Improvements
Add a button to start countdown
Add longer countdown (10, 30 seconds)
Add RGB LEDs
Add WiFi trigger via ESP8266
Add sound effects from speaker module
⚡ Disclaimer

This is a harmless visual/sound project designed for learning electronics and programming.
It does not create any explosive or dangerous effect.
