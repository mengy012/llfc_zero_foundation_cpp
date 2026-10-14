#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <memory>
#include <cassert>

namespace my
{
template <typename Key, typename Value, typename Compare = std::less<Key>>
class map
{
  public:
    struct TreeNode
    {
        std::pair<Key, Value> data_;
        TreeNode* left_{nullptr};
        TreeNode* right_{nullptr};
        TreeNode* parent_{nullptr};

        TreeNode(const Key& key, const Value& value = Value(), TreeNode* parent = nullptr) : data_{std::make_pair(key, value)}, left_{nullptr}, right_{nullptr}, parent_{parent} {}
    };

    map(const map&) = delete;
    map(map&&) = delete;
    map& operator=(const map&) = delete;
    map& operator=(map&&) = delete;

    using data_type = std::pair<Key, Value>;

    // 1. 构造、析构与赋值
    map() : root_{nullptr}, size_{0} {}
    ~map()
    {
        clear();
    }

    // 2. 容量
    bool empty() const noexcept
    {
        return size_ == 0;
    }
    std::size_t size() const noexcept
    {
        return size_;
    }

    // 3. 查找
    bool contains(const Key& key) const
    {
        try
        {
            at(key);
            return true;
        }
        catch (const std::out_of_range& e)
        {
            return false;
        }
    }

    // 4. 插入
    bool insert(const Key& key, const Value& value)
    {
        if (root_ == nullptr)
        {
            TreeNode* new_node = new TreeNode(key, value);
            root_ = new_node;
            ++size_;
            return true;
        }

        TreeNode* current = root_;
        TreeNode* parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (cmp_func_(current->data_.first, key))
            {
                current = current->right_;
            }
            else
            {
                // >=
                if (current->data_.first == key)
                {
                    current->data_.second = value;
                    return false;
                }
                else
                {
                    current = current->left_;
                }
            }
        }

        current = new TreeNode(key, value, parent);

        if (key < parent->data_.first)
        {
            parent->left_ = current;
        }
        else if (key > parent->data_.first)
        {
            parent->right_ = current;
        }
        ++size_;

        return true;
    }

    // 5. 元素访问
    Value& at(const Key& key)
    {
        TreeNode* current = root_;

        while (current != nullptr)
        {
            if (cmp_func_(current->data_.first, key))
            {
                current = current->right_;
            }
            else
            {
                // >=
                if (current->data_.first == key)
                {
                    return current->data_.second;
                }
                else
                {
                    current = current->left_;
                }
            }
        }

        throw std::out_of_range("has no value");
    }
    const Value& at(const Key& key) const
    {
        TreeNode* current = root_;

        while (current != nullptr)
        {
            if (cmp_func_(current->data_.first, key))
            {
                current = current->right_;
            }
            else
            {
                // >=
                if (current->data_.first == key)
                {
                    return current->data_.second;
                }
                else
                {
                    current = current->left_;
                }
            }
        }

        throw std::out_of_range("has no value");
    }
    Value& operator[](const Key& key)
    {
        TreeNode* current = root_;
        TreeNode* parent = nullptr;

        if (current == nullptr)
        {
            TreeNode* tmp = new TreeNode(key);
            root_ = tmp;
            ++size_;
            return root_->data_.second;
        }

        while (current != nullptr)
        {
            parent = current;
            if (cmp_func_(current->data_.first, key))
            {
                current = current->right_;
            }
            else
            {
                // >=
                if (current->data_.first == key)
                {
                    return current->data_.second;
                }
                else
                {
                    current = current->left_;
                }
            }
        }

        if (key < parent->data_.first)
        {
            parent->left_ = new TreeNode(key);
            parent->left_->parent_ = parent;
            ++size_;
            return parent->left_->data_.second;
        }
        else if (key > parent->data_.first)
        {
            parent->right_ = new TreeNode(key);
            parent->right_->parent_ = parent;
            ++size_;
            return parent->right_->data_.second;
        }
    }

    // 6. 删除
    bool erase(const Key& key)
    {
        // 1.找到要删除的节点
        TreeNode* current = root_;
        while (current != nullptr)
        {
            if (key >= current->data_.first)
            {
                if (key == current->data_.first)
                {
                    break;
                }
                current = current->right_;
            }
            else
            {
                current = current->left_;
            }
        }
        if (current == nullptr)
        {
            return false;
        }

        // 2. 有两个孩子
        if (current->left_ != nullptr && current->right_ != nullptr)
        {
            // 找右子树最小节点
            TreeNode* successor = current->right_;
            TreeNode* save_node = nullptr;
            while (successor != nullptr)
            {
                save_node = successor;
                successor = successor->left_;
            }

            successor = save_node;

            // 替换当前节点的data
            current->data_ = successor->data_;

            current = successor;
        }
        // 2. 有一个孩子
        if ((current->left_ != nullptr && current->right_ == nullptr) || (current->left_ == nullptr && current->right_ != nullptr))
        {
            // 让这个孩子接替父节点
            if (current->left_ != nullptr)
            {
                TreeNode* parent = current->parent_;
                if (parent)
                {
                    current->left_->parent_ = current->parent_;
                    if (current->parent_->left_ == current)
                    {
                        current->parent_->left_ = current->left_;
                    }
                    else
                    {
                        current->parent_->right_ = current->left_;
                    }
                }
                else
                {
                    current->left_->parent_ = nullptr;
                    root_ = current->left_;
                }
            }

            if (current->right_ != nullptr)
            {
                TreeNode* parent = current->parent_;
                if (parent)
                {
                    current->right_->parent_ = parent;
                    if (parent->left_ == current)
                    {
                        parent->left_ = current->right_;
                    }
                    else
                    {
                        parent->right_ = current->right_;
                    }
                }
                else
                {
                    current->right_->parent_ = nullptr;
                    root_ = current->right_;
                }
            }

            delete current;
            --size_;
            return true;
        }
        // 2. 没有孩子
        if (current->left_ == nullptr && current->right_ == nullptr)
        {
            if (current->parent_ == nullptr)
            {
                root_ = nullptr;
            }
            else if (current->parent_->left_ == current)
            {
                current->parent_->left_ = nullptr;
            }
            else
            {
                current->parent_->right_ = nullptr;
            }
            delete current;
            --size_;
            return true;
        }
        return false;
    }
    void clear() noexcept
    {
        r_clear(root_);
        size_ = 0;
        root_ = nullptr;
    }

    void show()
    {
        r_show(root_);
    }

    Key minimum_key()
    {
        TreeNode* current = root_;
        TreeNode* parent = nullptr;

        if (current == nullptr)
        {
            throw std::out_of_range("minimum_key()");
        }
        while (current != nullptr)
        {
            parent = current;
            current = current->left_;
        }
        return parent->data_.first;
    }
    Key maximum_key()
    {
        TreeNode* current = root_;
        TreeNode* parent = nullptr;

        if (current == nullptr)
        {
            throw std::out_of_range("maximum_key()");
        }

        while (current != nullptr)
        {
            parent = current;
            current = current->right_;
        }
        return parent->data_.first;
    }
    // 7. 迭代器（后续实现）
  private:
    TreeNode* root_{nullptr};
    size_t size_{0};
    [[no_unique_address]] Compare cmp_func_;

    // 删除树中的所有节点
    void r_clear(TreeNode* node)
    {
        if (node == nullptr) return;
        r_clear(node->left_);
        r_clear(node->right_);
        delete node;
    }

    void r_show(TreeNode* node)
    {
        if (node == nullptr) return;
        r_show(node->left_);
        std::cout << "key: " << node->data_.first << ' ' << "value: " << node->data_.second << std::endl;
        r_show(node->right_);
    }
};
} // namespace my

int main()
{
    // {
    //     my::map<int, std::string> my_map;
    //     my_map.insert(3, "c");
    //     my_map.insert(2, "b");
    //     my_map.insert(1, "a");

    //     // std::cout << my_map.maximum_key() << std::endl;
    //     // std::cout << my_map.minimum_key() << std::endl;

    //     std::cout << my_map.size() << std::endl;
    //     my_map.erase(1);
    //     std::cout << my_map.size() << std::endl;
    //     std::cout << my_map.minimum_key() << std::endl;

    //     // my_map[1] = "a";
    //     std::cout << my_map[1] << std::endl;
    //     std::cout << my_map[2] << std::endl;
    //     std::cout << my_map[3] << std::endl;

    //     std::cout << my_map.size() << std::endl;

    //     my_map.insert(4, "d");
    //     my_map.insert(0, "e");
    //     my_map.show();
    // }

    {

        my::map<std::string, int> myMap;
        // 插入元素
        myMap.insert("apple", 3);
        myMap.insert("banana", 5);
        myMap.insert("orange", 2);
        myMap.insert("grape", 7);
        myMap.insert("cherry", 4);

        myMap.show();

        std::cout << myMap.maximum_key() << std::endl;
        std::cout << myMap.minimum_key() << std::endl;

        std::cout << myMap.contains("banana") << std::endl;
        std::cout << myMap.contains("aaa") << std::endl;

        // 删除元素
        myMap.erase("apple");
        myMap.erase("cherry");

        myMap.show();
    }
}