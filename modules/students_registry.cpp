/*
===============================================
MODULE: STUDENT REGISTRY
DATA STRUCTURE: HASH TABLE (unordered_map)
REASON: Fast O(1) lookup by student ID
TIME COMPLEXITY:
  - Insert: O(1) average
  - Search: O(1) average
  - Delete: O(1) average
===============================================
*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class StudentRegistry {
private:
    // HASH TABLE USED HERE
    unordered_map<string, string> students; // studentID -> studentName
    
public:
    // O(1) operation
    void addStudent(string id, string name) {
        students[id] = name;
        cout << "Added: " << name << endl;
    }
    
    // O(1) operation
    string findStudent(string id) {
        // HASH TABLE LOOKUP
        if (students.find(id) != students.end()) {
            return students[id];
        }
        return "Not found";
    }
    
    // O(1) operation
    void removeStudent(string id) {
        // HASH TABLE DELETE
        students.erase(id);
        cout << "Removed student " << id << endl;
    }
    
    void displayAll() {
        cout << "\nAll Students:" << endl;
        // ITERATING HASH TABLE: O(n)
        for (auto& student : students) {
            cout << "ID: " << student.first 
                 << " | Name: " << student.second << endl;
        }
    }
};

int main() {
    StudentRegistry registry;
    
    registry.addStudent("S001", "Alice");
    registry.addStudent("S002", "Bob");
    registry.addStudent("S003", "Charlie");
    
    cout << "Find S002: " << registry.findStudent("S002") << endl;
    
    registry.displayAll();
    registry.removeStudent("S001");
    registry.displayAll();
    
    return 0;
}