#ifndef FEE_TRACKING_H
#define FEE_TRACKING_H

#include <string>
#include <vector>

struct Payment {
    std::string student_id;
    double amount;
    std::string date;
    std::string description;
    
    Payment(const std::string& id, double amt, const std::string& d, const std::string& desc = "")
        : student_id(id), amount(amt), date(d), description(desc) {}
};

struct AVLNode {
    Payment payment;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(const std::string& id, double amt, const std::string& d, const std::string& desc = "")
        : payment(id, amt, d, desc), left(nullptr), right(nullptr), height(1) {}
};

class FeeTracker {
private:
    AVLNode* root;
    
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, const std::string& student_id, double amount, 
                   const std::string& date, const std::string& description);
    void inOrderRange(AVLNode* node, const std::string& start_id, const std::string& end_id, 
                     std::vector<Payment>& payments) const;
    void inOrderTraversal(AVLNode* node, std::vector<Payment>& payments) const;
    void clearTree(AVLNode* node);
    
public:
    FeeTracker();
    ~FeeTracker();
    void addPayment(const std::string& student_id, double amount, 
                   const std::string& date, const std::string& description = "");
    std::vector<Payment> getPaymentsInRange(const std::string& start_id, const std::string& end_id) const;
    std::vector<Payment> getAllPayments() const;
    double getTotalRevenue() const;
    void displayAllPayments() const;
};

#endif