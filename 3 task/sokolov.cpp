// Sokolov Fedor AA-22-07

// Inputs
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<functional>
#include<sstream>

using namespace std;

// Utility Functions
bool isNumber(const string& s) {
    for (char const &ch : s) {
        if (isdigit(ch) == 0) return false;
    }
    return true;
}

// Classes
class Pipe {
public:
    static int idCounter;
    int id;
    string name;
    int length, diameter;
    bool atWork;

    Pipe() : id(idCounter++), name("Unnamed"), length(0), diameter(0), atWork(false) {}
    
    void changeStatus() {
        atWork = !atWork;
    }

    void printInfo() const {
        cout << "Pipe ID: " << id << "\nName: " << name << "\nLength: " << length << "\nDiameter: " << diameter << "\nStatus: " << (atWork ? "Working" : "Not working") << endl;
    }
};

int Pipe::idCounter = 1;

class CompressorStation {
public:
    static int idCounter;
    int id;
    string name;
    int numberOfWorkshops, numberOfWorkshopsAtWork, effectiveness;

    CompressorStation() : id(idCounter++), name("Unnamed"), numberOfWorkshops(0), numberOfWorkshopsAtWork(0), effectiveness(0) {}

    void printInfo() const {
        cout << "Station ID: " << id << "\nName: " << name << "\nTotal Workshops: " << numberOfWorkshops << "\nWorkshops at Work: " << numberOfWorkshopsAtWork << "\nEffectiveness: " << effectiveness << "%" << endl;
    }
};

int CompressorStation::idCounter = 1;

// Global Collections
unordered_map<int, Pipe> pipes;
unordered_map<int, CompressorStation> stations;

// Function Declarations
void addPipe();
void addStation();
void viewAllElements();
void editPipe();
void editStation();
void saveToFile();
void loadFromFile();
void searchAndEditPipes();

// Main
int main() {
    string input;

    while (true) {
        cout << "\nChoose an option:\n"
             << "1. Add a pipe\n"
             << "2. Add a compressor station\n"
             << "3. View all elements\n"
             << "4. Edit a pipe\n"
             << "5. Edit a compressor station\n"
             << "6. Save changes\n"
             << "7. Load data\n"
             << "8. Search and Edit Pipes\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> input;

        if (input == "1") {
            addPipe();
        } else if (input == "2") {
            addStation();
        } else if (input == "3") {
            viewAllElements();
        } else if (input == "4") {
            editPipe();
        } else if (input == "5") {
            editStation();
        } else if (input == "6") {
            saveToFile();
        } else if (input == "7") {
            loadFromFile();
        } else if (input == "8") {
            searchAndEditPipes();
        } else if (input == "0") {
            break;
        } else {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return 0;
}

void addPipe() {
    Pipe p;
    cout << "Enter pipe name: ";
    cin >> p.name;
    cout << "Enter pipe length: ";
    cin >> p.length;
    cout << "Enter pipe diameter: ";
    cin >> p.diameter;
    string status;
    cout << "Is the pipe at work (yes/no): ";
    cin >> status;
    p.atWork = (status == "yes");
    pipes[p.id] = p;
    cout << "Pipe added with ID " << p.id << endl;
}

void addStation() {
    CompressorStation s;
    cout << "Enter station name: ";
    cin >> s.name;
    cout << "Enter total number of workshops: ";
    cin >> s.numberOfWorkshops;
    cout << "Enter number of workshops at work: ";
    cin >> s.numberOfWorkshopsAtWork;
    cout << "Enter effectiveness percentage: ";
    cin >> s.effectiveness;
    stations[s.id] = s;
    cout << "Station added with ID " << s.id << endl;
}

void viewAllElements() {
    cout << "\n--- Pipes ---" << endl;
    for (const auto& p : pipes) {
        p.second.printInfo();
        cout << endl;
    }
    cout << "\n--- Compressor Stations ---" << endl;
    for (const auto& s : stations) {
        s.second.printInfo();
        cout << endl;
    }
}

void editPipe() {
    int id;
    cout << "Enter pipe ID to edit: ";
    cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes[id].changeStatus();
        cout << "Pipe status changed!" << endl;
    } else {
        cout << "Pipe with this ID not found!" << endl;
    }
}

void editStation() {
    int id;
    cout << "Enter station ID to edit: ";
    cin >> id;
    if (stations.find(id) != stations.end()) {
        cout << "Enter new number of workshops at work: ";
        int newWorkshops;
        cin >> newWorkshops;
        if (newWorkshops <= stations[id].numberOfWorkshops) {
            stations[id].numberOfWorkshopsAtWork = newWorkshops;
            cout << "Station updated!" << endl;
        } else {
            cout << "Cannot have more workshops at work than exist!" << endl;
        }
    } else {
        cout << "Station with this ID not found!" << endl;
    }
}

void saveToFile() {
    ofstream file("data.txt");
    if (!file.is_open()) {
        cout << "Failed to open file for writing!" << endl;
        return;
    }

    for (const auto& p : pipes) {
        file << "Pipe:" << p.second.id << ":" << p.second.name << ":" << p.second.length << ":" << p.second.diameter << ":" << p.second.atWork << endl;
    }
    for (const auto& s : stations) {
        file << "Station:" << s.second.id << ":" << s.second.name << ":" << s.second.numberOfWorkshops << ":" << s.second.numberOfWorkshopsAtWork << ":" << s.second.effectiveness << endl;
    }
    file.close();
    cout << "Data saved to file." << endl;
}

void loadFromFile() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Failed to open file for reading!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, id, name;
        getline(ss, type, ':');
        getline(ss, id, ':');
        getline(ss, name, ':');

        if (type == "Pipe") {
            Pipe p;
            p.id = stoi(id);
            p.name = name;
            ss >> p.length >> p.diameter >> p.atWork;
            pipes[p.id] = p;
        } else if (type == "Station") {
            CompressorStation s;
            s.id = stoi(id);
            s.name = name;
            ss >> s.numberOfWorkshops >> s.numberOfWorkshopsAtWork >> s.effectiveness;
            stations[s.id] = s;
        }
    }
    file.close();
    cout << "Data loaded from file." << endl;
}

void searchAndEditPipes() {
    cout << "Enter filter (name or status): ";
    string filter;
    cin >> filter;
    vector<int> foundIds;

    for (const auto& p : pipes) {
        if (p.second.name == filter || (filter == "working" && p.second.atWork) || (filter == "not_working" && !p.second.atWork)) {
            foundIds.push_back(p.first);
            p.second.printInfo();
            cout << endl;
        }
    }

    if (foundIds.empty()) {
        cout << "No pipes found with this filter." << endl;
        return;
    }

    cout << "Enter ID of pipe to edit or 'all' to edit all found pipes: ";
    string choice;
    cin >> choice;

    if (choice == "all") {
        for (int id : foundIds) {
            pipes[id].changeStatus();
        }
        cout << "All found pipes have been edited." << endl;
    } else if (isNumber(choice)) {
        int id = stoi(choice);
        if (find(foundIds.begin(), foundIds.end(), id) != foundIds.end()) {
            pipes[id].changeStatus();
            cout << "Pipe edited." << endl;
        } else {
            cout << "Pipe not found in the search results." << endl;
        }
    } else {
        cout << "Invalid input." << endl;
    }
}
