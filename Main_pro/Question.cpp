#include "QuizGame.h"

Question::Question(const string& art, const string& ans) : asciiArt(art) {
    // ���� ���ڿ��� ',' �������� ������ ���� ���� ������ ���Ϳ� ����
    stringstream ss(ans);
    string token;
    while (getline(ss, token, ',')) {
        // �� ������ �յ� ���� ���� �� ����
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
        cerr << "�Է� ó�� �� ������ �߻��߽��ϴ�: " << e.what() << endl;
        return false;
    }
 
}