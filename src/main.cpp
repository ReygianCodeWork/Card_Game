#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <vector>
#include <string>
#include <ArduinoJson.h>

const char *ssid = "ESP32_Card_Quiz_Game";

unsigned int counterCard = 0;

struct QuizQuestion {
    String question;
    String choiceA;
    String choiceB;
    String choiceC;
    String choiceD;
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


// This will handle the question queueing acquisition
void handleGetQuestion() {
    JsonDocument doc;

    doc["question"] = QAA[counterCard].question;
    doc["a"] = QAA[counterCard].choiceA;
    doc["b"] = QAA[counterCard].choiceB;
    doc["c"] = QAA[counterCard].choiceC;
    doc["d"] = QAA[counterCard].choiceD;

    
    String jsonResponse;
    serializeJson(doc, jsonResponse);

    Serial.println(jsonResponse);

    server.send(200, "application/json", jsonResponse);
}

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
    server.on("/textQAA", HTTP_GET,  handleGetQuestion);



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