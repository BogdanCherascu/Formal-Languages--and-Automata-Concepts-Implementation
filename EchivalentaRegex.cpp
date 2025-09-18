//Verifi cați dacă două expresii regulate sunt echivalente (acceptă același limbaj).


#include <iostream>
#include <regex>
#include <vector>
#include <set>
#include <string>

using namespace std;

const vector<char> alfabet = {'a', 'b'};

void genereaza_stringuri(vector<string>& rezultate, string curent, int max_len) {
    if (curent.length() > max_len) return;
    rezultate.push_back(curent);
    for (char c : alfabet) {
        genereaza_stringuri(rezultate, curent + c, max_len);
    }
}

void compara_regexuri(const string& regex1_str, const string& regex2_str, int max_len) {
    regex regex1(regex1_str);
    regex regex2(regex2_str);

    vector<string> toate_cuvintele;
    genereaza_stringuri(toate_cuvintele, "", max_len);

    set<string> acceptat_de_1, acceptat_de_2;

    for (const string& cuvant : toate_cuvintele) {
        if (regex_match(cuvant, regex1)) {
            acceptat_de_1.insert(cuvant);
        }
        if (regex_match(cuvant, regex2)) {
            acceptat_de_2.insert(cuvant);
        }
    }

    bool echivalenta = (acceptat_de_1 == acceptat_de_2);

    cout << "Expr1: " << regex1_str << endl;
    cout << "Expr2: " << regex2_str << endl;
    cout << "Sunt echivalente? " << (echivalenta ? "DA" : "NU") << endl;

    if (!echivalenta) {
        cout << "\nCuvinte diferite:\n";
        for (const auto& w : acceptat_de_1) {
            if (!acceptat_de_2.count(w)) {
                cout << "Acceptat de expr1, NU si de expr2: " << w << endl;
            }
        }
        for (const auto& w : acceptat_de_2) {
            if (!acceptat_de_1.count(w)) {
                cout << "Acceptat de expr2, NU si de expr1: " << w << endl;
            }
        }
    }

    cout << string(50, '-') << endl;
}

int main() {
    int max_len = 4;

    compara_regexuri("(ab)*", "(ba)*", max_len);

    compara_regexuri("(a|b)*", "(b|a)*", max_len);

    return 0;
}

