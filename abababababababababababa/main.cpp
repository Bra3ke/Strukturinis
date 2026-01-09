#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Studento duomenu struktura
struct Student {
    int id;
    string answers;
    int score;
    double percent;
    int grade;
};

// Funkcija pazymiui nustatyti pagal procentus 
// Teigiamas ivertinimas pradedamas nuo 5 balu (50%)
int calculateGrade(double percent) {
    if (percent >= 95.0) return 10;
    if (percent >= 85.0) return 9;
    if (percent >= 75.0) return 8;
    if (percent >= 65.0) return 7;
    if (percent >= 55.0) return 6;
    if (percent >= 50.0) return 5; // Minimalus teigiamas ivertinimas
    if (percent >= 35.0) return 4;
    if (percent >= 25.0) return 3;
    if (percent >= 15.0) return 2;
    return 1;
}

// Funkcija: Klases statistika
void classStatistics(const vector<Student>& students) {
    if (students.empty()) return;

    int n = students.size();
    int minScore = students[0].score;
    int maxScore = students[0].score;
    double sumScore = 0;
    double sumPercent = 0;
    int gradeCount[11] = {0}; 

    for (const auto& lol : students) {
        if (lol.score < minScore) minScore = lol.score;
        if (lol.score > maxScore) maxScore = lol.score;
        sumScore += lol.score;
        sumPercent += lol.percent;
        if (lol.grade >= 1 && lol.grade <= 10) gradeCount[lol.grade]++;
    }

    cout << "\n KLASES STATISTIKA" << endl;
    cout << "Studentu skaicius: " << n << endl;
    cout << "Didziausias balas: " << maxScore << endl;
    cout << "Maziausias balas: " << minScore << endl;
    cout << "Vidutinis balas: " << fixed << setprecision(2) << sumScore / n << endl;
    cout << "Vidutinis procentas: " << sumPercent / n << "%" << endl;

    cout << "\nPazymiu pasiskirstymas klaseje:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << " balu: " << gradeCount[i] << " studentu" << endl;
    }
}

//Studento paieška pagal ID
void searchStudent(const vector<Student>& students) {
    int searchId;
    while (true) {
        cout << "\nPAIESKA" << endl;
        cout << "Iveskite studento ID (0 - baigti): ";
        if (!(cin >> searchId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if (searchId == 0) break;

        bool found = false;
        for (const auto& lol : students) {
            if (lol.id == searchId) {
                cout << "Rasta: ID " << lol.id << " | Taskai: " << lol.score 
                     << " | " << fixed << setprecision(2) << lol.percent << "% | Pazymys: " << lol.grade << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "Studentas su ID " << searchId << " nerastas." << endl;
    }
}

// Rezultatai issaugojami i faila
void saveResults(const vector<Student>& students, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Klaida kuriant rezultatu faila!" << endl;
        return;
    }
    for (const auto& lol : students) {
        out << "ID: " << lol.id << " Taskai: " << lol.score << " Procentai: " 
            << fixed << setprecision(2) << lol.percent << "% Pazymys: " << lol.grade << endl;
    }
    out.close();
    cout << "\n Rezultatai issaugoti faile: " << filename << endl;
}

// Kiekvieno klausimo statistika ir Sunkiausio klausimo nustatymas
void questionAnalysis(const vector<Student>& students, const string& correctAnswers) {
    if (students.empty()) return;
    const int Q_COUNT = 20;
    int correctCnt[Q_COUNT] = {0}, wrongCnt[Q_COUNT] = {0}, emptyCnt[Q_COUNT] = {0};
    int n = students.size();

    for (const auto& am : students) {
        for (int i = 0; i < Q_COUNT; i++) {
            if (i < (int)am.answers.length()) {
                char ans = am.answers[i];
                if (ans == 'T' || ans == 'F') {
                    if (ans == correctAnswers[i]) correctCnt[i]++;
                    else wrongCnt[i]++;
                } else {
                    emptyCnt[i]++;
                }
            } else {
                emptyCnt[i]++;
            }
        }
    }

    cout << "\n KIEKVIENO KLAUSIMO STATISTIKA" << endl;
    double minCorrectPercent = 101.0;
    for (int i = 0; i < Q_COUNT; i++) {
        double p = (correctCnt[i] * 100.0) / n;
        if (p < minCorrectPercent) minCorrectPercent = p;
        cout << "Klausimas " << setw(2) << i + 1 << ": "
             << "Teisingi=" << setw(2) << correctCnt[i] << ", "
             << "Neteisingi=" << setw(2) << wrongCnt[i] << ", "
             << "Neatsake=" << setw(2) << emptyCnt[i] << " (" 
             << fixed << setprecision(1) << p << "%)" << endl;
    }

    cout << "\nSUNKIAUSI KLAUSIMAI (maziausias teisingu %)" << endl;
    for (int i = 0; i < Q_COUNT; i++) {
        double p = (correctCnt[i] * 100.0) / n;
        if (abs(p - minCorrectPercent) < 0.001) {
            cout << "Klausimas nr. " << i + 1 << " (" << fixed << setprecision(1) << p << "%)" << endl;
        }
    }
}

int main() {
    ifstream in("testData.txt");
    if (!in) {
        cout << "Klaida: Nepavyko atidaryti testData.txt!" << endl;
        return 1;
    }

    string correctAnswers;
    getline(in, correctAnswers);

    vector<Student> students;
    int tempId;
    string tempAns;

    while (in >> tempId) {
        in.ignore();
        getline(in, tempAns);
        
        Student am;
        am.id = tempId;
        am.answers = tempAns;
        am.score = 0;

        for (int i = 0; i < 20; i++) {
            if (i < (int)am.answers.length()) {
                char a = am.answers[i];
                if (a == 'T' || a == 'F') {
                    if (a == correctAnswers[i]) am.score += 2;
                    else am.score -= 1;
                }
            }
        }

        am.percent = (am.score / 40.0) * 100.0;
        if (am.percent < 0) am.percent = 0;
        am.grade = calculateGrade(am.percent);
        students.push_back(am);
    }
    in.close();

    cout << "VISI STUDENTU REZULTATAI" << endl;
    for (const auto& lol : students) {
        cout << "ID: " << lol.id << " | Taskai: " << setw(2) << lol.score 
             << " | " << fixed << setprecision(2) << setw(6) << lol.percent << "% | Pazymys: " << lol.grade << endl;
    }

    classStatistics(students);
    questionAnalysis(students, correctAnswers);
    saveResults(students, "results.txt");
    searchStudent(students);

    return 0;
}
