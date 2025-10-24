#ifndef SCHOOL_MANAGER_H
#define SCHOOL_MANAGER_H

#include <random>
#include "../modules/student_registry.h"
#include "../modules/course_scheduler.h"
#include "../modules/fee_tracker.h"
#include "../modules/library_system.h"
#include "../modules/analytics_engine.h"

class SchoolManager {
private:
    StudentRegistry studentRegistry;
    CourseScheduler courseScheduler;
    FeeTracker feeTracker;
    LibrarySystem librarySystem;
    AnalyticsEngine analyticsEngine;
    std::mt19937 randomGenerator;

    void initializeSampleData();

public:
    SchoolManager();
    
    // Public methods to access modules
    StudentRegistry& getStudentRegistry() { return studentRegistry; }
    CourseScheduler& getCourseScheduler() { return courseScheduler; }
    FeeTracker& getFeeTracker() { return feeTracker; }
    LibrarySystem& getLibrarySystem() { return librarySystem; }
    AnalyticsEngine& getAnalyticsEngine() { return analyticsEngine; }

    void demonstrateAllFeatures();
};

#endif