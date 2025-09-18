//Dându-se un automat Mealy și un șir de caractere la intrare,
//să se determine șirul de caractere de ieșire.


#include <iostream>
#include <string>
#include <map>

using namespace std;

class MealyMachine {
private:
    string stare_initiala = "S0";
    map<pair<string, char>, pair<string, char>> tranzitii;

public:
    MealyMachine() {
        tranzitii[{"S0", '0'}] = {"S0", 'A'};
        tranzitii[{"S0", '1'}] = {"S1", 'B'};
        tranzitii[{"S1", '0'}] = {"S0", 'B'};
        tranzitii[{"S1", '1'}] = {"S1", 'A'};
    }

    string run(const string& input) {
        string output;
        string stare = stare_initiala;

        for (char c : input) {
            auto tranzitie = tranzitii[{stare, c}];
            stare = tranzitie.first;
            output += tranzitie.second;
        }

        return output;
    }
};

int main() {
    MealyMachine mealy;
    string input = "01011";

    cout << "Mealy Input:  " << input << endl;
    cout << "Mealy Output: " << mealy.run(input) << endl;

    return 0;
}
