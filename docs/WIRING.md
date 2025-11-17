# Wiring Notes


- Power the ESP32 from a regulated 5V buck converter (do not feed 7.4V directly).
- Servo VCC -> 5V (buck OUT). Servo GND -> common GND with ESP32 and battery.
- HW-130 (L298N) motor Vmot -> Battery + (7.4V). Motor GND -> common GND.
- Motor IN pins -> match pins in `receiver.ino` (IN1-IN4, ENA/ENB).
- Ensure all grounds are connected.
