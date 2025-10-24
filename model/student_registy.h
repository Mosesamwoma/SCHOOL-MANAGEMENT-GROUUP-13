#ifndef STUDENT_REGISTRY_H
#define STUDENT_REGISTRY_H

#include <string>
#include <vector>

struct Student {
    std::string student_id;
    std::string name;
    std::string email;
    std::string phone;
    
    Student(const std::string& id, const std::string& n, const std::string& e, const std::string& p = "")
        : student_id(id), name(n), email(e), phone(p) {}
};

class StudentRegistry {
private:
    static const int TABLE_SIZE = 1000;
    std::vector<std::vector<Student>> table;
    int count;
    
    int hash(const std::string& student_id);
    
public:
    StudentRegistry();
    bool addStudent(const std::string& student_id, const std::string& name, 
                   const std::string& email, const std::string& phone = "");
    Student* findStudent(const std::string& student_id);
    bool removeStudent(const std::string& student_id);
    void displayAllStudents();
    int getCount() const { return count; }
};

#endif