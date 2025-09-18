//Dându-se un automat Moore și un șir de caractere la intrare,
//să se determine șirul de caractere de ieșire.

#include <iostream>
#include <string>
#include <map>

using namespace std;

class MooreMachine {
private:
    string stare_initiala = "S0";
    map<pair<string, char>, string> tranzitii;
    map<string, char> outputs;

public:
    MooreMachine() {
        tranzitii[{"S0", '0'}] = "S0";
        tranzitii[{"S0", '1'}] = "S1";
        tranzitii[{"S1", '0'}] = "S0";
        tranzitii[{"S1", '1'}] = "S1";

        outputs["S0"] = 'A';
        outputs["S1"] = 'B';
    }

    string run(const string& input) {
        string output;
        string stare = stare_initiala;

        output += outputs[stare]; // outputul inițial
        for (char c : input) {
            stare = tranzitii[{stare, c}];
            output += outputs[stare];
        }

        return output;
    }
};

int main() {
    MooreMachine moore;
    string input = "01011";

    cout << "Moore Input:  " << input << endl;
    cout << "Moore Output: " << moore.run(input) << endl;

    return 0;
}
