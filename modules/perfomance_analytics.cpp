/*
===============================================
MODULE: PERFORMANCE ANALYTICS
DATA STRUCTURE: GRAPH (Adjacency List)
REASON: Natural representation of student-subject-performance
TIME COMPLEXITY:
  - Add grade: O(1)
  - Find connections: O(V+E)
  - Top performers: O(n log n)
===============================================
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class PerformanceAnalytics {
private:
    // GRAPH USED HERE (Adjacency List)
    // studentID -> vector of (subject, grade) pairs
    unordered_map<string, vector<pair<string, int>>> graph;
    
public:
    // O(1) operation
    void addGrade(string studentId, string subject, int grade) {
        // ADD EDGE IN GRAPH
        graph[studentId].push_back({subject, grade});
        cout << studentId << " got " << grade << " in " << subject << endl;
    }
    
    // O(V+E) operation where V=students, E=grades
    void analyzeStudent(string studentId) {
        if (graph.find(studentId) != graph.end()) {
            cout << "\nAnalysis for " << studentId << ":" << endl;
            double sum = 0;
            for (auto& grade : graph[studentId]) {
                cout << "- " << grade.first << ": " << grade.second << endl;
                sum += grade.second;
            }
            double average = sum / graph[studentId].size();
            cout << "Average: " << average << endl;
        }
    }
    
    // O(n log n) operation for sorting
    void findTopPerformers() {
        cout << "\n=== TOP PERFORMERS ===" << endl;
        vector<pair<string, double>> averages;
        
        // CALCULATE AVERAGES: O(n*m) where n=students, m=grades per student
        for (auto& student : graph) {
            double sum = 0;
            for (auto& grade : student.second) {
                sum += grade.second;
            }
            double avg = sum / student.second.size();
            averages.push_back({student.first, avg});
        }
        
        // SORT: O(n log n)
        sort(averages.begin(), averages.end(), 
             [](auto& a, auto& b) { return a.second > b.second; });
        
        // DISPLAY TOP 3
        int count = 0;
        for (auto& student : averages) {
            if (count >= 3) break;
            cout << student.first << ": " << student.second << endl;
            count++;
        }
    }
    
    // O(V+E) operation
    void listAllConnections() {
        cout << "\n=== ALL STUDENT-SUBJECT CONNECTIONS ===" << endl;
        for (auto& student : graph) {
            cout << student.first << " takes: ";
            for (auto& grade : student.second) {
                cout << grade.first << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    PerformanceAnalytics analytics;
    
    analytics.addGrade("S001", "Math", 85);
    analytics.addGrade("S001", "Science", 90);
    analytics.addGrade("S002", "Math", 78);
    analytics.addGrade("S002", "Science", 82);
    analytics.addGrade("S003", "Math", 95);
    
    analytics.analyzeStudent("S001");
    analytics.findTopPerformers();
    
    return 0;
}