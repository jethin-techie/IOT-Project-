#include <WiFi.h>
#include <esp_now.h>


// Replace with receiver (rover) MAC address
uint8_t receiverMAC[] = {0x8C, 0x4F, 0x00, 0x2F, 0x51, 0xB4};


struct Message {
uint8_t type; // 1 = alert, 2 = cleaning_done
float voltage;
float current;
};


Message outgoing;


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("Last Packet Send Status: ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);


if (esp_now_init() != ESP_OK) {
Serial.println("ESP-NOW init failed");
return;
}


esp_now_register_send_cb(OnDataSent);


esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, receiverMAC, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;
esp_now_add_peer(&peerInfo);


Serial.println("Controller ready");
}


void loop() {
// Example: send alert message
outgoing.type = 1; // alert
outgoing.voltage = 12.34;
outgoing.current = 0.56;


esp_now_send(receiverMAC, (uint8_t*)&outgoing, sizeof(outgoing));
Serial.println("Alert sent");
delay(5000);
}
