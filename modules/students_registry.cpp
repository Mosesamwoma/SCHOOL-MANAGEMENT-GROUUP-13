#include "student_registry.h"
#include <iostream>

StudentRegistry::StudentRegistry() : count(0) {
    table.resize(TABLE_SIZE);
}

int StudentRegistry::hash(const std::string& student_id) {
    int hash = 0;
    for (char c : student_id) {
        hash = (hash * 31 + c) % TABLE_SIZE;
    }
    return hash;
}

bool StudentRegistry::addStudent(const std::string& student_id, const std::string& name,
                               const std::string& email, const std::string& phone) {
    int index = hash(student_id);
    
    // Check if student already exists
    for (auto& student : table[index]) {
        if (student.student_id == student_id) {
            student = Student(student_id, name, email, phone);
            return true;
        }
    }
    
    // Add new student
    table[index].emplace_back(student_id, name, email, phone);
    count++;
    return true;
}

Student* StudentRegistry::findStudent(const std::string& student_id) {
    int index = hash(student_id);
    
    for (auto& student : table[index]) {
        if (student.student_id == student_id) {
            return &student;
        }
    }
    return nullptr;
}

bool StudentRegistry::removeStudent(const std::string& student_id) {
    int index = hash(student_id);
    
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->student_id == student_id) {
            table[index].erase(it);
            count--;
            return true;
        }
    }
    return false;
}

void StudentRegistry::displayAllStudents() {
    std::cout << "\n=== ALL REGISTERED STUDENTS ===\n";
    for (const auto& bucket : table) {
        for (const auto& student : bucket) {
            std::cout << "ID: " << student.student_id 
                      << ", Name: " << student.name 
                      << ", Email: " << student.email 
                      << ", Phone: " << student.phone << "\n";
        }
    }
    std::cout << "Total students: " << count << "\n";
}