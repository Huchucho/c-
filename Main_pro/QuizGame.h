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
    string asciiArt;  // 문제의 아스키 아트
    vector<string> answers;    // 정답 리스트

public:
    Question(const string& art, const string& ans);
    void displayQuestion() const;              // 문제 출력
    bool checkAnswer(const string& userAnswer) const;  // 정답 확인
};

class QuizGame {
private:
    vector<Question> questions; // 문제 리스트
    void shuffleQuestions(); // 문제를 무작위로 섞기 위한 함수
    void modeOne();  // 1번 모드: 30초 동안 문제 풀이
    void modeTwo();  // 2번 모드: 5개의 문제, 문제당 4초 시간 제한
    void modeThree(); // 3번 모드: 무제한 문제, 한 번 오답 시 게임오버
    void modetest(); // 테스트 모드 : 문제 이미지가 적절한지 확인하기
public:
    bool loadQuestionsFromFile(const string& filename); // 파일로부터 문제 로드
    void startGame(int mode); // 모드에 따라 게임 실행
    void clearScreen(); // 화면을 지우는 함수
};

#endif