#include "task/task.h"
#include <string>

class HelloTask : public Task {
   public:
    std::string name_;
    explicit HelloTask(const std::string& name) : name_(name) {}
    void Execute() override { std::cout << "Executing task: " << name_ << std::endl; }
};