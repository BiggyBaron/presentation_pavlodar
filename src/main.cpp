// Данный кусочек кода отвечает за внедрения "Шапки", в которой прописаны детали библиотеки
#include "qmobot.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "UniversalTelegramBot.h"

// Напишите имя и пароль от ВайФай
char ssid[] = "Cleverest";     // Имя ВайФай
char password[] = "Robot1x1sTheBest";   // Пароль

#define BOTtoken "2055112763:AAFcfBMBrJztaQ2cMw2nm6Q_ly5VxkcVuyI"  // Bot Token (получите у Botfather)
String botname = "@PresentationPavlodar_bot"; // Напишите имя бота


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 500;
long Bot_lasttime;
bool Start = false;


void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/alga") {
      digitalWrite(BUILTIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)

      bot.sendMessage(chat_id, "Вперед!", "");
      run('L', 255);
      run('R', 255);
      delay(500);
      run('L', 0);
      run('R', 0);
    }

    if (text == "/artqa") {
      digitalWrite(BUILTIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)

      bot.sendMessage(chat_id, "Назад!", "");
      run('L', -255);
      run('R', -255);
      delay(500);
      run('L', 0);
      run('R', 0);
    }

    if (text == "/bile") {
      digitalWrite(BUILTIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)

      bot.sendMessage(chat_id, "Танцую!", "");
      run('L', 150);
      run('R', -150);
      delay(500);
      run('L', 0);
      run('R', 0);
      delay(100);
      run('L', -150);
      run('R', 150);
      delay(500);
      run('L', 0);
      run('R', 0);
    }

    if (text == "/start") {
      String welcome = "Привет, я Qmobot лучшего колледжа РК!\n";
      welcome += "/alga : поеду вперед! \n";
      welcome += "/artqa : поеду назад! \n";
      welcome += "/bile : станцую для Вас!\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  begin(true, true);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  erase();
  show("Qosylu...", 0, 0);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  erase();
  show("Kütude!", 0, 0);
  show("Telegram: ", 0, 20);
  show(botname, 0, 30);
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
