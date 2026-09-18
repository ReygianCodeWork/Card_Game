#include "QuizManager.hxx"

QuizManager::QuizManager() : currentCardIndex(0) {}

void QuizManager::loadMockQuestions() {
        questions = {
        {"What is the worlds tallest ice mountain", "A. Mt. Fuji", "B. Tommorow", "C. NExt", "D. NOT NOW"},
        {"The Brain of the computer", "A. Tower A", "B. CPU", "C. Volatile Memory", "D. HTTP"}
    };
}

bool QuizManager::hasNextQuestion() const {
    return currentCardIndex < questions.size();
}

QuizQuestion QuizManager::getCurrentQuestion() const {
    if (currentCardIndex < questions.size()) {
        return questions.at(currentCardIndex);
    }

    return QuizQuestion{"No more Questions", "", "", "", ""};
}

void QuizManager::advanceToNext() {
    currentCardIndex++;
    if (currentCardIndex >= questions.size()) {
        this->reset();
    }
}

void QuizManager::reset() {
    currentCardIndex = 0;
}

size_t QuizManager::getCurrentIndex() const {
    return currentCardIndex;
}



