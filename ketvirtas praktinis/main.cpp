#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

const int MAX_ITEMS = 50;
menuItemType menuList[MAX_ITEMS];
int quantities[MAX_ITEMS] = {0};
int itemCount = 0;

void getData() {
    ifstream in("menu.txt");
    if (!in) {
        cout << "Klaida: nerastas failas menu.txt!" << endl;
        return;
    }

    string line;
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        size_t lastSpace = line.find_last_of(" \t");
        
        if (lastSpace != string::npos) {
            string name = line.substr(0, lastSpace);
            string priceStr = line.substr(lastSpace + 1);

            while (!name.empty() && (name.back() == ' ' || name.back() == '\t')) {
                name.pop_back();
            }

            if (itemCount < MAX_ITEMS) {
                menuList[itemCount].menuItem = name;
                menuList[itemCount].menuPrice = stod(priceStr);
                itemCount++;
            }
        }
    }
    in.close();
}

void showMenu() {
    cout << "   MENIU   " << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << ". " 
             << left << setw(30) << menuList[i].menuItem 
             << right << fixed << setprecision(2) << menuList[i].menuPrice << " EUR" << endl;
    }
    cout << "               " << endl;
    cout << "Pasirinkite patiekalo numeri ir kieki (pvz.: 2 1). 0 - baigti." << endl;
}

void printCheck() {
    ofstream out("receipt.txt");
    
    cout << endl << "SASKAITA" << endl;
    out << "SASKAITA" << endl;

    double subtotal = 0;

    for (int i = 0; i < itemCount; i++) {
        if (quantities[i] > 0) {
            double kaina = quantities[i] * menuList[i].menuPrice;
            subtotal += kaina;

            cout << left << setw(2) << quantities[i] << "x "
                 << setw(30) << menuList[i].menuItem 
                 << right << fixed << setprecision(2) << kaina << " EUR" << endl;

            out << left << setw(2) << quantities[i] << " "
                << setw(30) << menuList[i].menuItem 
                << right << fixed << setprecision(2) << kaina << " EUR" << endl;
        }
    }

    double pvm = subtotal * 0.21;
    double total = subtotal + pvm;

    cout << "                " << endl;
    cout << left << setw(33) << "PVM (21%)" << right << fixed << setprecision(2) << pvm << " EUR" << endl;
    cout << left << setw(33) << "Galutine suma" << right << fixed << setprecision(2) << total << " EUR" << endl;

    out << "                 " << endl;
    out << left << setw(33) << "PVM (21%)" << right << fixed << setprecision(2) << pvm << " EUR" << endl;
    out << left << setw(33) << "Galutine suma" << right << fixed << setprecision(2) << total << " EUR" << endl;

    out.close();
}

int main() {
    getData();
    
    if (itemCount == 0) {
        return 0;
    }

    showMenu();

    int choice, qty;
    while (true) {
        cout << "Iveskite Patiekalo numeri ir kieki: ";
        cin >> choice;
        if (choice == 0) break;

        cin >> qty;

        if (choice > 0 && choice <= itemCount && qty > 0) {
            quantities[choice - 1] += qty;
        } else {
            cout << "Blogas pasirinkimas, bandykite dar karta." << endl;
        }
    }

    printCheck();

    return 0;
}