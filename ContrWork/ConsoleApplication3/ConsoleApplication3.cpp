#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <exception>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Raspisaniye
{
private:
    int dennedeli;
    string vrema;
    string name_uc_d;
    int auditoria;
public:
    Raspisaniye(int d, string v, string n, int au) :dennedeli(d), vrema(v), name_uc_d(n), auditoria(au) {}

    void file()
    {

        setlocale(LC_ALL, "Russian");
        ofstream files("a.txt", ios::app);
        if (!files.is_open()) {
            cout << "Нет файла";
        }
        files << dennedeli << " ";
        files << "'" << vrema << "'" << " ";
        files << name_uc_d << " ";
        files << auditoria << " ";
        files << endl;
        files.close();
    }


    friend ostream& operator<<(ostream& so, Raspisaniye& r) {
        setlocale(LC_ALL, "Russian");
        so << r.dennedeli << r.vrema << r.name_uc_d << r.auditoria;
        return so;
    }

    friend istream& operator>>(istream& so, Raspisaniye& r) {
        setlocale(LC_ALL, "Russian");
        so >> r.dennedeli >> r.vrema >> r.name_uc_d >> r.auditoria;
        return so;
    }

    bool remove_line(const char* filename, size_t index)
    {
        vector<string> vec;
        ifstream file(filename);
        if (file.is_open())
        {
            string str;
            while (getline(file, str))
                vec.push_back(str);
            file.close();
            if (vec.size() < index)
                return false;
            vec.erase(vec.begin() + index);
            ofstream outfile(filename);
            if (outfile.is_open())
            {
                copy(vec.begin(), vec.end(),
                    ostream_iterator<string>(outfile, "\n"));
                outfile.close();
                return true;
            }
            return false;
        }
        return false;
    }
    void vivod()
    {
        string line;
        ifstream files("a.txt");
        if (files.is_open())
        {
            while (!files.eof())
            {
                getline(files, line);
                cout << line << endl;
            }
            files.close();
        }
    }
    int konk() {
        ifstream fin("a.txt");
        if (!fin.is_open()) cout << "Ошибка при открытии файла для чтения\n";
        else
        {
            cout << "Введите букву для поиска: ";
            char ch;
            string line;
            cin >> ch;
            while (fin.peek() != EOF) //ищем строку в файле, первый символ которой равен ch
            {
               while (fin.peek() == ch) {
                    getline(fin, line);
                    cout << line << endl;
                }
                fin.ignore(500, '\n'); // если первый символ не совпадает, то строка (макс. 500 символов) пропускается
            }
            fin.close();
        }

        system("pause");
        return 0;
    }
 };

int main()
{
    setlocale(LC_ALL, ".1251");
    int i = 0, n, a, m, c,j,k;
    cout << "1. Добавить запись в файл\n";
    cout << "2. Удалить запись из файла\n";
    cout << "3. Вывести полное расписание \n";
    cout << "4. вывести расписание за конкретный день\n";
    cout << "выбор: \n";
    cin >> a;
    Raspisaniye pa(1, "'13:21'", "Английский", 337);
    switch (a) {
    case 1:
        cout << "Введите количество внесений изменений в расписание = ";
        cin >> n;
        for (i = 0; i < n; i++) {
            cin >> pa;
            pa.file();
        }
        break;
    case 2:
        pa.vivod();
        cout << "Введите номер записи для удаления (начинается с 0): ";
        cin >> m;
        pa.remove_line("a.txt", m);
        pa.vivod();
        break;
    case 3:
        pa.vivod();
        break;
    case 4:
        pa.konk();
        break;
    default:
        cout << "Ошибка программирования\n";
        break;
    }
    system("pause");
    return 0;
};