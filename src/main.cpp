#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

const char* ssid = "ESP32_Card_Game";
const char* password = "Password123";

WebServer server(80);

// Helper function to serve files from LittleFS
bool handleFileRead(String path) {
    Serial.println("Requested file: " + path);
    
    // Default to index.html if the root "/" is requested
    if (path.endsWith("/")) {
        path += "index.html";
    }

    // Determine content-type based on file extension
    String contentType = "text/plain";
    if (path.endsWith(".html")) contentType = "text/html";
    else if (path.endsWith(".css"))  contentType = "text/css";
    else if (path.endsWith(".js"))   contentType = "application/javascript";
    else if (path.endsWith(".ico"))  contentType = "image/x-icon";

    // If file exists, open and send it over the network
    if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, "r");
        server.streamFile(file, contentType);
        file.close();
        return true;
    }
    
    return false; // File doesn't exist
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Initialize LittleFS
    if (!LittleFS.begin(true)) { // 'true' formats filesystem if it fails to mount
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully.");

    // Start Access Point
    WiFi.softAP(ssid, password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // API route example for your Javascript fetch action
    server.on("/api/draw", HTTP_GET, []() {
        server.send(200, "text/plain", "Ace of Spades!");
    });

    // Catch-all route to serve static files from LittleFS
    server.onNotFound([]() {
        if (!handleFileRead(server.uri())) {
            server.send(404, "text/plain", "FileNotFound");
        }
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
