#include <string>
#include <vector>
#include <atomic>

class Node {
   public:
    explicit Node(const std::string& name) : name_(name), in_degree_(0) {}
    std::string name() { return name_; }
    int in_degree() { return in_degree_.load(std::memory_order_relaxed); }
    void increase_in_degree() {
        in_degree_.fetch_add(1, std::memory_order_relaxed);
    }
    void decrease_in_degree() {
        in_degree_.fetch_sub(1, std::memory_order_relaxed);
    }
    void AddDependency(Node* node) { dependencies_.push_back(node); }

    std::string name_;
    std::vector<Node*> dependencies_;
    std::atomic<int> in_degree_;
};