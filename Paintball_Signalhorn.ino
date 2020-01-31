#define second 1000 //ms
#define countdowns 9 //times honk before starting honk occures
#define countdownhonk_duration 50 //ms
#define playstarthonk_duration 400 //ms
#define checktime 100 //ms - aprox. time to check, if a button was pressed in the past

const int leftBtn = 4;
const int midBtn = 3;
const int rightBtn = 2;
const int ledPin = 13;
const int hornPin = 9;
//pwm freq:
//3,9,10,11 = 490Hz
//5,6 = 980hz

bool btntoggle = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(hornPin, OUTPUT);

  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(midBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);

  analogWrite(hornPin, 50);
  delay(50);
  analogWrite(hornPin, 0);

}

void writeLEDandHorn(byte status) {
  digitalWrite(hornPin, status);
  digitalWrite(ledPin, status);
}

void honkFor(int duration) {
  writeLEDandHorn(HIGH);
  delay(duration);
  writeLEDandHorn(LOW);
}

void pulsedHonk(int ontime, int fulltime) {
  for(int i = 0; i <= 5; i++) {
    writeLEDandHorn(HIGH);
    delay(ontime);
    writeLEDandHorn(LOW);
    delay(fulltime-ontime);
  }
}

void countdown() {
  for (int i = 1; i <= countdowns; i++) {
    honkFor(countdownhonk_duration);
    for (int t = second - countdownhonk_duration ; t > 0 ; t -= checktime) {
      delay(min(t,checktime));
      if (digitalRead(midBtn) == LOW) {
        if (btntoggle) return;
      } else {
        btntoggle = true;
      }
    }
  }
  honkFor(500);
}

void loop() {
  if (digitalRead(midBtn) == LOW) {
    if (!btntoggle) countdown();
  } else {
    btntoggle = false;
  }

  if(digitalRead(rightBtn) == LOW) {
    writeLEDandHorn(HIGH);
  } else {
    writeLEDandHorn(LOW);
  }

  if(digitalRead(leftBtn) == LOW) {
    pulsedHonk(3,5);
  }

  delay(5); //give that chip a break, will ya?
}
