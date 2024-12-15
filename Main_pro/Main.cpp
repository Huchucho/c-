
#include "QuizGame.h"

int main() {
    int category;
    int mode;
    string filename;
    QuizGame game;

    cout << "게임 종류를 선택하세요: \n\n1. 연예인\n2. 캐릭터\n3. 동물\n\n선택: ";
    while (!(cin >> category) || (category < 1 || category > 3)) {
        cout << "잘못된 입력입니다. 1, 2, 3 중에서 선택하세요: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (category)
    {
        case 1: 
            filename = "Star.txt";
            break;
        case 2:
            filename = "Char.txt";
            break;
        case 3: 
            filename = "Animal.txt";
            break;
        default:
            cout << "잘못된 입력입니다.";
            break;
    }

        game.clearScreen();

    if (!game.loadQuestionsFromFile(filename)) {
        cerr << "문제를 불러오지 못했습니다." << endl;
        return 1;
    } 

    cout << "게임 모드를 선택하세요: \n\n1. 30초 동안 문제 풀이\n2. 5개의 문제, 문제당 4초 시간 제한\n3. 무제한 문제, 오답 시 게임오버\n\n모드 선택: ";

    while (!(cin >> mode) || (mode != 99 && (mode < 1 || mode > 3))){
        cout << "잘못된 입력입니다. 1, 2, 3 중에서 선택하세요: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    game.startGame(mode);
    return 0;
}
