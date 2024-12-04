#include <Arduino.h>
#include <ESP32Servo.h>  // Thư viện điều khiển Servo
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include <Ticker.h>


namespace
{
    const char *ssid = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;
    const char *ldr_topic1 = "esp32/ldr";       // Chủ đề gửi giá trị LDR
    const char *ldr_topic2 = "esp32/ldr2";     // Chủ đề gửi giá trị LDR 2
    const char *servo_topic = "esp32/servo";  // Chủ đề điều khiển Servo
    const char *echo_topic = "esp32/echo_test";
    unsigned int publish_count = 0;
    uint16_t keepAlive = 15;    // Giữ kết nối MQTT (giây)
    uint16_t socketTimeout = 5; // Thời gian chờ MQTT (giây)
}

WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);
Servo myServo;

Ticker mqttLDRTicker;

// ---------------------- Cấu hình phần cứng ----------------------
#define LDR1_PIN 34      // Chân đọc giá trị cảm biến ánh sáng 1
#define LDR2_PIN 36      // Chân đọc giá trị cảm biến ánh sáng 2
#define SERVO_PIN 19     // Chân điều khiển Servo

// ---------------------- Chức năng ----------------------

// Gửi giá trị LDR qua MQTT
void publishLDR()
{
    int ldrValue1 = analogRead(LDR1_PIN);  // Đọc giá trị cảm biến LDR 1
    int ldrValue2 = analogRead(LDR2_PIN);  // Đọc giá trị cảm biến LDR 2

    // Gửi giá trị cảm biến LDR 1
    Serial.print("LDR 1 Value: ");
    Serial.println(ldrValue1);
    mqttClient.publish(ldr_topic1, String(ldrValue1).c_str(), false);

    // Gửi giá trị cảm biến LDR 2
    Serial.print("LDR 2 Value: ");
    Serial.println(ldrValue2);
    mqttClient.publish(ldr_topic2, String(ldrValue2).c_str(), false);
}

// Điều khiển servo thông qua MQTT
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("From %s:  ", topic);
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    if (strcmp(topic, servo_topic) == 0)
    {
        char angleStr[length + 1];
        memcpy(angleStr, payload, length);
        angleStr[length] = '\0';
        int angle = atoi(angleStr);  // Chuyển đổi giá trị từ chuỗi sang số nguyên
        if (angle >= 0 && angle <= 180)
        {
            Serial.print("Setting servo angle to: ");
            Serial.println(angle);
            myServo.write(angle);  // Điều chỉnh góc servo
        }
        else
        {
            Serial.println("Invalid angle value received!");
        }
    }
}

// Kết nối lại MQTT
void mqttReconnect()
{
    while (!mqttClient.connected())
    {
        Serial.println("Attempting MQTT connection...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if (mqttClient.connect(client_id.c_str(), MQTT::username, MQTT::password))
        {
            Serial.print(client_id);
            Serial.println(" connected");

            mqttClient.subscribe(echo_topic);
            mqttClient.subscribe(servo_topic);  // Đăng ký nhận tin nhắn để điều khiển servo
        }
        else
        {
            Serial.print("MQTT connect failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 1 seconds");
            delay(1000);
        }
    }
}

// ---------------------- Setup và Loop ----------------------
void setup()
{
    Serial.begin(115200);
    delay(10);

    setup_wifi(ssid, password);
    tlsClient.setCACert(ca_cert);

    mqttClient.setCallback(mqttCallback);
    mqttClient.setServer(MQTT::broker, MQTT::port);

    mqttLDRTicker.attach(1, publishLDR);  // Gửi giá trị LDR mỗi giây

    myServo.attach(SERVO_PIN);  // Gắn Servo
    pinMode(LDR1_PIN, INPUT);   // Cấu hình chân cảm biến ánh sáng 1
    pinMode(LDR2_PIN, INPUT);   // Cấu hình chân cảm biến ánh sáng 2
}

void loop()
{
    if (!mqttClient.connected())
    {
        mqttReconnect();
    }
    mqttClient.loop();  // Lắng nghe tin nhắn MQTT
}
