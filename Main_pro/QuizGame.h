#ifndef QUIZGAME_H
#define QUIZGAME_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <random>    
#include <algorithm>  
#include <chrono>
#include <thread>
#include <limits>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
#include <stdexcept>


using namespace std;

class Question {
private:
    string asciiArt;  // ������ �ƽ�Ű ��Ʈ
    vector<string> answers;    // ���� ����Ʈ

public:
    Question(const string& art, const string& ans);
    void displayQuestion() const;              // ���� ���
    bool checkAnswer(const string& userAnswer) const;  // ���� Ȯ��
};

class QuizGame {
private:
    vector<Question> questions; // ���� ����Ʈ
    void shuffleQuestions(); // ������ �������� ���� ���� �Լ�
    void modeOne();  // 1�� ���: 30�� ���� ���� Ǯ��
    void modeTwo();  // 2�� ���: 5���� ����, ������ 4�� �ð� ����
    void modeThree(); // 3�� ���: ������ ����, �� �� ���� �� ���ӿ���
    void modetest(); // �׽�Ʈ ��� : ���� �̹����� �������� Ȯ���ϱ�
public:
    bool loadQuestionsFromFile(const string& filename); // ���Ϸκ��� ���� �ε�
    void startGame(int mode); // ��忡 ���� ���� ����
    void clearScreen(); // ȭ���� ����� �Լ�
};

#endif