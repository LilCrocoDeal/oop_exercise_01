/*М8О-201Б-20 Тимофеев Михаил Юрьевич ООП ЛР№1*/
#include "oop_exercise_01.h"

using namespace std;

class BitString {
    unsigned long long pt1, pt2;
public:
    BitString() : pt1(0), pt2(0) {}
    void init(unsigned long long a, unsigned long long b) { pt1 = a, pt2 = b; }

    void globa() { // вывод числа в консоль
        int n = 0;
        if ((pt1 << 0 >> 60) == 0) {
            while (((pt1 << n >> 60) == 0) && (n != 64)) {
                cout << "0";
                n += 4;
            }
        }
        n = 0;

        if (pt1 != 0) { cout << hex << uppercase << pt1; }

        if ((pt2 << 0 >> 60) == 0) {
            while (((pt2 << n >> 60) == 0) && (n != 64)) {
                cout << "0";
                n += 4;
            }
        }

        if (pt2 != 0) { cout << hex << uppercase << pt2 << endl; }
        cout << endl;
    }
    BitString operator &(const BitString& t) { // операция and
        BitString potna;
        potna.pt1 = pt1 & t.pt1;
        potna.pt2 = pt2 & t.pt2;
        return potna;
    }
    BitString operator |(const BitString& t) { // операция or
        BitString potna;
        potna.pt1 = pt1 | t.pt1;
        potna.pt2 = pt2 | t.pt2;
        return potna;
    }
    BitString operator ^(const BitString& t) {  // операци xor
        BitString potna;
        potna.pt1 = pt1 ^ t.pt1;
        potna.pt2 = pt2 ^ t.pt2;
        return potna;
    }
    BitString operator ~() {    // операция not
        BitString potna;
        potna.pt1 = ~pt1;
        potna.pt2 = ~pt2;
        return potna;
    }
    int BitCounter() {  // считает единицы числа
        int a, b;
        int count = 0;
        for (int i = 0;i < 16;i++) {
            a = pt1 << (60 - i * 4) >> 60;
            while (a != 0) {
                if (a % 2 == 1) { count++; }
                a /= 2;
            }
        }
        for (int i = 0;i < 16;i++) {
            b = pt2 << (60 - i * 4) >> 60;
            while (b != 0) {
                if (b % 2 == 1) { count++; }
                b /= 2;
            }
        }
        return count;
    }
    BitString operator <<(const int& k) {    //сдвиг влево
        BitString boba;
        if (k < 64) {
            unsigned long long g = pt2 >> (64 - k);
            boba.pt2 = pt2 << k;
            boba.pt1 = pt1 << k;
            boba.pt1 = boba.pt1 | g;
        }
        else if (k > 64) {
            boba.pt1 = pt2 << (k - 64);
            boba.pt2 = 0x0000000000000000;
        }
        else {
            boba.pt1 = pt2;
            boba.pt2 = 0x0000000000000000;
        }
        return boba;
    }
    BitString operator >>(const int& k) {    //сдвиг вправо
        BitString boba;
        if (k < 64) {
            unsigned long long g = pt1 << (64 - k);
            boba.pt1 = pt1 >> k;
            boba.pt2 = pt2 >> k;
            boba.pt2 = boba.pt2 | g;
        }
        else if (k > 64) {
            boba.pt1 = 0x0000000000000000;
            boba.pt2 = pt1 >> (k - 64);
        }
        else {
            boba.pt1 = 0x0000000000000000;
            boba.pt2 = pt1;
        }
        return boba;
    }

    string worker() {   // переводит число в строку из единиц и нулей для нахождения подстроки
        int n = 0;
        vector<int> v;
        if ((pt1 << 0 >> 60) == 0) {
            while (((pt1 << n >> 60) == 0) && (n != 64)) {
                v.push_back(0);
                v.push_back(0);
                v.push_back(0);
                v.push_back(0);
                n += 4;
            }
        }

        if (pt1 != 0) {
            while (n != 64) {
                int ff = pt1 << n >> 60;
                vector<int> jj(4);
                for (int j = 3;j >= 0;j--) {
                    int f = ff % 2;
                    jj[j] = f;
                    ff /= 2;
                }
                for (int i = 0;i < 4;i++) {
                    v.push_back(jj[i]);
                }
                n += 4;
            }
        }
        n = 0;

        if ((pt2 << 0 >> 60) == 0) {
            while (((pt2 << n >> 60) == 0) && (n != 64)) {
                v.push_back(0);
                v.push_back(0);
                v.push_back(0);
                v.push_back(0);
                n += 4;
            }
        }

        if (pt2 != 0) {
            while (n != 64) {
                int ff = pt2 << n >> 60;
                vector<int> jj(4);
                for (int j = 3;j >= 0;j--) {
                    int f = ff % 2;
                    jj[j] = f;
                    ff /= 2;
                }
                for (int i = 0;i < 4;i++) {
                    v.push_back(jj[i]);
                }
                n += 4;
            }
        }
        stringstream ss;
        for (int i = 0; i < v.size(); ++i) {
            ss << v[i];
        }
        string s = ss.str();
        return s;
    }
    void BitSearch(string s) {    // нахождение подстроки
        string ss = worker();
        int position = ss.find(s, 0);
        if (position != string::npos) {
            cout << "Введенная строка присутствует в данной битовой строке" << endl;
        }
        else {
            cout << "Введенная строка отсутствует в данной битовой строке" << endl;
        }
    }
};

void BitCompare(BitString a, BitString b) {    // сравниваем по единичкам
    if (a.BitCounter() > b.BitCounter()) { cout << "В первом числе больше единиц" << endl; }
    else if (a.BitCounter() < b.BitCounter()) { cout << "Во втором числе больше единиц" << endl; }
    else { cout << "Числа равны по количеству единиц" << endl; }
}

int main()
{
    int f = 1, menu;
    setlocale(LC_ALL, "Russian");
    unsigned long long a, b;
    cout << "Введите 128-битовую строку в 16ричной СИ:" << endl;
    string lol, s, t;
    cin >> lol;
    s.insert(0, lol, 0, 16);
    t.insert(0, lol, 16, 16);
    stringstream(s) >> hex >> a;
    stringstream(t) >> hex >> b;
    BitString krab;
    krab.init(a, b);
    while (f) {
        cout << "1.  Вывести изначальную строку" << endl;
        cout << "2.  Операция and" << endl;
        cout << "3.  Операция or" << endl;
        cout << "4.  Операция xor" << endl;
        cout << "5.  Операция not" << endl;
        cout << "6.  Операция сдвиг влево" << endl;
        cout << "7.  Операция сдвиг вправо" << endl;
        cout << "8.  Операция вычисления количества единичных битов" << endl;
        cout << "9.  Операция сравнения по количеству единичных битов" << endl;
        cout << "10. Операция проверки включения" << endl;
        cout << "11. Выход" << endl;
        cin >> menu;
        switch (menu) {
        case 1: {
            krab.globa();
            break;
        }
        case 2: {
            cout << "Введите еще одну 128-битовую строку в 16ричной СИ для операции and:" << endl;
            unsigned long long c, d;
            string l, x, standart;
            cin >> standart;
            l.insert(0, standart, 0, 16);
            x.insert(0, standart, 16, 16);
            stringstream(l) >> hex >> c;
            stringstream(x) >> hex >> d;
            BitString grob;
            grob.init(c, d);
            BitString end = krab & grob;
            end.globa();
            break;
        }
        case 3: {
            cout << "Введите еще одну 128-битовую строку в 16ричной СИ для операции or:" << endl;
            unsigned long long c, d;
            string l, x, standart;
            cin >> standart;
            l.insert(0, standart, 0, 16);
            x.insert(0, standart, 16, 16);
            stringstream(l) >> hex >> c;
            stringstream(x) >> hex >> d;
            BitString grob;
            grob.init(c, d);
            BitString end = krab | grob;
            end.globa();
            break;
        }
        case 4: {
            cout << "Введите еще одну 128-битовую строку в 16ричной СИ для операции xor:" << endl;
            unsigned long long c, d;
            string l, x, standart;
            cin >> standart;
            l.insert(0, standart, 0, 16);
            x.insert(0, standart, 16, 16);
            stringstream(l) >> hex >> c;
            stringstream(x) >> hex >> d;
            BitString grob;
            grob.init(c, d);
            BitString end = krab ^ grob;
            end.globa();
            break;
        }
        case 5: {
            BitString kkk = ~krab;
            kkk.globa();
            break;
        }
        case 6: {
            cout << "Введите количество битов, на которое нужно сдвинуть строку влево:" << endl;
            int rust;
            cin >> rust;
            BitString end = krab << rust;
            end.globa();
            break;
        }
        case 7: {
            cout << "Введите количество битов, на которое нужно сдвинуть строку вправо:" << endl;
            int rust;
            cin >> rust;
            BitString end = krab >> rust;
            end.globa();
            break;
        }
        case 8: {
            int dd = krab.BitCounter();
            cout << "Количество едничных битов в строке: " << dd << endl;
            cout << endl;
            break;
        }
        case 9: {
            cout << "Введите еще одну 128-битовую строку в 16ричной СИ для операции сравнения по количеству единичных битов:" << endl;
            unsigned long long c, d;
            string l, x, standart;
            cin >> standart;
            l.insert(0, standart, 0, 16);
            x.insert(0, standart, 16, 16);
            stringstream(l) >> hex >> c;
            stringstream(x) >> hex >> d;
            BitString grob;
            grob.init(c, d);
            BitCompare(krab, grob);
            cout << endl;
            break;
        }
        case 10: {
            cout << "Введите строку из единиц и нулей (меньше 128) для проверки включения:" << endl;
            string fruit;
            cin >> fruit;
            krab.BitSearch(fruit);
            cout << endl;
            break;
        }
        case 11: {
            f = 0;
            break;
        }
        default: {
            cout << "Неправильная команда" << endl;
            break;
        }
        }

    }

    return 0;
}
