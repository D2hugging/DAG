#include "task/task.h"
#include <string>
#include <unordered_map>
#include <memory>



class TaskFactory {
   public:
    static TaskFactory& GetInstance() {
        static TaskFactory instance;
        return instance;
    }
    using TaskCreator = function<unique_ptr<Task>()>;

    void RegisterTaskCreator(const string& nodeName, TaskCreator creator) {
        taskCreators[nodeName] = std::move(creator);
    }

    unique_ptr<Task> CreateTask(const string& nodeName) {
        if (taskCreators.find(nodeName) != taskCreators.end()) {
            return taskCreators[nodeName]();
        }
        return nullptr;
    }

   private:
    std::unordered_map<std::string, TaskCreator> taskCreators;

    TaskFactory() = default;
    TaskFactory(const TaskFactory&) = delete;
    TaskFactory& operator=(const TaskFactory&) = delete;
};