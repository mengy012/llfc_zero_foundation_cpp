#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

// 使用 std::shared_ptr 和 std::weak_ptr 构建图的数据结构
// 题目描述：
// 设计并实现一个简单的图结构，其中每个节点可以连接到多个其他节点。使用 std::shared_ptr 来管理节点之间的所有权关系，并使用 std::weak_ptr 防止循环引用，导致内存泄漏。
// 要求：
// 1. 类定义：
//   ○ 创建一个名为 GraphNode 的类。
//   ○ 每个节点包含一个唯一标识符（如 int id）和一个存储连接节点的容器（如 std::vector<std::weak_ptr<GraphNode>>）。
// 2. 成员函数：
//   ○ 构造函数，初始化节点的标识符。
//   ○ void addEdge(const std::shared_ptr<GraphNode>& node);
// 添加一个边到另一个节点。
//   ○ void printEdges() const;
// 打印当前节点连接的所有节点的标识符。
// 3. 图的构建与管理：
//   ○ 编写一个函数 createGraph()，创建多个 GraphNode 对象，并建立它们之间的连接关系。
//   ○ 确保使用 std::shared_ptr 管理节点的生命周期，并通过 std::weak_ptr 存储连接，防止循环引用。
// 4. 测试：
//   ○ 在 main 函数中调用 createGraph()，并打印每个节点及其连接的节点，验证智能指针的正确使用。

class GraphNode
{
  public:
    GraphNode(std::string id) : id_{id} {}
    ~GraphNode() = default;

    GraphNode& addEdge(const std::shared_ptr<GraphNode>& node)
    {
        Vertexs.push_back(node);
        return *this;
    }

    void show_Adjacent_id()
    {
        std::cout << "current node: " << id_ << std::endl;
        for (const auto& ele : Vertexs)
        {
            if (auto locked = ele.lock())
            {
                std::cout << locked->id_ << std::endl;
            }
        }
    }

  private:
    std::string id_{};
    // 相邻的顶点
    std::vector<std::weak_ptr<GraphNode>> Vertexs;
};

std::vector<std::shared_ptr<GraphNode>> createGraph()
{
    std::shared_ptr<GraphNode> A = std::make_shared<GraphNode>("A");
    std::shared_ptr<GraphNode> B = std::make_shared<GraphNode>("B");
    std::shared_ptr<GraphNode> C = std::make_shared<GraphNode>("C");
    std::shared_ptr<GraphNode> D = std::make_shared<GraphNode>("D");

    A->addEdge(B).addEdge(D);
    B->addEdge(A).addEdge(C);
    C->addEdge(B).addEdge(D);
    D->addEdge(A).addEdge(C);

    std::vector<std::shared_ptr<GraphNode>> ret{A, B, C, D};
    return ret;
}
int main()
{
    std::cout << fs::current_path() << std::endl;

    auto nodes = createGraph();
    for (const auto& ele : nodes)
    {
        ele->show_Adjacent_id();
    }
    for (const auto& ele : nodes)
    {
        std::cout << ele.use_count() << std::endl;
    }
    auto t = nodes;
    for (const auto& ele : nodes)
    {
        std::cout << ele.use_count() << std::endl;
    }

}