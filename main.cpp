#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Class to handle individual student records
class Student {
private:
    string name;
    int rollNumber;
    double marks;
    char grade;

    // Internal helper to calculate grade based on standard boundaries
    void calculateGrade() {
        if (marks >= 90) grade = 'A';
        else if (marks >= 80) grade = 'B';
        else if (marks >= 70) grade = 'C';
        else if (marks >= 60) grade = 'D';
        else grade = 'F';
    }

public:
    // Function to accept student details from user
    void inputDetails(int index) {
        cout << "\n--- Enter Details for Student " << index + 1 << " ---\n";
        cout << "Enter Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        getline(cin, name);
        
        cout << "Enter Roll Number: ";
        while (!(cin >> rollNumber) || rollNumber <= 0) {
            cout << "Invalid input! Enter a valid positive Roll Number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Marks (0 - 100): ";
        while (!(cin >> marks) || marks < 0 || marks > 100) {
            cout << "Invalid input! Enter marks between 0 and 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        calculateGrade();
    }

    // Getters
    double getMarks() const { return marks; }
    string getName() const { return name; }

    // Function to display student information in a tabular row
    void displayRow() const {
        cout << left << setw(15) << rollNumber 
             << setw(25) << name 
             << setw(15) << fixed << setprecision(2) << marks 
             << setw(10) << grade << "\n";
    }
};

int main() {
    int numStudents;

    cout << "=========================================\n";
    cout << "        STUDENT MARKS ANALYZER          \n";
    cout << "=========================================\n";
    
    cout << "Enter the number of students: ";
    while (!(cin >> numStudents) || numStudents <= 0) {
        cout << "Please enter a valid positive integer for number of students: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Student> classList(numStudents);

    // Collect data
    for (int i = 0; i < numStudents; ++i) {
        classList[i].inputDetails(i);
    }

    // Perform analysis calculations
    double totalMarks = 0;
    double highestMarks = classList[0].getMarks();
    double lowestMarks = classList[0].getMarks();
    string topScorer = classList[0].getName();
    string lowestScorer = classList[0].getName();

    for (const auto& student : classList) {
        double m = student.getMarks();
        totalMarks += m;

        if (m > highestMarks) {
            highestMarks = m;
            topScorer = student.getName();
        }
        if (m < lowestMarks) {
            lowestMarks = m;
            lowestScorer = student.getName();
        }
    }

    double classAverage = totalMarks / numStudents;

    // Output Report Generation
    cout << "\n===========================================================\n";
    cout << "                      STUDENT REPORT                       \n";
    cout << "===========================================================\n";
    cout << left << setw(15) << "Roll No" 
         << setw(25) << "Name" 
         << setw(15) << "Marks" 
         << setw(10) << "Grade" << "\n";
    cout << "-----------------------------------------------------------\n";
    
    for (const auto& student : classList) {
        student.displayRow();
    }
    
    cout << "-----------------------------------------------------------\n";

    // Summary Analytics Block
    cout << "\n===========================================================\n";
    cout << "                    ANALYTICS SUMMARY                      \n";
    cout << "===========================================================\n";
    cout << fixed << setprecision(2);
    cout << "Class Average Marks : " << classAverage << "\n";
    cout << "Highest Score       : " << highestMarks << " (By: " << topScorer << ")\n";
    cout << "Lowest Score        : " << lowestMarks << " (By: " << lowestScorer << ")\n";
    cout << "===========================================================\n";

    return 0;
}
