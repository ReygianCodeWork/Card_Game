#pragma once
#include <vector>
#include "types.hxx"


class QuizManager {
    private:
        std::vector<QuizQuestion> questions;
        size_t currentCardIndex;
        
    public:
        QuizManager();
        void loadMockQuestions();

        bool hasNextQuestion() const;
        QuizQuestion getCurrentQuestion() const;
        void advanceToNext();
        void reset();
        size_t getCurrentIndex() const;

};
