
#include "QuizGame.h"

int main() {
    int category;
    int mode;
    string filename;
    QuizGame game;

    cout << "���� ������ �����ϼ���: \n\n1. ������\n2. ĳ����\n3. ����\n\n����: ";
    while (!(cin >> category) || (category < 1 || category > 3)) {
        cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �߿��� �����ϼ���: ";
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
            cout << "�߸��� �Է��Դϴ�.";
            break;
    }

        game.clearScreen();

    if (!game.loadQuestionsFromFile(filename)) {
        cerr << "������ �ҷ����� ���߽��ϴ�." << endl;
        return 1;
    } 

    cout << "���� ��带 �����ϼ���: \n\n1. 30�� ���� ���� Ǯ��\n2. 5���� ����, ������ 4�� �ð� ����\n3. ������ ����, ���� �� ���ӿ���\n\n��� ����: ";

    while (!(cin >> mode) || (mode != 99 && (mode < 1 || mode > 3))){
        cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �߿��� �����ϼ���: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    game.startGame(mode);
    return 0;
}
