#include <iostream>
#include <string>
#include <fstream>




using namespace std;

void delOneLine(string& line)
{
    if (line.length() > 1)
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '/' && line[i + 1] == '/')
            {
                line.erase(i);
            }
        }
    }
}

void delMultiLine(string& line, int& mlComentFlag)
{
    if (line.length() > 1)
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != '*' && line[i + 1] != '/' && mlComentFlag == 1)
            {
                line.replace(i, 1, 1, ' ');
            }
            if (line[i] == '/' && line[i + 1] == '*' && mlComentFlag == 0)
            {
                line.erase(i);
                mlComentFlag = 1;
            }
            if (line[i] == '*' && line[i + 1] == '/' && mlComentFlag == 1)
            {
                line.erase(0, i + 2);
                mlComentFlag = 0;
            }
        }
    }
}

void IO()
{
    string path;
    string input;
    char mode = 0;
    cout << "Считывание из файла - 1, Ввод из клавиатуры - 0 > ";
    cin >> mode;
    
    switch (mode)
    {
    case '1':
        path = "Comment.txt";
        break;
    case '0':
        cout << "Введите код с++ по строкам(endOfInput - завершение ввода) > " << endl;
        cin.ignore(32767, '\n');
        ofstream enter;
        enter.open("Comment1.txt");
        char endOfInput = '0';
        while (endOfInput == '0')
        {
            getline(cin, input);
            if (input == "endOfInput")
            {
                input.erase(0);
                endOfInput = '1';
            }
            input += '\n';
            enter << input;
        }
        enter.close();
        path = "Comment1.txt";
        break;
    }

    


    ifstream fin;
    fin.open(path);
    if (!fin.is_open())
    {
        cout << "ошибка открытия файла" << endl;
    }
    else
    {
        cout << "Файл открыт" << endl;
        string line;
        int mlComentFlag = 0;
        while (!fin.eof())
        {
            getline(fin, line);

            delOneLine(line);

            delMultiLine(line, mlComentFlag);

            line += '\n';
            cout << line;
            line = ' ';
        }
    }
    fin.close();
}

int main()
{
    setlocale(0, "");
    char uslovie = 0;
    cout << "Начать выполнение програмы - y Выйти - n > ";
    cin >> uslovie;
    cout << endl;
    while (uslovie != 'n')
    {
        IO();
        cout << endl;
        cout << "повтоорить выполнение програмы y - да n - нет  > ";
        cin >> uslovie;
        cout << endl;
    }
}