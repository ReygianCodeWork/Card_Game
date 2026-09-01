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
        "D. NOT NOW", 
    },
    {
        "The Brain of the computer", 
        "A. Tower A", 
        "B. CPU", 
        "C. Volatile Memory", 
        "D. HTTP",
    }
};

WebServer server(80);


// This will handle the question queueing acquisition
void handleGetQuestion() {
    if (counterCard >= QAA.size()) {
        counterCard = 0;
        JsonDocument noNext;

        noNext["nonext"] = "NONEXT";
        noNext["count"] = counterCard;

        String Response;
        serializeJson(noNext, Response);
        server.send(200, "application/json", Response);
        return;
    }
    JsonDocument doc;
    
    doc["question"] = QAA.at(counterCard).question;
    doc["a"] = QAA.at(counterCard).choiceA;
    doc["b"] = QAA.at(counterCard).choiceB;
    doc["c"] = QAA.at(counterCard).choiceC;
    doc["d"] = QAA.at(counterCard).choiceD;
    
    String jsonResponse;
    serializeJson(doc, jsonResponse);
    
    Serial.println(jsonResponse);
    
    server.send(200, "application/json", jsonResponse);

}

// Handle the press button in the website
void handlePostString() {
    if (server.hasArg("plain")) {
        String message = server.arg("plain"); // captures raw "plain/text"

        if(message == "press") {
            counterCard++;
            if (counterCard >= QAA.size()) {
                counterCard = 0;
            }

            server.send(200, "text/plain", "Action is executed");
        }
        else {
            server.send(400, "text/plain", "Error: Unknown command received");
        }
    } 
    else {
        server.send(400, "text/plain", "Error: Empty body received");
    }
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

    // The next server.on will receive a POST request and store it in 
    // a variable.
    server.on("/textPress", HTTP_POST, handlePostString);

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