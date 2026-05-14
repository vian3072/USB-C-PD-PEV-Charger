#include <Wire.h>
#include <Adafruit_INA228.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define PWM_PIN 19        // change to your pin
#define EN_PIN 5         // enable pin
#define PWM_FREQ 78125    // 78.125 kHz
#define PWM_RESOLUTION 10 // 10-bit (0–1023)

volatile bool boost = true; 
volatile int duty = 100; //0->1023 fr duty cycle
static double max_current_out_in_ma = 500;
static double max_P_in = 5;

static double I_out_reff_in_ma = 300;

TaskHandle_t Task1;
TaskHandle_t Task2;

float measured_results[6];

uint16_t counts[] = {1, 4, 16, 64, 128, 256, 512, 1024};
Adafruit_INA228 ina228_0x40 = Adafruit_INA228();
Adafruit_INA228 ina228_0x41 = Adafruit_INA228();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Task1code: Handling touch and oled 
void Task1code( void * pvParameters );

//Task2: PWM and future control system
void Task2code( void * pvParameters );

void setup() {
  Serial.begin(115200);

  // Attach PWM to pin
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);
  pinMode(EN_PIN, OUTPUT);

  // ESP32 I2C pins
  Wire.begin(21, 22);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    while (true) {
      delay(10);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

   if (!ina228_0x41.begin(0x41)) {
    Serial.println("Couldn't find INA228 chip 0x41");
    while (1)
      ;
  }
   if (!ina228_0x40.begin(0x40)) {
    Serial.println("Couldn't find INA228 chip 0x40");
    while (1)
      ;
  }
  Serial.println("INA228 0x41,0x40 found");
  
  ina228_0x41.setShunt(0.015, 10.0);
  ina228_0x40.setShunt(0.015, 5);
  ina228_0x41.setAveragingCount(INA228_COUNT_16); //1,4,16,64,128,512,1024
  ina228_0x40.setAveragingCount(INA228_COUNT_16);
  ina228_0x41.setVoltageConversionTime(INA228_TIME_150_us);  //50,84,150,280,540,1052,2074,4120
  ina228_0x40.setVoltageConversionTime(INA228_TIME_150_us);  
  ina228_0x41.setCurrentConversionTime(INA228_TIME_280_us);
  ina228_0x40.setCurrentConversionTime(INA228_TIME_280_us);
  
  
   xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}

void loop() {
}
