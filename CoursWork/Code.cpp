#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <random>

using namespace std;

enum Color
{
    BLACK = 0,
    DARKBLUE = FOREGROUND_BLUE,
    DARKGREEN = FOREGROUND_GREEN,
    DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKRED = FOREGROUND_RED,
    DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
    DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GRAY = FOREGROUND_INTENSITY,
    BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
    MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

ostream& operator << (ostream& os, const Color& att)
{
    if (&os == &cout)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(att));
    return os;
}


class Player
{
private:
    string name;

public:
    void SetNickName(string _name) { this->name = _name; }
    string GetNickName() { return name; }


};

class Data
{
public:
    vector<string> Questions;
    vector<string> Answers;
    vector<string> CorrectAnswer;
};
Data EasyQuestion;
Data MediumQuestion;
Data HardQuestion;
vector<int>choises;
int tryes = 0;



class Viktorina :Player
{
private:
    int score = 0;
    Player player;

public:


    bool ValidateChoise(int _choise)
    {
        tryes++;
        choises.push_back(_choise);


        if (tryes == 2)
        {
            if (choises[0] == choises[1])
            {
                cout << RED << "�� ��� ������� ��� ������, ������� �����!" << WHITE << endl;
                choises.pop_back();
                tryes--;
                return false;
            }
        }

        if (tryes == 3)
        {
            if (choises[0] == choises[1] || choises[0] == choises[2] || choises[1] == choises[2])
            {
                cout << RED << "�� ��� ������� ��� ������, ������� �����!" << WHITE << endl;
                choises.pop_back();
                tryes--;
                return false;
            }
        }
        if (tryes == 4)
        {
            if (choises[0] == choises[1] || choises[0] == choises[2] || choises[1] == choises[2] || choises[0] == choises[3] || choises[1] == choises[3] || choises[2] == choises[3])
            {
                cout << RED << "�� ��� ������� ��� ������, ������� �����!" << WHITE << endl;
                choises.pop_back();
                tryes--;
                return false;
            }
        }
        return true;
    }


    int ShowResult()
    {
        cout << BLUE << player.GetNickName() << "," << MAGENTA << "���� ����: " << RED << score << WHITE << endl;
        return 0;

    };


    int StartWindow()
    {
        int variant;
        Player SetName;
        string NickName;

        cout << GREEN << "1 - ������ ��������" << WHITE << endl;
        cout << RED << "2 - ������� ����" << WHITE << endl;
        cin >> variant;
        system("cls");

        if (variant == 1)
        {
            cout << BLUE << "������ ��� ��" << WHITE << endl;
            cin >> NickName;
            SetName.SetNickName(NickName);
            player = SetName;
            system("cls");
            QuestionsWindow();
        }
        else
        {
            system("cls");
            cout << WHITE << "�� � ������ �����! ��� �� �� ������ �����������\n 1-����������� �����\n 2-�������" << WHITE << endl;
            cin >> variant;
            if (variant == 1)
            {
                system("cls");
                StartWindow();
            }
            else
            {
                system("cls");
                cout << RED << "�� ���������!" << WHITE << endl;
                return 0;
            }
            return 0;
        }

    }



    void LoadData(string name, int dif)
    {
        ifstream File(name);

        string readLine;
        int i = 0;

        if (!File.is_open())
        {
            cout << RED << "������� �������� �����" << WHITE << endl;
        }
        else
        {
            while (getline(File, readLine))
            {
                if (i % 3 == 0)
                {
                    if (dif == 0)
                    {
                        EasyQuestion.Questions.push_back(readLine);
                    }
                    if (dif == 1)
                    {
                        MediumQuestion.Questions.push_back(readLine);
                    }
                    if (dif == 2)
                    {
                        HardQuestion.Questions.push_back(readLine);
                    }
                }
                if (i % 3 == 1)
                {
                    if (dif == 0)
                    {
                        EasyQuestion.Answers.push_back(readLine);
                    }
                    if (dif == 1)
                    {
                        MediumQuestion.Answers.push_back(readLine);
                    }
                    if (dif == 2)
                    {
                        HardQuestion.Answers.push_back(readLine);
                    }
                }
                if (i % 3 == 2)
                {
                    if (dif == 0)
                    {
                        EasyQuestion.CorrectAnswer.push_back(readLine);
                    }
                    if (dif == 1)
                    {
                        MediumQuestion.CorrectAnswer.push_back(readLine);
                    }
                    if (dif == 2)
                    {
                        HardQuestion.CorrectAnswer.push_back(readLine);
                    }
                }
                i++;
            }
        }

        File.close();
    }
    bool result;



    void IsAnswerCorrect(int answer, string correctAnswer)
    {

        int correctAnswerInt = stoi(correctAnswer);
        result = answer == correctAnswerInt;
        if (result)
        {
            score++;
            cout << GREEN << "�� ������� ���������, ���� ����: " << WHITE;
        }
        else
        {
            cout << RED << "�� ������� �� ���������, ���� ����: " << WHITE;
        }
    }


    void QuestionsWindow()
    {


        int choise, choise1 = 1, choise2;
        string str, line;


        for (int i = 0; i < 4; i++)
        {

            cout << GREEN << "\t\t\t      ���в�� ���� � ��в��Ҳ�\n" << WHITE << endl;
            cout << GREEN << "1-����� �������\t" << "\t2-������� �������" << "\t3-����� �������\t" << "\t4-�������� ³�������" << WHITE << endl;
            cin >> choise;
            system("cls");
            if (ValidateChoise(choise) == false)
            {

                QuestionsWindow();
            }
            int count = 0;
            int index = 0;

            while (true)
            {
                count++;
                if (choise == 1)
                {
                    cout << BLUE << EasyQuestion.Questions[index] << "\t" << WHITE << endl;
                    cout << BLUE << EasyQuestion.Answers[index] << WHITE << endl;
                    cin >> choise2;
                    IsAnswerCorrect(choise2, EasyQuestion.CorrectAnswer[index]);
                    cout << RED << score << WHITE << endl;
                    if (count == EasyQuestion.Questions.size())
                    {
                        cout << WHITE << "�� �������� ���� � ������� ���������! ������ ENTER ��� ������� � ���� �������!" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    }
                }
                if (choise == 2)
                {
                    cout << BLUE << MediumQuestion.Questions[index] << "\t" << WHITE << endl;
                    cout << BLUE << MediumQuestion.Answers[index] << WHITE << endl;
                    cin >> choise2;
                    IsAnswerCorrect(choise2, MediumQuestion.CorrectAnswer[index]);
                    if (result == true)
                    {
                        score++;
                    }
                    cout << RED << score << WHITE << endl;


                    if (count == MediumQuestion.Questions.size())
                    {
                        cout << WHITE << "�� �������� ���� � �������� ���������! ������ ENTER ��� ������� � ���� �������!" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    }
                }
                if (choise == 3)
                {
                    cout << BLUE << HardQuestion.Questions[index] << "\t" << WHITE << endl;
                    cout << BLUE << HardQuestion.Answers[index] << WHITE << endl;
                    cin >> choise2;
                    IsAnswerCorrect(choise2, HardQuestion.CorrectAnswer[index]);
                    if (result == true)
                    {
                        score += 2;
                    }
                    cout << RED << score << WHITE << endl;
                    if (count == HardQuestion.Questions.size())
                    {
                        cout << WHITE << "�� �������� ���� � ������� ���������! ������ ENTER ��� ������� � ���� �������!" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    }
                }

                if (choise == 4)
                {
                    system("cls");
                    cout << WHITE << "����� ��� �� ������ � ³������!" << endl;
                    ShowResult();
                    system("pause");
                    exit(0);
                }
                index++;
                system("pause");
                system("cls");



            }
        }
    }


};

int main()

{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Viktorina Start;
    Player Name;

    Start.LoadData("MyFile.txt", 0);
    Start.LoadData("myfile2.txt", 1);
    Start.LoadData("myfile3.txt", 2);

    Start.StartWindow();

    system("pause");
    return 0;
}