#ifndef COURSE_SCHEDULING_H
#define COURSE_SCHEDULING_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

class CircularQueue {
private:
    std::vector<std::string> queue;
    int front, rear, size, capacity;
    
public:
    CircularQueue(int cap);
    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const std::string& student_id);
    std::string dequeue();
    int getSize() const { return size; }
};

class CourseScheduler {
private:
    CircularQueue enrollmentQueue;
    std::unordered_set<std::string> enrolledStudents;
    int courseCapacity;
    std::string courseCode;
    
public:
    CourseScheduler(const std::string& code, int capacity);
    std::string registerForCourse(const std::string& student_id);
    bool processWaitingList();
    void displayEnrollmentStatus();
    int getEnrolledCount() const { return enrolledStudents.size(); }
    int getWaitingCount() const { return enrollmentQueue.getSize(); }
};

#endif