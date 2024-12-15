#include "QuizGame.h"

#include <locale>
#include <codecvt>

bool QuizGame::loadQuestionsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return false;
    }

    string line, asciiArt, answer;
    while (getline(file, line)) {
        if (line == "===") {  // ������
            getline(file, answer);  // ���� �б�
            questions.emplace_back(asciiArt, answer);
            asciiArt.clear();
        }
        else {
            asciiArt += line + "\n";  // �ƽ�Ű ��Ʈ ����
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
        cout << "�߸��� ��� �����Դϴ�." << endl;
        break;
    }
}

void QuizGame::modeOne() {
    shuffleQuestions();
    cout << "30�� ���� �ִ��� ���� ������ Ǯ�����!" << endl;
    int score = 0;
    auto startTime = chrono::steady_clock::now();

    for (const auto& question : questions) {
        auto currentTime = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(currentTime - startTime).count() >= 30) {
            break;
        }

        clearScreen(); 
        question.displayQuestion();
        cout << "������ �Է��ϼ���: ";
        string userAnswer;
        cin >> userAnswer;

        if (question.checkAnswer(userAnswer)) {
            cout << "�����Դϴ�!" << endl;
            score++;
        }
        else {
            cout << "�����Դϴ�." << endl;
        }
    }

    cout << "30�� ������ ����: " << score << " / " << questions.size() << endl;

}

void QuizGame::modeTwo() {
    shuffleQuestions();
    cout << "������ 4���� �ð��� �־����ϴ�. 5���� ������ Ǯ�����!" << endl;
    int score = 0;
    int questionCount = 0;

    for (const auto& question : questions) {
        if (questionCount >= 5) {
            break;
        }

        clearScreen(); 
        question.displayQuestion();
        cout << "������ �Է��ϼ���: ";
        string userAnswer;

        auto startTime = chrono::steady_clock::now();
        while (true) {
            if (cin.rdbuf()->in_avail()) {
                cin >> userAnswer;
                break;
            }

            auto currentTime = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::seconds>(currentTime - startTime).count() >= 4) {
                cout << "\n�ð� �ʰ�! ���� ó���˴ϴ�." << endl;
                userAnswer = "";
                break;
            }
        }

        if (question.checkAnswer(userAnswer)) {
            cout << "�����Դϴ�!" << endl;
            score++;
        }
        else {
            cout << "�����Դϴ�." << endl;
        }

        questionCount++;
    }

    cout << "5���� �� ����: " << score << " / 5" << endl;
}

void QuizGame::modeThree() {
    shuffleQuestions();
    cout << "������ ����, �� ���̶� Ʋ���� ���� ����!" << endl;

    int score = 0;
    for (const auto& question : questions) {
        clearScreen(); 
        question.displayQuestion();
        cout << "������ �Է��ϼ���: ";
        string userAnswer;
        cin >> userAnswer;

        if (!question.checkAnswer(userAnswer)) {
            cout << "�����Դϴ�. ���� ����!" << endl;
            cout << "�� " << score << "���� ������ ������ϴ�." << endl;
            return;
        }

        cout << "�����Դϴ�!" << endl;
        score++;
    }
    cout << "��� ������ ������ϴ�! �����մϴ�!" << endl;
}

void QuizGame::modetest() {
    clearScreen();
    cout << "��� ������ ����մϴ�:\n";
    int count = 1;
    for (const auto& question : questions) {
        question.displayQuestion();
        cout << count << endl;
        count++;
    }
 
}