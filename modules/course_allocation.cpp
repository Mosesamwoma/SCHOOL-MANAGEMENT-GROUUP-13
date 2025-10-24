#include "course_scheduling.h"
#include <iostream>

CircularQueue::CircularQueue(int cap) 
    : capacity(cap), front(0), rear(-1), size(0) {
    queue.resize(capacity);
}

bool CircularQueue::isEmpty() const {
    return size == 0;
}

bool CircularQueue::isFull() const {
    return size == capacity;
}

bool CircularQueue::enqueue(const std::string& student_id) {
    if (isFull()) return false;
    
    rear = (rear + 1) % capacity;
    queue[rear] = student_id;
    size++;
    return true;
}

std::string CircularQueue::dequeue() {
    if (isEmpty()) return "";
    
    std::string student_id = queue[front];
    front = (front + 1) % capacity;
    size--;
    return student_id;
}

CourseScheduler::CourseScheduler(const std::string& code, int capacity)
    : courseCode(code), courseCapacity(capacity), enrollmentQueue(1000) {}

std::string CourseScheduler::registerForCourse(const std::string& student_id) {
    if (enrolledStudents.find(student_id) != enrolledStudents.end()) {
        return "Already enrolled in " + courseCode;
    }
    
    if (enrolledStudents.size() < courseCapacity) {
        enrolledStudents.insert(student_id);
        return "Successfully enrolled in " + courseCode;
    } else {
        if (enrollmentQueue.enqueue(student_id)) {
            return "Added to waiting list for " + courseCode + ". Position: " + 
                   std::to_string(enrollmentQueue.getSize());
        }
        return "Waiting list is full for " + courseCode;
    }
}

bool CourseScheduler::processWaitingList() {
    if (!enrollmentQueue.isEmpty() && enrolledStudents.size() < courseCapacity) {
        std::string student_id = enrollmentQueue.dequeue();
        if (!student_id.empty()) {
            enrolledStudents.insert(student_id);
            return true;
        }
    }
    return false;
}

void CourseScheduler::displayEnrollmentStatus() {
    std::cout << "\n=== COURSE " << courseCode << " ENROLLMENT STATUS ===\n";
    std::cout << "Enrolled: " << enrolledStudents.size() << "/" << courseCapacity << "\n";
    std::cout << "Waiting list: " << enrollmentQueue.getSize() << " students\n";
    
    std::cout << "Enrolled students: ";
    for (const auto& student : enrolledStudents) {
        std::cout << student << " ";
    }
    std::cout << "\n";
}