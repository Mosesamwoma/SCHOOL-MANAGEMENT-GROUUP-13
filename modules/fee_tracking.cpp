#include "fee_tracking.h"
#include <iostream>
#include <algorithm>

FeeTracker::FeeTracker() : root(nullptr) {}

FeeTracker::~FeeTracker() {
    clearTree(root);
}

void FeeTracker::clearTree(AVLNode* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

int FeeTracker::height(AVLNode* node) {
    return node ? node->height : 0;
}

int FeeTracker::balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* FeeTracker::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    
    return x;
}

AVLNode* FeeTracker::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    
    return y;
}

AVLNode* FeeTracker::insert(AVLNode* node, const std::string& student_id, double amount,
                           const std::string& date, const std::string& description) {
    if (!node) {
        return new AVLNode(student_id, amount, date, description);
    }
    
    if (student_id < node->payment.student_id) {
        node->left = insert(node->left, student_id, amount, date, description);
    } else {
        node->right = insert(node->right, student_id, amount, date, description);
    }
    
    node->height = 1 + std::max(height(node->left), height(node->right));
    
    int balance = balanceFactor(node);
    
    // Left Left Case
    if (balance > 1 && student_id < node->left->payment.student_id) {
        return rotateRight(node);
    }
    
    // Right Right Case
    if (balance < -1 && student_id > node->right->payment.student_id) {
        return rotateLeft(node);
    }
    
    // Left Right Case
    if (balance > 1 && student_id > node->left->payment.student_id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left Case
    if (balance < -1 && student_id < node->right->payment.student_id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

void FeeTracker::addPayment(const std::string& student_id, double amount,
                           const std::string& date, const std::string& description) {
    root = insert(root, student_id, amount, date, description);
}

void FeeTracker::inOrderRange(AVLNode* node, const std::string& start_id, const std::string& end_id,
                             std::vector<Payment>& payments) const {
    if (!node) return;
    
    if (start_id < node->payment.student_id) {
        inOrderRange(node->left, start_id, end_id, payments);
    }
    
    if (start_id <= node->payment.student_id && node->payment.student_id <= end_id) {
        payments.push_back(node->payment);
    }
    
    if (node->payment.student_id < end_id) {
        inOrderRange(node->right, start_id, end_id, payments);
    }
}

std::vector<Payment> FeeTracker::getPaymentsInRange(const std::string& start_id, const std::string& end_id) const {
    std::vector<Payment> payments;
    inOrderRange(root, start_id, end_id, payments);
    return payments;
}

void FeeTracker::inOrderTraversal(AVLNode* node, std::vector<Payment>& payments) const {
    if (!node) return;
    
    inOrderTraversal(node->left, payments);
    payments.push_back(node->payment);
    inOrderTraversal(node->right, payments);
}

std::vector<Payment> FeeTracker::getAllPayments() const {
    std::vector<Payment> payments;
    inOrderTraversal(root, payments);
    return payments;
}

double FeeTracker::getTotalRevenue() const {
    auto payments = getAllPayments();
    double total = 0;
    for (const auto& payment : payments) {
        total += payment.amount;
    }
    return total;
}

void FeeTracker::displayAllPayments() const {
    auto payments = getAllPayments();
    std::cout << "\n=== ALL FEE PAYMENTS ===\n";
    for (const auto& payment : payments) {
        std::cout << "Student: " << payment.student_id
                  << ", Amount: $" << payment.amount
                  << ", Date: " << payment.date
                  << ", Desc: " << payment.description << "\n";
    }
    std::cout << "Total Revenue: $" << getTotalRevenue() << "\n";
}