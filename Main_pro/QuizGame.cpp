#include "QuizGame.h"

#include <locale>
#include <codecvt>

bool QuizGame::loadQuestionsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return false;
    }

    string line, asciiArt, answer;
    while (getline(file, line)) {
        if (line == "===") {  // 구분자
            getline(file, answer);  // 정답 읽기
            questions.emplace_back(asciiArt, answer);
            asciiArt.clear();
        }
        else {
            asciiArt += line + "\n";  // 아스키 아트 구성
        }
    }
    file.close();
    return true;
}

void QuizGame::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void QuizGame::shuffleQuestions() {
    random_device rd;
    mt19937 g(rd());
    shuffle(questions.begin(), questions.end(), g);
}

void QuizGame::startGame(int mode) {
    switch (mode) {
    case 1:
        modeOne();
        break;
    case 2:
        modeTwo();
        break;
    case 3:
        modeThree();
        break;
    case 99 :
        modetest();
        break;
    default:
        cout << "잘못된 모드 선택입니다." << endl;
        break;
    }
}

void QuizGame::modeOne() {
    shuffleQuestions();
    cout << "30초 동안 최대한 많은 문제를 풀어보세요!" << endl;
    int score = 0;
    auto startTime = chrono::steady_clock::now();

    for (const auto& question : questions) {
        auto currentTime = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(currentTime - startTime).count() >= 30) {
            break;
        }

        clearScreen(); 
        question.displayQuestion();
        cout << "정답을 입력하세요: ";
        string userAnswer;
        cin >> userAnswer;

        if (question.checkAnswer(userAnswer)) {
            cout << "정답입니다!" << endl;
            score++;
        }
        else {
            cout << "오답입니다." << endl;
        }
    }

    cout << "30초 동안의 점수: " << score << " / " << questions.size() << endl;

}

void QuizGame::modeTwo() {
    shuffleQuestions();
    cout << "문제당 4초의 시간이 주어집니다. 5개의 문제를 풀어보세요!" << endl;
    int score = 0;
    int questionCount = 0;

    for (const auto& question : questions) {
        if (questionCount >= 5) {
            break;
        }

        clearScreen(); 
        question.displayQuestion();
        cout << "정답을 입력하세요: ";
        string userAnswer;

        auto startTime = chrono::steady_clock::now();
        while (true) {
            if (cin.rdbuf()->in_avail()) {
                cin >> userAnswer;
                break;
            }

            auto currentTime = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::seconds>(currentTime - startTime).count() >= 4) {
                cout << "\n시간 초과! 오답 처리됩니다." << endl;
                userAnswer = "";
                break;
            }
        }

        if (question.checkAnswer(userAnswer)) {
            cout << "정답입니다!" << endl;
            score++;
        }
        else {
            cout << "오답입니다." << endl;
        }

        questionCount++;
    }

    cout << "5문제 중 점수: " << score << " / 5" << endl;
}

void QuizGame::modeThree() {
    shuffleQuestions();
    cout << "무제한 문제, 한 번이라도 틀리면 게임 오버!" << endl;

    int score = 0;
    for (const auto& question : questions) {
        clearScreen(); 
        question.displayQuestion();
        cout << "정답을 입력하세요: ";
        string userAnswer;
        cin >> userAnswer;

        if (!question.checkAnswer(userAnswer)) {
            cout << "오답입니다. 게임 오버!" << endl;
            cout << "총 " << score << "개의 문제를 맞췄습니다." << endl;
            return;
        }

        cout << "정답입니다!" << endl;
        score++;
    }
    cout << "모든 문제를 맞췄습니다! 축하합니다!" << endl;
}

void QuizGame::modetest() {
    clearScreen();
    cout << "모든 문제를 출력합니다:\n";
    int count = 1;
    for (const auto& question : questions) {
        question.displayQuestion();
        cout << count << endl;
        count++;
    }
 
}