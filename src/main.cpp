#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <vector>
#include <string>

const char *ssid = "ESP32_Card_Quiz_Game";

unsigned int counterCard = 0;

struct QuizQuestion {
    std::string question;
    std::string choiceA;
    std::string choiceB;
    std::string choiceC;
    std::string ChoiceD;
};


std::vector<QuizQuestion> QAA = {
    {
        "What is the worlds tallest ice mountain", 
        "A. Mt. Fuji", 
        "B. Tommorow", 
        "C. NExt", 
        "D. NOT NOW"       
    }
};

WebServer server(80);

bool handleFileRead(String path) {

    Serial.println("Requested file: " + path);
    if (path.endsWith("/")) {
        path += "index.html";
    }
    String contentType = "text/plain";

    if (path.endsWith(".html"))
        contentType = "text/html";
    else if (path.endsWith(".css"))
        contentType = "text/css";
    else if (path.endsWith(".js"))
        contentType = "application/javascript";
    else if (path.endsWith(".ico"))
        contentType = "image/x-icon";

    if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, "r");
        Serial.println("the file has been sent to the client" + file);
        server.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    if(!LittleFS.begin(true)) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    WiFi.softAP(ssid, "", 1, 0, 1);

    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());


    // The next problem now is how you can send the data from the 
    // "/textQAA" route
    server.on("/textQAA", HTTP_GET, [](){
        server.send(200, "text/plain", "Aces of spade");
    });

    server.onNotFound([]() {
        if(!handleFileRead(server.uri())) {
            server.send(404, "text/plain", "Theres something wrong with you!");
        }
    });

    server.begin();
    Serial.println("HTTP started");
}


void loop() {
    server.handleClient();



    // on the loop will all the sensor input
    // and the output for the counter
}