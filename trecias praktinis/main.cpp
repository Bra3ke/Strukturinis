#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

void skaiciuotiAtlyginimus() {
    ifstream in("salary.txt");
    in.open("..\\salary.txt");
    ofstream out("newSalary.txt");

    cout << fixed << setprecision(2);
    out << fixed << setprecision(2);

    string last, first;
    double current, raisePct;
    int processed = 0;

    while (in >> last >> first >> current >> raisePct) {
        double newSalary = current * (1.0 + raisePct / 100.0);
        cout << last << ' ' << first << ' ' << newSalary << '\n';
        out << last << ' ' << first << ' ' << newSalary << '\n';
        ++processed;
    }

    if (processed == 0) {
        cout << "Klaida" << endl;
    } else {
        cout << "Rezultatai irasyti i newSalary.txt" << endl;
    }
}

void skaiciuotiBilietus() {
    ifstream in("bilietai.txt");
    in.open("..\\bilietai.txt");
    ofstream out("sales_report.txt");

    cout << fixed << setprecision(2);
    out << fixed << setprecision(2);

    int totalTickets = 0;
    double totalSales = 0.0;

    out << "Bilietu pardavimai" << '\n';
    out << "Kaina    Kiekis    Suma" << '\n';

    double price; int count;
    while (in >> price >> count) {
        double sum = price * static_cast<double>(count);
        totalTickets += count;
        totalSales += sum;
        out << price << "  " << count << "  " << sum << '\n';
    }

    cout << "Is viso parduota bilietu: " << totalTickets << endl;
    cout << "Bendra suma: " << totalSales << " EUR" << endl;

    out << "Is viso bilietu: " << totalTickets << '\n';
    out << "Bendra suma: " << totalSales << " EUR" << '\n';

    cout << "Rezultatai irasyti i sales_report.txt" << endl;
}

void spausdintiPasirinkimai() {
    cout << "\nPasirinkimai" << endl;
    cout << "1. Skaiciuoti bilietu pardavimus is bilietai.txt" << endl;
    cout << "2. Atnaujinti darbuotoju atlyginimus is salary.txt i newSalary.txt" << endl;
    cout << "0. Iseiti" << endl;
}

int main() {
    cin.tie(nullptr);

    while (true) {
        spausdintiPasirinkimai();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            string dump;
            getline(cin, dump);
            cout << "Neteisinga. Bandykite dar karta." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                skaiciuotiBilietus();
                break;
            case 2:
                skaiciuotiAtlyginimus();
                break;
            case 0:
                cout << "Programa mire." << endl;
                return 0;
            default:
                cout << "Neteisinga. Bandykite dar karta." << endl;
        }
    }
}
