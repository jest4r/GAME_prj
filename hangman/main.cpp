#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
string chooseWord();
string displayWord(string s, string w, int k);
void displayMan(char m[10][10], int k);
void render(string s, int &n);
int main()
{
    string word = chooseWord();
    int n = word.length();
    render(word, n);
}
string chooseWord(){
    ifstream word("word.txt");
    string s;
    while (word >> s) {
        return s;
    }
}
string displayWord(string s, string w, char a){
    string s1 = s;
    int l = s1.length();
    for (int i = 0; i < l; i++){
        if (w[i] == a) s1[i] = a;
    }
    return s1;
}
void displayMan(char m[10][10], int k){
    for (int i = 0; i < 4; i++) m[0][i] = '-';
    switch (k) {
        case 1:
            m[1][3] = '|';
            break;
        case 2:
            m[2][3] = 'O';
            break;
        case 3:
            m[3][3] = '|';
            break;
        case 4:
            m[4][2] = '/';
            break;
        case 5:
            m[4][4] = '\\';
            break;
        case 6:
            m[4][3] = '|';
            break;
        case 7:
            m[5][2] = '/';
            break;
        case 8:
            m[5][4] = '\\';
            break;
    }
    for (int i = 0; i <= 9; i++){
        for (int j = 0; j<= 9; j++) cout << m[i][j];
        cout << endl;
    }
}
void render(string s, int &n){
    string s1 = s.substr(0);
    char guess;
    for (int i = 0; i < n; i++){
        s1[i] = '_';
    }
    int k = 0;
    cout << "Tu can tim gom co " << n << " ky tu: " << s1 << endl;
    do{
        cout << "Neu tim dc tu chia khoa vui long bam 1" << endl;
        cout << "Xin moi chon chu: ";
        int check = 0;
        cin >> guess;
        if (guess == '1') {
            cout << "Vui long go tu chia khoa: ";
            cin >> s1;
            if (s1 == s) {
                cout << "VCL LUON THANG LUON" << endl;
                cout << s;
                break;
            } else
            {
                cout << "SAI CMNR THUA LUON" << endl;
                break;
            }
        } else {
        for (int i = 0; i < n; i++)
            if (s[i] == guess)
            {
                    check++;
            }
        if (check > 0)
        {
            cout << "Ban da doan dung" << endl;
            while (check-- >0)
            {
                s1 = displayWord(s1, s, guess);
            }
        cout << s1 << endl;
        }
        else
        {
            cout << "Ban da doan sai" << endl;
            k++;
            char m[10][10];
            displayMan(m, k);
        }
        if (k == 8) {
            cout << "BAN THUA CMNR" << endl;
            break;
        }
        if (s == s1) {
            cout << "XIN CHUC CMN MUNG BAN NHE" << endl;
            break;
        }
    }
    }
    while (k < 8 || s != s1);
}
