#include "school_manager.h"
#include <iostream>
#include <vector>

SchoolManager::SchoolManager() : randomGenerator(std::random_device{}()) {
    initializeSampleData();
}

void SchoolManager::initializeSampleData() {
    std::cout << "Initializing sample data...\n";
    
    // Add sample students
    std::vector<std::string> students = {
        studentRegistry.addStudent("Alice Johnson", "alice@meru.edu", 2),
        studentRegistry.addStudent("Bob Smith", "bob@meru.edu", 2),
        studentRegistry.addStudent("Carol Davis", "carol@meru.edu", 1),
        studentRegistry.addStudent("David Wilson", "david@meru.edu", 3)
    };

    // Add sample fee transactions
    std::uniform_real_distribution<double> feeDist(250.0, 450.0);
    std::uniform_int_distribution<int> dayDist(10, 19);
    
    for (const auto& studentId : students) {
        double amount = feeDist(randomGenerator);
        std::string date = "2024-09-" + std::to_string(dayDist(randomGenerator));
        feeTracker.addTransaction(studentId, amount, date);
    }

    // Add sample library books
    librarySystem.addBook("ISBN001", "Data Structures", "Author A", 2023);
    librarySystem.addBook("ISBN002", "Algorithms", "Author B", 2022);
    librarySystem.addBook("ISBN003", "Database Systems", "Author C", 2024);

    // Borrow some books
    librarySystem.borrowBook("ISBN001", students[0]);
    librarySystem.borrowBook("ISBN002", students[1]);

    // Enroll students in courses and add grades
    std::vector<std::string> courses = {"CS101", "MATH201", "PHY301"};
    std::uniform_real_distribution<double> gradeDist(70.0, 95.0);
    std::bernoulli_distrollment enrollDist(0.7); // 70% chance to enroll
    
    for (const auto& studentId : students) {
        for (const auto& courseId : courses) {
            if (enrollDist(randomGenerator)) {
                courseScheduler.enrollStudent(courseId, studentId);
                // Add random grade between 70-95
                double grade = gradeDist(randomGenerator);
                analyticsEngine.addGrade(studentId, courseId, grade);
            }
        }
    }

    // Process some waitlists
    courseScheduler.processWaitlist("CS101");
    
    std::cout << "Sample data initialized successfully!\n";
}

void SchoolManager::demonstrateAllFeatures() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "MERU UNIVERSITY MANAGEMENT SYSTEM DEMONSTRATION\n";
    std::cout << std::string(60, '=') << "\n";

    // 1. Student Registry Demo
    std::cout << "\n1. STUDENT REGISTRY (Hash Table):\n";
    std::cout << std::string(40, '-') << "\n";
    studentRegistry.displayAllStudents();

    // 2. Course Scheduling Demo
    std::cout << "\n2. COURSE SCHEDULING (Circular Queue):\n";
    std::cout << std::string(40, '-') << "\n";
    courseScheduler.displayCourseStatus("CS101");
    courseScheduler.displayCourseStatus("MATH201");

    // 3. Fee Tracking Demo
    std::cout << "\n3. FEE TRACKING (AVL Tree):\n";
    std::cout << std::string(40, '-') << "\n";
    feeTracker.displayAllTransactions();

    // 4. Library System Demo
    std::cout << "\n4. LIBRARY SYSTEM (Stack + Hash Map):\n";
    std::cout << std::string(40, '-') << "\n";
    librarySystem.displayAllBooks();
    librarySystem.displayBookStatus("ISBN001");

    // 5. Analytics Demo
    std::cout << "\n5. PERFORMANCE ANALYTICS (Graph + Min-Heap):\n";
    std::cout << std::string(40, '-') << "\n";
    
    auto students = studentRegistry.getAllStudentIds();
    if (!students.empty()) {
        analyticsEngine.displayStudentPerformance(students[0]);
        analyticsEngine.displayCourseAnalytics("CS101");
        
        // Show top performers
        auto topPerformers = analyticsEngine.getTopPerformers(3);
        std::cout << "\nTOP 3 PERFORMERS:\n";
        for (const auto& performer : topPerformers) {
            std::cout << "Student " << performer.first << ": " << performer.second << " average\n";
        }
    }
}