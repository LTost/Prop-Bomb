// Moduels
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Setting pins and screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_DC    D3
#define OLED_CS    D8
#define OLED_RESET D4
#define RELAY_PIN  D6

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, 
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define LED_1   D0
#define LED_2   D2
#define BUZZER  D1

// Sound calculation
void tone_play(int pin, int freq, int duration_ms) {
	int period = 1000000 / freq;
	long cycles = (long)freq * duration_ms / 1000;
	for (long i = 0; i < cycles; i++) {
		digitalWrite(pin, HIGH);
		delayMicroseconds(period / 2);
		digitalWrite(pin, LOW);
		delayMicroseconds(period / 2);
	}
}

// Extra function to make it easier to call 
void beep(int freq, int ms) {
	tone_play(BUZZER, freq, ms);
}

// What the display shows
void show_number(int n) {
	display.clearDisplay();
	display.setTextColor(SSD1306_WHITE);
	display.setTextSize(6);
	display.setCursor(n >= 10 ? 20 : 48, 4);
	display.print(n);
	display.setTextSize(1);
	display.setCursor(28, 56);
	display.print("COUNTDOWN");
	display.display();
}

// Display Boom
void show_boom() {
	display.clearDisplay();
	display.setTextSize(3);
	display.setCursor(16, 0);
	display.print("* BOOM *");
	display.setTextSize(1);
	display.setCursor(22, 40);
	display.print("(not really)");
	display.setCursor(10, 54);
	display.print("have a nice day :)");
	display.display();
}

// LED state
void leds_all(bool state) {
	digitalWrite(LED_1, state);
	digitalWrite(LED_2, state);
}

// LED Blinking
void leds_blink_fast(int times) {
	for (int i = 0; i < times; i++) {
		leds_all(HIGH);
		delay(80);
		leds_all(LOW);
		delay(80);
	}
}

// Countdown tick
void tick(int n) {
	show_number(n);
	int freq = 400 + (5 - n) * 120;
	leds_blink_fast(2);
	beep(freq, 120);
	delay(200);
	leds_all(LOW);
	int gap = 200 + n * 80;
	delay(gap);
}

// Secuence for explotion
void boom_sequence() {
	for (int i = 0; i < 20; i++) {
		leds_all(HIGH);
		beep(1200, 30);
		leds_all(LOW);
		delay(30);
	}
	for (int rep = 0; rep < 4; rep++) {
		for (int f = 600;  f < 1400; f += 30) tone_play(BUZZER, f, 15);
		for (int f = 1400; f > 600;  f -= 30) tone_play(BUZZER, f, 15);
	}
	leds_all(HIGH);
	show_boom();
	delay(500);
	leds_all(LOW);
}

// Set up of the unit
void setup() {
	Serial.begin(115200);
	pinMode(LED_1,     OUTPUT);
	pinMode(LED_2,     OUTPUT);
	pinMode(BUZZER,    OUTPUT);
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, HIGH);
	if (!display.begin(0x00)) {
		Serial.println("SSD1306 init failed");
		while (true);
	}
	display.clearDisplay();
	display.display();
	delay(500);
}

// The actual running loop 
void loop() {
	for (int i = 5; i >= 1; i--) tick(i);
	show_number(0);
	delay(300);
	Serial.println("FIRING RELAY NOW");
	digitalWrite(RELAY_PIN, LOW);
	delay(50);
	boom_sequence();
	delay(4000);
	digitalWrite(RELAY_PIN, HIGH);
	display.clearDisplay();
	display.display();
	leds_all(LOW);
	delay(1000);
}