const int A_1_PIN = 2;
const int A_2_PIN = 3;
const int B_1_PIN = 4;
const int B_2_PIN = 5;

void setup() {
  pinMode(A_1_PIN, OUTPUT);
  pinMode(A_2_PIN, OUTPUT);
  pinMode(B_1_PIN, OUTPUT);
  pinMode(B_2_PIN, OUTPUT);

  digitalWrite(A_1_PIN, HIGH);
  digitalWrite(A_2_PIN, LOW);
  digitalWrite(B_1_PIN, HIGH);
  digitalWrite(B_2_PIN, LOW);
}

void loop() {
}
