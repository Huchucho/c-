#include "QuizGame.h"

Question::Question(const string& art, const string& ans) : asciiArt(art) {
    // 정답 문자열을 ',' 기준으로 나누어 여러 개의 정답을 벡터에 저장
    stringstream ss(ans);
    string token;
    while (getline(ss, token, ',')) {
        // 각 정답의 앞뒤 공백 제거 후 저장
        token.erase(token.begin(), find_if(token.begin(), token.end(), [](unsigned char ch) { return !isspace(ch); }));
        token.erase(find_if(token.rbegin(), token.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), token.end());
        answers.push_back(token);
    }
}

void Question::displayQuestion() const {
    cout << asciiArt << endl;
}

bool Question::checkAnswer(const string& userAnswer) const {
    try {
        locale loc("");
        string userAnswerProcessed = userAnswer;

        for (const auto& correctAnswer : answers) {
            string correctAnswerProcessed = correctAnswer;
            correctAnswerProcessed.erase(remove_if(correctAnswerProcessed.begin(), correctAnswerProcessed.end(), [](unsigned char ch) { return isspace(ch); }), correctAnswerProcessed.end());
            for (auto& ch : correctAnswerProcessed) {
                ch = tolower(ch, loc);
            }

            if (userAnswerProcessed == correctAnswerProcessed) {
                return true;
            }
        }

        return false;
    }
    catch (const exception& e) {
        cerr << "입력 처리 중 오류가 발생했습니다: " << e.what() << endl;
        return false;
    }
 
}