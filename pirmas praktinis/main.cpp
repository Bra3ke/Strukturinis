
//urte brazenaite

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

int main() {
    string valiutos[4] = {"EUR - Euras",
                          "GBP - Anglijos svaras",
                          "USD - JAV doleris",
                          "INR - Indijos rupija"};
    string trumpiniai[4] = {"EUR", "GBP", "USD", "INR"};
    double kursaiPirkti[4] = {1.0, 0.86, 1.1460, 101.3862};
    double kursaiParduoti[4] = {1.0, 1/0.9220, 1.2340, 107.8546};

    int pasirinkimas, valiuta;
    double kiekis, rezultatas;
    bool veikia = true;

    cout << fixed << setprecision(2);

    while (veikia) {
        cout << "\nPasirinkite funkcija:\n";
        cout << "1 - Valiutos kurso palyginimas\n";
        cout << "2 - Pirkti valiuta (is EUR)\n";
        cout << "3 - Parduoti valiuta (i EUR)\n";
        cout << "0 - Baigti programa\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 0) {
            cout << "Aciu, viso gero!\n";
            veikia = false;
        }
        else if (pasirinkimas == 1) {
            cout << "\n--- Valiutos kurso palyginimas ---\n";
            cout << left << setw(40) << "Valiuta"
                 << setw(15) << "Pirkimo kursas"
                 << setw(15) << "Pardavimo kursas" << endl;
            cout << string(70, '-') << endl;

            for (int i = 0; i < 4; i++) {
                cout << left << setw(40) << valiutos[i]
                     << setw(15) << kursaiPirkti[i]
                     << setw(15) << kursaiParduoti[i] << endl;
            }

            cout << "\nPaspauskite ENTER migtuka, kad gristumet atgal...\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (pasirinkimas == 2 || pasirinkimas == 3) {
            while (true) {
                cout << "\nPasirinkite valiuta (arba 0 - gristi atgal):\n";
                for (int i = 0; i < 4; i++) {
                    cout << i + 1 << " - " << valiutos[i] << endl;
                }
                cout << "Pasirinkimas: ";
                cin >> valiuta;

                if (valiuta == 0) {
                    cout << "Griztama i atgal...\n";
                    break;
                }

                if (valiuta < 1 || valiuta > 4) {
                    cout << "Neteisingas pasirinkimas! Bandykite dar karta:0\n";
                    continue;
                }

                cout << "Iveskite kieki: ";
                cin >> kiekis;

                if (pasirinkimas == 2) { // pirkti
                    rezultatas = kiekis * kursaiPirkti[valiuta - 1];
                    cout << kiekis << " EUR = " << rezultatas << " "
                         << trumpiniai[valiuta - 1] << endl;
                } else { // parduoti
                    rezultatas = kiekis / kursaiParduoti[valiuta - 1];
                    cout << kiekis << " " << trumpiniai[valiuta - 1]
                         << " = " << rezultatas << " EUR" << endl;
                }

                cout << "\nAr norite testi sia funkcija? (1 - taip, 0 - grizti atgal ): ";
                int testi;
                cin >> testi;
                if (testi == 0) break;
            }
        }
        else {
            cout << "Tokios funkcijos nera! Bandykite dar karta:0\n";
        }
    }

    return 0;
}
