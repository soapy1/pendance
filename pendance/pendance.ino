/*
 * TODO: 
 * - when swtiched to red have a 3 quick buzzes
 * 
 */

int slide_g = 8;
int slide_y = 7;
int reset_pin = 1;
int panic_pin = 0;
int led = 9;

int green_mode = false;
int yellow_mode = false;
int red_mode = false;

int yellow_mode_count_down = 15000; // 15 seconds
int yellow_mode_blink_count_down = 5000; // 5 seconds
int num_yellow_mode_bink_count = yellow_mode_count_down/yellow_mode_blink_count_down; // 3 times
unsigned long yellow_mode_start_time = 0;

volatile int num_panic = 0;
int PANIC_TRIGGER = 3;

int reset_steps = 0;

void setup() {
  pinMode(slide_g, INPUT);
  pinMode(slide_y, INPUT);  
  pinMode(reset_pin, INPUT_PULLUP);
  attachInterrupt(reset_pin, reset, FALLING);
  pinMode(panic_pin, INPUT_PULLUP);
  attachInterrupt(panic_pin, panic, FALLING);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (red_mode == false) {
    if ((green_mode == false) && (digitalRead(slide_g) == LOW)){
      enable_green_mode();
    }else if ((yellow_mode == false) && (digitalRead(slide_y) == LOW)){
      enable_yellow_mode();
    }
    
    if (yellow_mode == true) {
      if (millis() > (yellow_mode_start_time + yellow_mode_count_down)) {
        enable_panic_mode(); 
      } else if (activate_warning() == true) {
        Serial.println("yellow mode warning");
        blink_light(1);
      }
    }
  } else if (red_mode == true) {
     if ((digitalRead(slide_y) == LOW) && (reset_steps == 0)) {
       reset_steps = 1;
     }
     if ((digitalRead(slide_g) == LOW) && (reset_steps == 1)) {
       reset_steps = 2;
     }
     if (reset_steps == 2) {
       enable_green_mode();
       reset_steps = 0;
     }
  }
}

boolean activate_warning(){
  for (int i=1; i<=num_yellow_mode_bink_count; i++){
    if ((millis() > (yellow_mode_start_time + (i*yellow_mode_blink_count_down))) && (millis() < (yellow_mode_start_time + (i*yellow_mode_blink_count_down)+100))) {
      Serial.println("warning no " + i);
      return true;
    }
  }
  return false;
}

void panic() {
  num_panic++;
  if (num_panic == PANIC_TRIGGER) {
    enable_panic_mode();
  }
}

void reset() {
  if (yellow_mode == true) {
    yellow_mode_start_time = millis();
  }
}

void enable_panic_mode() {
  red_mode = true;
  green_mode = false;
  yellow_mode = false;
  num_panic = 0;
  Serial.println("enabling red mode");
  blink_light(7);
  // TODO: panic
}

void enable_yellow_mode() {
  blink_light(1);
  PANIC_TRIGGER = 1; 
  yellow_mode = true;
  green_mode = false;
  red_mode = false;
  yellow_mode_start_time = millis();
  Serial.println("enabling yellow mode");
}

void enable_green_mode() {
  PANIC_TRIGGER = 3;
  green_mode = true;
  yellow_mode = false;
  red_mode = false;
  Serial.println("enabling green mode");
}

void blink_light(int times) {
  for (int i=0; i<times; i++) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000); 
  }
}

void blink_light(int blink_length_high, int blink_length_low, int times) {
  for (int i=0; i<times; i++) {
    digitalWrite(led, HIGH);
    delay(blink_length_high);
    digitalWrite(led, LOW);
    delay(blink_length_low); 
  }
}

void test_led() {
  Serial.println("testing led");
  blink_light(4);
  delay(2000);
}

void test_slide() {
   if (digitalRead(slide_g) == LOW){
    digitalWrite(13, HIGH);
  }else if (digitalRead(slide_y) == LOW){
    digitalWrite(13, LOW);
  } 
}
