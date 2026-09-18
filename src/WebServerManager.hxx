#pragma once

#include <WebServer.h>
#include "QuizManager.hxx"


class WebServerManager {
    private:
        WebServer server;
        QuizManager &quiz;

        void handleGetQuestion();
        void handlePostString();
        bool handleFileRead(String path);
        String getContentType(const String &path);

    public:
        WebServerManager(QuizManager &quizManager);
        void begin();
        void handleClient();
};
