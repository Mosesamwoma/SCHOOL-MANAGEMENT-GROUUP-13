#include "performance_analytics.h"
#include <iostream>
#include <algorithm>

void PerformanceAnalytics::addGrade(const std::string& student_id, const std::string& subject, double score) {
    student_grades[student_id].emplace_back(subject, score);
}

double PerformanceAnalytics::getStudentAverage(const std::string& student_id) const {
    auto it = student_grades.find(student_id);
    if (it == student_grades.end() || it->second.empty()) {
        return 0.0;
    }
    
    double total = 0;
    for (const auto& grade : it->second) {
        total += grade.score;
    }
    return total / it->second.size();
}

std::vector<std::pair<std::string, double>> PerformanceAnalytics::getTopPerformers(int k) const {
    // Use min-heap to efficiently find top k performers
    using StudentAvg = std::pair<std::string, double>;
    std::priority_queue<StudentAvg, std::vector<StudentAvg>, 
                       std::function<bool(const StudentAvg&, const StudentAvg&)>> 
        min_heap([](const StudentAvg& a, const StudentAvg& b) {
            return a.second > b.second; // Min-heap based on average
        });
    
    for (const auto& entry : student_grades) {
        double avg = getStudentAverage(entry.first);
        
        if (min_heap.size() < k) {
            min_heap.emplace(entry.first, avg);
        } else if (avg > min_heap.top().second) {
            min_heap.pop();
            min_heap.emplace(entry.first, avg);
        }
    }
    
    // Convert to sorted vector (descending order)
    std::vector<StudentAvg> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    std::reverse(result.begin(), result.end());
    
    return result;
}

std::vector<std::pair<std::string, double>> PerformanceAnalytics::getSubjectTopPerformers(const std::string& subject, int k) const {
    std::vector<std::pair<std::string, double>> subject_grades;
    
    for (const auto& entry : student_grades) {
        for (const auto& grade : entry.second) {
            if (grade.subject == subject) {
                subject_grades.emplace_back(entry.first, grade.score);
                break;
            }
        }
    }
    
    // Sort by grade in descending order
    std::sort(subject_grades.begin(), subject_grades.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });
    
    if (subject_grades.size() > k) {
        subject_grades.resize(k);
    }
    
    return subject_grades;
}

void PerformanceAnalytics::displayAllPerformance() const {
    std::cout << "\n=== ALL STUDENT PERFORMANCE ===\n";
    for (const auto& entry : student_grades) {
        std::cout << "Student: " << entry.first 
                  << ", Average: " << getStudentAverage(entry.first) 
                  << ", Subjects: ";
        for (const auto& grade : entry.second) {
            std::cout << grade.subject << "(" << grade.score << ") ";
        }
        std::cout << "\n";
    }
}

void PerformanceAnalytics::displayStudentPerformance(const std::string& student_id) const {
    auto it = student_grades.find(student_id);
    if (it != student_grades.end()) {
        std::cout << "\n=== PERFORMANCE FOR STUDENT " << student_id << " ===\n";
        std::cout << "Overall Average: " << getStudentAverage(student_id) << "\n";
        for (const auto& grade : it->second) {
            std::cout << "Subject: " << grade.subject << ", Score: " << grade.score << "\n";
        }
    } else {
        std::cout << "No performance data found for student " << student_id << "\n";
    }
}