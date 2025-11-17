#include <WiFi.h>
// ============ LOOP ============
void loop() {
delay(3000);
Serial.println("...Rover active, waiting for message...");
}


// ============ CALLBACK ============
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
if (len != sizeof(Message)) return;


Message msg;
memcpy(&msg, data, sizeof(msg));


Serial.println("\n\ud83d\udce1 Message received!");
Serial.print("Type: "); Serial.println(msg.type);
Serial.print("Voltage: "); Serial.println(msg.voltage);
Serial.print("Current: "); Serial.println(msg.current);


// Trigger servo and motors only for alert message
if (msg.type == 1) {
Serial.println("\u2699 Triggering cleaning servo and moving forward...");
rotateServoAndMoveMotor();


// Send acknowledgment
Message ack;
ack.type = 2; // cleaning done
ack.voltage = msg.voltage;
ack.current = msg.current;


esp_now_send(senderMAC, (uint8_t*)&ack, sizeof(ack));
Serial.println("\u2705 Cleaning done acknowledgment sent!");
}
}


// ============ SERVO AND MOTOR ACTION ============
void rotateServoAndMoveMotor() {
motorsForward(); // start motors


// Sweep servo 0 -> 180 -> 0
for (int pos = 0; pos <= 180; pos += 10) {
cleaner.write(pos);
delay(20);
}
delay(300);
for (int pos = 180; pos >= 0; pos -= 10) {
cleaner.write(pos);
delay(20);
}


motorsStop(); // stop motors after servo done
}


void motorsForward() {
// Motor A forward
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
analogWrite(ENA, 200); // adjust speed 0-255


// Motor B forward (shared pins)
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(ENB, 200);
}


void motorsStop() {
digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
analogWrite(ENA, 0);
analogWrite(ENB, 0);
}
