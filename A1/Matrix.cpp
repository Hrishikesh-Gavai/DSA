#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    int matrix_size;
    string cities[100];
    int mat[100][100];   // Time matrix (in hours)
    int fuel[100][100];  // Fuel matrix (in litres)

public:
    Flight();
    void read_cities();
    void display_cities();
    void read_flight();
    void display_flight();
    void StoD();
    void all();
};

Flight::Flight() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            mat[i][j] = 0;
            fuel[i][j] = 0;
        }
    }
}

void Flight::read_cities() {
    cout << "\nEnter Matrix Size: ";
    cin >> matrix_size;
    cin.ignore();

    for (int i = 1; i <= matrix_size; i++) {
        cout << "\nEnter City Name: ";
        getline(cin, cities[i]);
        cout << "Unique Code For " << cities[i] << " Is " << i << endl;
    }
}

void Flight::display_cities() {
    cout << "\nList of Cities with Their Unique Codes:\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << ". " << cities[i] << endl;
    }
}

void Flight::read_flight() {
    int source, dest, time, fuel_amt;

    display_cities();

    char choice;
    do {
        cout << "\nEnter Code For Source City: ";
        cin >> source;
        cout << "Enter Code For Destination City: ";
        cin >> dest;
        cout << "Enter Time (in hours) from " << cities[source] << " to " << cities[dest] << ": ";
        cin >> time;
        cout << "Enter Fuel (in litres) from " << cities[source] << " to " << cities[dest] << ": ";
        cin >> fuel_amt;

        mat[source][dest] = time;
        fuel[source][dest] = fuel_amt;

        cout << "Do you want to add another flight (y/n)? ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void Flight::display_flight() {
    display_cities();

    cout << "\nFlight Time Matrix (in hours):\n\t";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t";
    }
    cout << "\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t";
        for (int j = 1; j <= matrix_size; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\nFuel Matrix (in litres):\n\t";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t";
    }
    cout << "\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t";
        for (int j = 1; j <= matrix_size; j++) {
            cout << fuel[i][j] << "\t";
        }
        cout << "\n";
    }
}

void Flight::StoD() {
    int s, d;
    display_cities();

    cout << "\nEnter Source City Code: ";
    cin >> s;
    cout << "Enter Destination City Code: ";
    cin >> d;

    if (mat[s][d] != 0) {
        cout << "\nDirect flight found from " << cities[s] << " to " << cities[d] 
             << " taking " << mat[s][d] << " hours and consuming " 
             << fuel[s][d] << " litres of fuel.\n";
    } else {
        cout << "\nNo direct flight from " << cities[s] << " to " << cities[d] << ".\n";
    }

    bool found = false;
    for (int k = 1; k <= matrix_size; k++) {
        if (k != s && k != d && mat[s][k] != 0 && mat[k][d] != 0) {
            cout << "Indirect flight via " << cities[k] << ": "
                 << cities[s] << " -> " << cities[k] << " -> " << cities[d]
                 << " taking " << (mat[s][k] + mat[k][d]) << " hours and "
                 << (fuel[s][k] + fuel[k][d]) << " litres of fuel.\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No indirect flight path found from " << cities[s] << " to " << cities[d] << ".\n";
    }
}

void Flight::all() {
    int s;
    display_cities();

    cout << "\nEnter City Code to List All Directly Connected Cities: ";
    cin >> s;

    cout << "\nCities directly connected from " << cities[s] << ":\n";
    bool connected = false;

    for (int i = 1; i <= matrix_size; i++) {
        if (mat[s][i] != 0) {
            cout << "- " << cities[i] << " (Time: " << mat[s][i] 
                 << " hours, Fuel: " << fuel[s][i] << " litres)\n";
            connected = true;
        }
    }

    if (!connected) {
        cout << "No cities are directly connected from " << cities[s] << ".\n";
    }
}

int main() {
    Flight F1;
    int x;

    do {
        cout << "\n***Select An Option***";
        cout << "\n1. Enter Cities";
        cout << "\n2. Display Cities With Their Unique Code";
        cout << "\n3. Read Flight Matrix";
        cout << "\n4. Display Flights Matrix";
        cout << "\n5. Source To Destination Details(Direct & Indirect)";
        cout << "\n6. All Connected Cities To A City";
        cout << "\n7. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1:
                F1.read_cities();
                break;
            case 2:
                F1.display_cities();
                break;
            case 3:
                F1.read_flight();
                break;
            case 4:
                F1.display_flight();
                break;
            case 5:
                F1.StoD();
                break;
            case 6:
                F1.all();
                break;
            default:
                if (x != 7)
                    cout << "Invalid Choice!\n\n";
        }
    } while (x != 7);

    return 0;
}








