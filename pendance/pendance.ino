/*
 * TODO: 
 * - don't go into other mode after being in red mode
 * - click buttons in succession from green mode to get to red mode
 * - automatic activation of red mode activated after 15 s (from yellow mode)
 *     - click reset button to reset timer
 *     - if timer runs out activate red mode
 
 * - use one led
 * - flash led when time is running out (blink at 5 s)
 */

int slide_g = 8;
int slide_y = 7;
int reset = 6;
int panic_pin = 0;
int red_led = 11;
int blue_led = 10;
int green_led = 9;

int green_mode = false;
int yellow_mode = false;
int red_mode = false;

volatile int num_panic = 0;
int PANIC_TRIGGER = 3;

void setup() {                
  pinMode(slide_g, INPUT);
  pinMode(slide_y, INPUT);  
  pinMode(reset, INPUT);
  pinMode(panic_pin, INPUT_PULLUP);
  attachInterrupt(panic_pin, panic, FALLING);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if ((green_mode == false) && (digitalRead(slide_g) == LOW)){
    enable_green_mode();
  }else if ((yellow_mode == false) && (digitalRead(slide_y) == LOW)){
    enable_yellow_mode();
  }
 
    if (digitalRead(slide_g) == LOW){
    digitalWrite(13, HIGH);
  }else if (digitalRead(slide_y) == LOW){
    digitalWrite(13, LOW);
  } 
}

void panic() {
  num_panic++;
  if (num_panic == PANIC_TRIGGER) {
    enable_panic_mode();
  }
}

void setColor(int red, int green, int blue)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(red_led, red);
  analogWrite(green_led, green);
  analogWrite(blue_led, blue);  
}

void blink_color(int red, int green, int blue, int times) {
  for (int i=0; i<times; i++){ 
    setColor(red, green, blue);
    delay(500);
    digitalWrite(red_led, LOW);
    digitalWrite(blue_led, LOW);
    digitalWrite(green_led, LOW);
    delay(500);
  }
}

void enable_panic_mode() {
  blink_color(255, 0, 0, 4);
  num_panic = 0;
  red_mode = true;
  green_mode = false;
  yellow_mode = false;
  // TODO: panic 
  Serial.println("enabling red mode");
}

void enable_yellow_mode() {
  blink_color(255, 255, 0, 4);
  PANIC_TRIGGER = 1; 
  yellow_mode = true;
  green_mode = false;
  red_mode = false;
  Serial.println("enabling yellow mode");
}

void enable_green_mode() {
  blink_color(0, 255, 0, 4);
  PANIC_TRIGGER = 3;
  green_mode = true;
  yellow_mode = false;
  red_mode = false;
  Serial.println("enabling green mode");
}

void test_led() {
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000); 
}

void test_push_buttons() {
  if (digitalRead(reset) == LOW) {
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
}

void test_slide() {
   if (digitalRead(slide_g) == LOW){
    digitalWrite(13, HIGH);
  }else if (digitalRead(slide_y) == LOW){
    digitalWrite(13, LOW);
  } 
}
