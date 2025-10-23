#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

constexpr int MAX_MOKINIAI = 3;
constexpr int MAX_PAZYMIAI = 3;

int mokiniuKiekis = 0;
string vardai[MAX_MOKINIAI];
int pazymiai[MAX_MOKINIAI][MAX_PAZYMIAI];
int pazymiuKiekis[MAX_MOKINIAI];

int ragh(const string& tekstas, int min = INT_MIN, int max = INT_MAX) {
    int reiksme;
    while (true) {
        cout << tekstas;
        cin >> reiksme;

        if (cin.fail() || reiksme < min || reiksme > max) {
            cout << "Klaida! Iveskite skaiciu nuo " << min << " iki " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return reiksme;
        }
    }
}

void pridetiMokini() {
    while (true) {
        if (mokiniuKiekis >= MAX_MOKINIAI) {
            cout << "Pasiektas mokiniu limitas!\n";
            return;
        }

        cout << "Iveskite mokinio varda: ";
        cin >> vardai[mokiniuKiekis];

        pazymiuKiekis[mokiniuKiekis] = ragh("Kiek pazymiu norite ivesti 1-10: ", 1, MAX_PAZYMIAI);

        for (int j = 0; j < pazymiuKiekis[mokiniuKiekis]; j++) {
            pazymiai[mokiniuKiekis][j] = ragh("Iveskite pazymi " + to_string(j + 1) + ": ", 1, 10);
        }

        mokiniuKiekis++;
        cout << "Mokinys sekmingai pridetas!\n";

        int testi = ragh("\nAr norite testi sia funkcija? 1 - Taip, 0 - Ne: ", 0, 1);
        if (testi == 0) break;
    }
}

void rodytiVisus() {
    while (true) {
        if (mokiniuKiekis == 0) {
            cout << "Nera ivestu mokiniu.\n";
            return;
        }

        cout << "\n Mokiniu sarasas \n";
        for (int i = 0; i < mokiniuKiekis; i++) {
            cout << setw(2) << i + 1 << ". " << vardai[i] << ": ";
            for (int j = 0; j < pazymiuKiekis[i]; j++)
                cout << pazymiai[i][j] << " ";
            cout << endl;
        }

        int testi = ragh("\nAr norite testi sia funkcija? 1 - Taip 0 - Ne: ", 0, 1);
        if (testi == 0) break;
    }
}

void rodytiMokini() {
    while (true) {
        if (mokiniuKiekis == 0) {
            cout << "Nera ivestu mokiniu.\n";
            return;
        }

        string vardas;
        cout << "Iveskite mokinio varda: ";
        cin >> vardas;

        bool rastas = false;
        for (int i = 0; i < mokiniuKiekis; i++) {
            if (vardai[i] == vardas) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < pazymiuKiekis[i]; j++)
                    cout << pazymiai[i][j] << " ";
                cout << endl;
                rastas = true;
                break;
            }
        }

        if (!rastas) cout << "Mokinys nerastas.\n";
        int testi = ragh("\nAr norite testi sia funkcija? 1 - Taip 0 - Ne: ", 0, 1);
        if (testi == 0) break;
    }
}

void atnaujintiPazymi() {
    while (true) {
        if (mokiniuKiekis == 0) {
            cout << "Nera mokiniu duomenu.\n";
            return;
        }

        string vardas;
        cout << "Iveskite mokinio varda: ";
        cin >> vardas;

        bool rastas = false;
        for (int i = 0; i < mokiniuKiekis; i++) {
            if (vardai[i] == vardas) {
                rastas = true;
                cout << vardai[i] << " turi siuos pazymius: ";
                for (int j = 0; j < pazymiuKiekis[i]; j++)
                    cout << "[" << j + 1 << "]" << pazymiai[i][j] << " ";
                cout << endl;

                int nr = ragh("Kuri pazymi norite pakeisti 1-" + to_string(pazymiuKiekis[i]) + ": ", 1, pazymiuKiekis[i]);
                pazymiai[i][nr - 1] = ragh("Naujas pazymys 1-10: ", 1, 10);
                cout << "Pazymys atnaujintas!\n";
                break;
            }
        }

        if (!rastas) cout << "Mokinys nerastas.\n";
        int testi = ragh("\nAr norite testi sia funkcija? 1 - Taip 0 - Ne: ", 0, 1);
        if (testi == 0) break;
    }
}

void pasalintiMokini() {
    while (true) {
        if (mokiniuKiekis == 0) {
            cout << "Nera mokiniu duomenu.\n";
            return;
        }

        string vardas;
        cout << "Iveskite mokinio varda, kuri norite pasalinti: ";
        cin >> vardas;

        bool rastas = false;
        for (int i = 0; i < mokiniuKiekis; i++) {
            if (vardai[i] == vardas) {
                for (int j = i; j < mokiniuKiekis - 1; j++) {
                    vardai[j] = vardai[j + 1];
                    pazymiuKiekis[j] = pazymiuKiekis[j + 1];
                    for (int k = 0; k < MAX_PAZYMIAI; k++) {
                        pazymiai[j][k] = pazymiai[j + 1][k];
                    }
                }
                vardai[mokiniuKiekis - 1].clear();
                pazymiuKiekis[mokiniuKiekis - 1] = 0;
                for (int k = 0; k < MAX_PAZYMIAI; k++) {
                    pazymiai[mokiniuKiekis - 1][k] = 0;
                }
                mokiniuKiekis--;
                cout << "Mokinys pasalintas\n";
                rastas = true;
                break;
            }
        }

        if (!rastas) cout << "Tokio mokinio nera.\n";
        int testi = ragh("\nAr norite testi sia funkcija? 1 - Taip 0 - Ne: ", 0, 1);
        if (testi == 0) break;
    }
}

int main() {
    int pasirinkimas;

    do {
        cout << "\nMOKINIU PAZYMIU SISTEMA\n";
        cout << "1. Prideti mokini\n";
        cout << "2. Rodyti visus mokinius\n";
        cout << "3. Rodyti konkretaus mokinio pazymius\n";
        cout << "4. Atnaujinti pazymi\n";
        cout << "5. Pasalinti mokini\n";
        cout << "0. Iseiti\n";

        pasirinkimas = ragh("Pasirinkite veiksma: ", 0, 5);

        switch (pasirinkimas) {
            case 1: pridetiMokini(); break;
            case 2: rodytiVisus(); break;
            case 3: rodytiMokini(); break;
            case 4: atnaujintiPazymi(); break;
            case 5: pasalintiMokini(); break;
            case 0: cout << "Programa baigta.\n"; break;
            default: cout << "Neteisingas pasirinkimas!\n"; break;
        }
    } while (pasirinkimas != 0);
    return 0;
}