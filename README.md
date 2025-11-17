# IOT-Project-
This project uses two ESP32 boards communicating through ESP-NOW to run a simple solar panel cleaning demo. The controller sends a “CLEAN” command, and the second ESP32 moves a servo arm to perform the cleaning. Powered directly by a solar panel through a buck converter, the system is portable and easy to expand.

# Solar Panel Cleaning — ESP32 ESP-NOW Demo

Two-node demo: a **Controller** ESP32 sends "ALERT/CLEAN" messages via ESP-NOW to a **Rover (Receiver)** ESP32 which runs a servo cleaning sweep and drives the motor briefly.


### Contents
- `rover/receiver.ino` — Receiver code (your provided rover code)
- `controller/sender.ino` — Example sender code to transmit alerts
- `docs/WIRING.md` — Wiring notes for power, servo and HW-130 motor driver


### Libraries
- ESP32 core (Board package)
- ESP32Servo (install via Library Manager)


### How to use
1. Put each folder/file into a Git repo and push to GitHub.
2. Replace the `senderMAC` in `rover/receiver.ino` or use the controller `sender.ino` with the receiver's MAC.
3. Upload `receiver.ino` to the Rover ESP32, and `sender.ino` to the Controller ESP32.
