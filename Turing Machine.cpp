//Implementați o mașină Turing care să accepte șiruri de caractere cu număr impar de 1.
//Afișați evoluția benzii pe parcursul procesării.


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct Tranzitie {
    string next_stare;
    char scrie_sim;
    char schimba_dir;
};

class TuringMachine {
private:
    map<pair<string, char>, Tranzitie> tranzitii;
    string stare_start = "q0";
    string stare_accept = "q1";
    string stare_reject = "qr";
    char spatiu = '_';

public:
    TuringMachine() {
        tranzitii[{"q0", '1'}] = {"q2", '1', 'R'};
        tranzitii[{"q0", '0'}] = {"q0", '0', 'R'};
        tranzitii[{"q0", '_'}] = {"qr", '_', 'R'};

        tranzitii[{"q2", '1'}] = {"q0", '1', 'R'};
        tranzitii[{"q2", '0'}] = {"q2", '0', 'R'};
        tranzitii[{"q2", '_'}] = {"q1", '_', 'R'};
    }

    bool run(string banda_input) {
        vector<char> banda(banda_input.begin(), banda_input.end());
        banda.push_back(spatiu);
        int head = 0;
        string stare_curenta = stare_start;

        int step = 0;
        cout << "Evolutia benzii:" << endl;

        while (true) {
            cout << "Pasul " << step++ << ": ";

            for (int i = 0; i < banda.size(); ++i) {
                if (i == head)
                    cout << "[" << banda[i] << "]";
                else
                    cout << " " << banda[i] << " ";
            }
            cout << "   (" << stare_curenta << ")" << endl;

            char simbol_curent = (head < banda.size()) ? banda[head] : spatiu;
            auto key = make_pair(stare_curenta, simbol_curent);

            if (tranzitii.find(key) == tranzitii.end()) {
                return stare_curenta == stare_accept;
            }

            Tranzitie t = tranzitii[key];
            banda[head] = t.scrie_sim;

            if (t.schimba_dir == 'R') ++head;
            else if (t.schimba_dir == 'L') --head;

            if (head < 0) {
                banda.insert(banda.begin(), spatiu);
                head = 0;
            } else if (head >= banda.size()) {
                banda.push_back(spatiu);
            }

            stare_curenta = t.next_stare;
        }
    }
};

int main() {
    TuringMachine tm;

    vector<string> teste_input = {
        "1", "11", "111", "10101", "0000", "1100"
    };

    for (const string& input : teste_input) {
        cout << string(40, '=') << endl;
        cout << "Test: " << input << endl;
        bool result = tm.run(input);
        cout << "Rezultat final: " << (result ? "ACCEPTAT" : "RESPINS") << endl;
    }

    return 0;
}