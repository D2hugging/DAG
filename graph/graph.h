
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include "graph/node.h"

class Node;
class Task;
class TaskFactory;

class Graph {
   public:
    Graph(TaskFactory& factory) : factory_(factory) {}

    void AddNode(const std::string& name) {
        if (nodes_.find(name) != nodes_.end()) return;
        Node* node = new Node(name);
        nodes_[name] = node;
    }

    void AddDependency(const std::string& src, const std::string& dst) {
        if (nodes_.find(src) == nodes_.end() ||
            nodes_.find(dst) == nodes_.end()) {
            cout << "Invalid task ID or dependency ID.\n";
            return;
        }
        Node* src_node = nodes_[src];
        Node* dst_node = nodes_[dst];
        src_node->AddDependency(dst_node);
        dst_node->increase_in_degree();
    }

    void ExecuteTask(Node* node) {
        std::unique_ptr<Task> task = factory_.CreateTask(node->name());
        task->Execute();

        std::cout << "Finished executing task: " << node->name() << std::endl;
    }

    void ExecuteWorkflow() {
        std::queue<Node*> ready;

        for (auto& pair : nodes_) {
            Node* node = pair.second;
            if (node->in_degree() == 0) {
                ready.push(node);
            }
        }

        while (!ready.empty()) {
            Node* current = ready.front();
            ready.pop();

            ExecuteTask(current);

            for (Node* dependency : current->dependencies_) {
                dependency->decrease_in_degree();
                if (dependency->in_degree() == 0) {
                    ready.push(dependency);
                }
            }
        }
    }

   private:
    std::unordered_map<std::string, Node*> nodes_;
    TaskFactory& factory_;
};
