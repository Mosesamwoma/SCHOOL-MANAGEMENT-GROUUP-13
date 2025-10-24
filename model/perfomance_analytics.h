#ifndef PERFORMANCE_ANALYTICS_H
#define PERFORMANCE_ANALYTICS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

struct Grade {
    std::string subject;
    double score;
    
    Grade(const std::string& subj, double scr) : subject(subj), score(scr) {}
};

class PerformanceAnalytics {
private:
    // student_id -> vector of grades
    std::unordered_map<std::string, std::vector<Grade>> student_grades;
    
public:
    void addGrade(const std::string& student_id, const std::string& subject, double score);
    double getStudentAverage(const std::string& student_id) const;
    std::vector<std::pair<std::string, double>> getTopPerformers(int k) const;
    std::vector<std::pair<std::string, double>> getSubjectTopPerformers(const std::string& subject, int k) const;
    void displayAllPerformance() const;
    void displayStudentPerformance(const std::string& student_id) const;
};

#endif