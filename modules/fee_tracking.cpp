/*
===============================================
MODULE: FEE TRACKING
DATA STRUCTURE: BINARY SEARCH TREE (map)
REASON: Maintains sorted records automatically
TIME COMPLEXITY:
  - Insert: O(log n)
  - Search: O(log n)
  - Range Queries: O(log n + k) where k is results
===============================================
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

class FeeTracker {
private:
    // BINARY SEARCH TREE USED HERE (map is typically Red-Black Tree)
    map<string, double> feeRecords; // studentID -> balance
    
public:
    // O(log n) operation
    void addPayment(string studentId, double amount) {
        feeRecords[studentId] += amount;
        cout << studentId << " paid $" << amount << endl;
    }
    
    // O(log n) operation
    double getBalance(string studentId) {
        // BST SEARCH
        auto it = feeRecords.find(studentId);
        if (it != feeRecords.end()) {
            return it->second;
        }
        return 0.0;
    }
    
    // O(n) operation (in-order traversal)
    void generateReport() {
        cout << "\n=== FEE REPORT ===" << endl;
        // AUTOMATICALLY SORTED BY STUDENT ID
        for (auto& record : feeRecords) {
            cout << "ID: " << record.first 
                 << " | Balance: $" << record.second << endl;
        }
    }
    
    // O(log n + k) for range query
    void showStudentsOwingMoreThan(double amount) {
        cout << "\nStudents owing > $" << amount << ":" << endl;
        for (auto& record : feeRecords) {
            if (record.second < 0) { // Negative balance means owing
                double owing = -record.second;
                if (owing > amount) {
                    cout << record.first << " owes $" << owing << endl;
                }
            }
        }
    }
};

int main() {
    FeeTracker tracker;
    
    tracker.addPayment("S001", 500);
    tracker.addPayment("S002", 300);
    tracker.addPayment("S003", 700);
    tracker.addPayment("S001", 200); // Additional payment
    
    cout << "S001 balance: $" << tracker.getBalance("S001") << endl;
    
    tracker.generateReport();
    
    return 0;
}