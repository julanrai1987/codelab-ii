#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main() {
    ifstream file("randomJokes.txt");
    if (!file) {
        cerr << "Could not open randomJokes.txt.\n";
        return 1;
    }

    vector<string> jokes;
    string line;
    while (getline(file, line)) {
        if (line.find('?') != string::npos) jokes.push_back(line);
    }
    if (jokes.empty()) {
        cerr << "No valid jokes found.\n";
        return 1;
    }

    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution<size_t> pick(0, jokes.size() - 1);

    cout << "=== Alexa Joke Generator ===\n";
    cout << "Type 'Alexa, tell me a joke' or 'quit'.\n";
    while (true) {
        cout << "\nCommand: ";
        if (!getline(cin, line) || line == "quit") break;
        if (line != "Alexa, tell me a joke") {
            cout << "Unknown command. Try again.\n";
            continue;
        }
        string joke = jokes[pick(generator)];
        size_t separator = joke.find('?');
        cout << joke.substr(0, separator + 1) << '\n';
        cout << "Press Enter for the punchline...";
        string response;
        if (!getline(cin, response)) break;
        cout << joke.substr(separator + 1) << '\n';
    }
    cout << "Goodbye!\n";
    return 0;
}
