#include <iostream>
#include <string>
using namespace std;

class FlightNode {
public:
    string destCity;
    int time;
    int fuel;
    FlightNode* down;

    FlightNode(string dest, int t, int f) {
        destCity = dest;
        time = t;
        fuel = f;
        down = NULL;
    }
};

class CityNode {
public:
    string cityName;
    CityNode* next;
    FlightNode* flightHead;

    CityNode(string name) {
        cityName = name;
        next = NULL;
        flightHead = NULL;
    }
};

class Flight {
private:
    CityNode* head;

    CityNode* findCity(const string& name);
    void StoDUtil(CityNode* current, const string& destination, string path, int time, int fuel, string visited[], int& vcount, bool& found);
    bool isVisited(string visited[], int count, const string& city);
    void allUtil(CityNode* current, string visited[], int& vcount);

public:
    Flight() {
        head = NULL;
    }

    void read_cities();
    void display_cities();
    void read_flights();
    void display_flights();
    void StoD();
    void all();
};

// Read cities
void Flight::read_cities() {
    char answer;
    string city;
    CityNode* last = NULL;

    do {
        cout << "Enter City Name: ";
        cin >> city;
        CityNode* newNode = new CityNode(city);

        if (!head) {
            head = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;

        cout << "Add another city? (Y/N): ";
        cin >> answer;

    } while (answer == 'Y' || answer == 'y');
}

// Display cities
void Flight::display_cities() {
    CityNode* temp = head;
    cout << "\nCities:\n";
    while (temp) {
        cout << "- " << temp->cityName << endl;
        temp = temp->next;
    }
}

// Find city
CityNode* Flight::findCity(const string& name) {
    CityNode* temp = head;
    while (temp) {
        if (temp->cityName == name)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add flights
void Flight::read_flights() {
    char ans;
    string src, dest;
    int time, fuel;

    do {
        cout << "\nEnter Source City: ";
        cin >> src;
        cout << "Enter Destination City: ";
        cin >> dest;
        cout << "Enter Time (in hours): ";
        cin >> time;
        cout << "Enter Fuel (in litres): ";
        cin >> fuel;

        CityNode* srcNode = findCity(src);
        if (!srcNode) {
            cout << "Source city not found!\n";
        } else {
            FlightNode* newFlight = new FlightNode(dest, time, fuel);
            newFlight->down = srcNode->flightHead;
            srcNode->flightHead = newFlight;
        }

        cout << "Add another flight? (Y/N): ";
        cin >> ans;

    } while (ans == 'Y' || ans == 'y');
}

// Display flights
void Flight::display_flights() {
    CityNode* city = head;

    cout << "\nFlight Connections:\n";
    while (city) {
        cout << city->cityName << " -> ";
        FlightNode* flight = city->flightHead;

        while (flight) {
            cout << "[" << flight->destCity << ", " << flight->time << "h, " << flight->fuel << "L] -> ";
            flight = flight->down;
        }

        cout << "NULL\n";
        city = city->next;
    }
}

// Check if city is already visited
bool Flight::isVisited(string visited[], int count, const string& city) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == city)
            return true;
    }
    return false;
}

// DFS utility for StoD
void Flight::StoDUtil(CityNode* current, const string& destination, string path, int time, int fuel, string visited[], int& vcount, bool& found) {
    if (!current || isVisited(visited, vcount, current->cityName))
        return;

    visited[vcount++] = current->cityName;

    FlightNode* flight = current->flightHead;
    while (flight) {
        string newPath = path + " -> " + flight->destCity;
        int newTime = time + flight->time;
        int newFuel = fuel + flight->fuel;

        if (flight->destCity == destination) {
            cout << "Path: " << newPath << " | Time: " << newTime << "h | Fuel: " << newFuel << "L\n";
            found = true;
        } else {
            CityNode* nextCity = findCity(flight->destCity);
            StoDUtil(nextCity, destination, newPath, newTime, newFuel, visited, vcount, found);
        }

        flight = flight->down;
    }

    vcount--; // backtrack
}

// Show paths from source to destination
void Flight::StoD() {
    string source, dest;
    cout << "Enter Source City: ";
    cin >> source;
    cout << "Enter Destination City: ";
    cin >> dest;

    CityNode* srcNode = findCity(source);
    if (!srcNode) {
        cout << "Source city not found.\n";
        return;
    }

    bool found = false;
    string visited[100];
    int vcount = 0;

    cout << "\nPaths from " << source << " to " << dest << ":\n";
    StoDUtil(srcNode, dest, source, 0, 0, visited, vcount, found);

    if (!found)
        cout << "No path found from " << source << " to " << dest << ".\n";
}

// DFS utility for all reachable cities
void Flight::allUtil(CityNode* current, string visited[], int& vcount) {
    if (!current || isVisited(visited, vcount, current->cityName))
        return;

    visited[vcount++] = current->cityName;

    FlightNode* flight = current->flightHead;
    while (flight) {
        if (!isVisited(visited, vcount, flight->destCity)) {
            cout << "- " << flight->destCity << endl;
            CityNode* next = findCity(flight->destCity);
            allUtil(next, visited, vcount);
        }
        flight = flight->down;
    }
}

// Show all reachable cities
void Flight::all() {
    string source;
    cout << "Enter Source City: ";
    cin >> source;

    CityNode* srcNode = findCity(source);
    if (!srcNode) {
        cout << "City not found.\n";
        return;
    }

    string visited[100];
    int vcount = 0;
    int printedBefore = vcount;

    cout << "\nCities reachable from " << source << ":\n";
    allUtil(srcNode, visited, vcount);

    if (vcount <= 1) {
        cout << "No connected cities found.\n";
    }
}


int main() {
    Flight F1;
    int x;

    do {
        cout << "\n*** Select An Option ***";
        cout << "\n1. Enter Cities";
        cout << "\n2. Display Cities";
        cout << "\n3. Add Flight Connections";
        cout << "\n4. Display Flight Connections";
        cout << "\n5. Source To Destination Paths";
        cout << "\n6. All Reachable Cities From Source";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1: F1.read_cities(); break;
            case 2: F1.display_cities(); break;
            case 3: F1.read_flights(); break;
            case 4: F1.display_flights(); break;
            case 5: F1.StoD(); break;
            case 6: F1.all(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (x != 7);

    return 0;
}







