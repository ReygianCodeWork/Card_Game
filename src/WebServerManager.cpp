// src/WebServerManager.cpp
#include "WebServerManager.hxx"
#include <LittleFS.h>
#include <ArduinoJson.h>

WebServerManager::WebServerManager(QuizManager& quizManager) : server(80), quiz(quizManager) {}

void WebServerManager::begin() {
    server.on("/textQAA", HTTP_GET, std::bind(&WebServerManager::handleGetQuestion, this));
   // server.on("/textPress", HTTP_POST, std::bind(&WebServerManager::handlePostString, this));
    
    server.onNotFound([this]() {
        if (!handleFileRead(server.uri())) {
            server.send(404, "text/plain", "Theres something wrong with you!");
        }
    });
    server.begin();
}

void WebServerManager::handleClient() {
    server.handleClient();
}

void WebServerManager::handleGetQuestion() {
    if (!quiz.hasNextQuestion()) {
        quiz.reset();
        JsonDocument noNext;
        noNext["nonext"] = "NONEXT";
        noNext["count"] = quiz.getCurrentIndex();
        String response;
        serializeJson(noNext, response);
        server.send(200, "application/json", response);
        return;
    }

    QuizQuestion q = quiz.getCurrentQuestion();
    JsonDocument doc;
    doc["question"] = q.question;
    doc["a"] = q.choiceA;
    doc["b"] = q.choiceB;
    doc["c"] = q.choiceC;
    doc["d"] = q.choiceD;
    
    String jsonResponse;
    serializeJson(doc, jsonResponse);
    server.send(200, "application/json", jsonResponse);
}

void WebServerManager::handlePostString() {
    if (server.hasArg("plain") && server.arg("plain") == "press") {
        quiz.advanceToNext();
        server.send(200, "text/plain", "Action executed");
    } else {
        server.send(400, "text/plain", "Error: Invalid request body");
    }
}

bool WebServerManager::handleFileRead(String path) {
    if (path.endsWith("/")) path += "index.html";
    String contentType = getContentType(path);

    if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, "r");
        server.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}

String WebServerManager::getContentType(const String& path) {
    if (path.endsWith(".html")) return "text/html";
    if (path.endsWith(".css")) return "text/css";
    if (path.endsWith(".js")) return "application/javascript";
    if (path.endsWith(".ico")) return "image/x-icon";
    return "text/plain";
}
