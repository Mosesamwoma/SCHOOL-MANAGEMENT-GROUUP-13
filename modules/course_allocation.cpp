/*
===============================================
MODULE: COURSE SCHEDULING
DATA STRUCTURE: QUEUE
REASON: FIFO ensures fair registration order
TIME COMPLEXITY:
  - Enqueue: O(1)
  - Dequeue: O(1)
  - Peek: O(1)
===============================================
*/

#include <iostream>
#include <queue>
#include <string>
using namespace std;

class CourseScheduler {
private:
    // QUEUE USED HERE
    queue<string> waitingList; // stores student IDs
    
public:
    // O(1) operation
    void registerStudent(string studentId) {
        // QUEUE ENQUEUE
        waitingList.push(studentId);
        cout << studentId << " joined waitlist." << endl;
    }
    
    // O(1) operation
    void allocateCourse() {
        if (!waitingList.empty()) {
            // QUEUE DEQUEUE
            string student = waitingList.front();
            waitingList.pop();
            cout << "Course allocated to: " << student << endl;
        } else {
            cout << "No students waiting." << endl;
        }
    }
    
    // O(1) operation
    string nextInLine() {
        if (!waitingList.empty()) {
            // QUEUE PEEK
            return waitingList.front();
        }
        return "None";
    }
    
    void showWaitlist() {
        cout << "\nWaitlist size: " << waitingList.size() << endl;
    }
};

int main() {
    CourseScheduler scheduler;
    
    scheduler.registerStudent("S001");
    scheduler.registerStudent("S002");
    scheduler.registerStudent("S003");
    
    cout << "Next: " << scheduler.nextInLine() << endl;
    
    scheduler.allocateCourse();
    scheduler.allocateCourse();
    
    scheduler.showWaitlist();
    
    return 0;
}