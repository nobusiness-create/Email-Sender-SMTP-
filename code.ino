#include <WiFi.h>
#include <ESP32_MailClient.h>

#define WIFI_SSID "Enter Wifi name"
#define WIFI_PASSWORD "Enter Wfi password"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "Enter senter's email"
#define AUTHOR_PASSWORD "Enter password here"
#define RECIPIENT_EMAIL "Enter receiver's email"

SMTPSession smtp;
SMTP_Message message;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nWiFi Connected!");

  smtp.debug(1);

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  message.sender.name = "ESP32 Sender";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "ESP32 TESTING EMAIL";
  message.addRecipient("Receiver", RECIPIENT_EMAIL);

  message.text.content = "Hello World from ESP32";


  if (!smtp.connect(&session)) {
    Serial.println("SMTP connection failed");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Error sending Email: " + smtp.errorReason());
  } else {
    Serial.println("Email sent successfully!");
  }

  smtp.closeSession();
}

void loop() {
}
