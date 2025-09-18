//Verifi cați dacă un cuvânt este acceptat de un PDA.

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class PDA {
public:
    bool accepta(const string& input) {
        stack<char> stiva;
        int i = 0;
        string stare = "q0";

        cout << "Procesare pentru cuvant: " << input << endl;

        while (i < input.size()) {
            char simbol = input[i];
            cout << "Stare: " << stare << ", Simbol: " << simbol << ", Varf stiva: "
                 << (stiva.empty() ? '#' : stiva.top()) << endl;

            if (stare == "q0") {
                if (simbol == 'a') {
                    stiva.push('A');
                    i++;
                } else if (simbol == 'b') {
                    if (stiva.empty()) return false;
                    stare = "q1";
                } else {
                    return false;
                }
            }

            if (stare == "q1") {
                if (simbol == 'b') {
                    if (stiva.empty() || stiva.top() != 'A') return false;
                    stiva.pop();
                    i++;
                } else {
                    return false;
                }
            }
        }

        cout << "Final: Stiva " << (stiva.empty() ? "goala" : "nevida") << endl;
        return stiva.empty();
    }
};

int main() {
    PDA pda;
    vector<string> teste = {
        "", "ab", "aabb", "aaabbb", "a", "abb", "aab", "aaab"
    };

    for (const auto& cuvant : teste) {
        cout << string(40, '=') << endl;
        bool rezultat = pda.accepta(cuvant);
        cout << "Rezultat: " << (rezultat ? "ACCEPTAT" : "RESPINS") << endl << endl;
    }

    return 0;
}
