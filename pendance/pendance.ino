/*
 * TODO: 
 * - don't go into other mode after being in red mode
 * - click buttons in succession from green mode to get to red mode
 * - automatic activation of red mode activated after 15 s (from yellow mode)
 *     - click reset button to reset timer
 *     - if timer runs out activate red mode
 * - flash led when time is running out (blink at 5 s)
 */

int slide_g = 8;
int slide_y = 7;
int reset = 6;
int panic_pin = 0;
int led = 9;

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
  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if ((green_mode == false) && (digitalRead(slide_g) == LOW)){
    enable_green_mode();
  }else if ((yellow_mode == false) && (digitalRead(slide_y) == LOW)){
    enable_yellow_mode();
  }
 

}

void panic() {
  num_panic++;
  if (num_panic == PANIC_TRIGGER) {
    enable_panic_mode();
  }
}

void enable_panic_mode() {
  num_panic = 0;
  red_mode = true;
  green_mode = false;
  yellow_mode = false;
  // TODO: panic 
  Serial.println("enabling red mode");
}

void enable_yellow_mode() {
  PANIC_TRIGGER = 1; 
  yellow_mode = true;
  green_mode = false;
  red_mode = false;
  Serial.println("enabling yellow mode");
}

void enable_green_mode() {
  PANIC_TRIGGER = 3;
  green_mode = true;
  yellow_mode = false;
  red_mode = false;
  Serial.println("enabling green mode");
}

void test_led() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
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
