#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <map>

#include <vector>
#include <list>
#include <utility>    // For std::pair
#include <functional> // For std::hash
#include <iterator>   // For iterator_traits
#include <stdexcept>  // For exceptions

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Compare = std::equal_to<Key>>
class MyHashMap
{
  public:
    struct HashNode
    {
        std::pair<const Key, Value> data_;
        HashNode(const Key& key, const Value& value) : data_{std::make_pair(key, value)} {}
    };

    class Iterator;
    // 构造函数及析构函数
    MyHashMap(size_t initial_capacity = 16, double max_load_factor = 0.75) : bucket_count_{initial_capacity}, element_count_{0}, max_load_factor_{max_load_factor}
    {
        buckets_.resize(bucket_count_);
    }
    ~MyHashMap()
    {
        clear();
    }

    // 禁止拷贝构造和赋值
    MyHashMap(const MyHashMap&) = delete;
    MyHashMap& operator=(const MyHashMap&) = delete;

    using list_type = std::list<HashNode>;
    // 基本操作
    void insert(const Key& key, const Value& value)
    {
        size_t hash_value = hash_func_(key);
        size_t index = hash_value % bucket_count_;

        list_type& list = buckets_[index];
        auto it = std::find_if(list.begin(), list.end(), [&key, this](const HashNode& o) { return compare_func_(key, o.data_.first); });
        if (it != list.end())
        {
            it->data_.second = value;
        }
        else
        {
            list.emplace_back(key, value);
            ++element_count_;
        }

        double load_factor = static_cast<double>(element_count_) / bucket_count_;
        if (load_factor > max_load_factor_)
        {
            rehash();
        }
    }
    Value* find(const Key& key)
    {
        size_t hash_value = hash_func_(key);
        size_t index = hash_value % bucket_count_;

        list_type& list = buckets_[index];

        auto it = std::find_if(list.begin(), list.end(), [&key, this](const HashNode& o) { return compare_func_(key, o.data_.first); });
        if (it != list.end())
        {
            return &(it->data_.second);
        }
        else
        {
            return nullptr;
        }
    }
    const Value* find(const Key& key) const
    {
        size_t hash_value = hash_func_(key);
        size_t index = hash_value % bucket_count_;

        const list_type& list = buckets_[index];

        auto it = std::find_if(list.begin(), list.end(), [&key, this](const HashNode& o) { return compare_func_(key, o.data_.first); });
        if (it != list.end())
        {
            return &(it->data_.second);
        }
        else
        {
            return nullptr;
        }
    }
    bool erase(const Key& key)
    {
        size_t hash_value = hash_func_(key);
        size_t index = hash_value % bucket_count_;

        list_type& list = buckets_[index];
        auto it = std::find_if(list.begin(), list.end(), [&key, this](const HashNode& o) { return compare_func_(key, o.data_.first); });
        if (it != list.end())
        {
            list.erase(it);
            --element_count_;
            return true;
        }
        else
        {
            return false;
        }
    }
    size_t size() const
    {
        return element_count_;
    }
    bool empty() const
    {
        return element_count_ == 0;
    }
    void clear()
    {
        buckets_.clear();
        element_count_ = 0;
    }

    // 迭代器操作
    Iterator begin()
    {

        for (size_t i = 0; i < bucket_count_; i++)
        {
            if (!buckets_[i].empty())
            {
                return {this, i, &buckets_[i].front()};
            }
        }

        return end();
    }
    Iterator end()
    {
        return {this, bucket_count_, nullptr};
    }

    // friend Iterator;

    // 迭代器类
    class Iterator
    {
      public:
        // 迭代器别名
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        // 构造函数
        Iterator(MyHashMap* map, size_t bucket_index, HashNode* node) : map_{map}, bucket_index_{bucket_index}, current_node_{node} {}

        // 解引用操作符
        reference operator*() const
        {
            if (current_node_ == nullptr)
            {
                throw std::out_of_range("iterator out of range");
            }
            else
            {
                return current_node_->data_;
            }
        }
        pointer operator->() const
        {
            if (current_node_ == nullptr)
            {
                throw std::out_of_range("iterator out of range");
            }
            else
            {
                return &(current_node_->data_);
            }
        }

        // 递增操作符
        Iterator& operator++()
        {
            advance();
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            advance();
            return tmp;
        }

        // 比较操作符
        bool operator==(const Iterator& other) const
        {
            return map_ == other.map_ && bucket_index_ == other.bucket_index_ && current_node_ == other.current_node_;
        }
        bool operator!=(const Iterator& other) const
        {
            return map_ != other.map_ || bucket_index_ != other.bucket_index_ || current_node_ != other.current_node_;
        }

      private:
        MyHashMap* map_;
        size_t bucket_index_;
        HashNode* current_node_;

        // 移动到下一个有效节点
        void advance()
        {
            if (current_node_ == nullptr)
            {
                throw std::out_of_range("iterator out of range");
            }
            std::list<HashNode>& list = map_->buckets_[bucket_index_];
            auto it = std::find_if(list.begin(), list.end(), [this](const HashNode& node) { return &node == current_node_; });
            if (it != list.end() && ++it != list.end())
            {
                current_node_ = &(*it);
                return;
            }

            {
                for (size_t i = bucket_index_ + 1; i < map_->bucket_count_; i++)
                {
                    if (!map_->buckets_[i].empty())
                    {
                        bucket_index_ = i;
                        current_node_ = &(map_->buckets_[bucket_index_].front());
                        return;
                    }
                }
                bucket_index_ = map_->bucket_count_;
                current_node_ = nullptr;
            }
        }
    };

  private:
    std::vector<std::list<HashNode>> buckets_;
    size_t bucket_count_;
    size_t element_count_;
    double max_load_factor_;
    Hash hash_func_;
    Compare compare_func_;

    // 辅助函数
    void rehash()
    {
        size_t new_bucket_count_ = bucket_count_ * 2 + 1;
        std::vector<std::list<HashNode>> new_buckets_(new_bucket_count_);

        for (std::list<HashNode>& list : buckets_)
        {
            if (!list.empty())
            {
                for (HashNode& node : list)
                {
                    size_t hash_value = hash_func_(node.data_.first);
                    size_t new_index = hash_value % new_bucket_count_;

                    std::list<HashNode>& new_list = new_buckets_[new_index];
                    new_list.emplace_back(std::move(node));
                }
            }
        }

        buckets_ = std::move(new_buckets_);
        bucket_count_ = new_bucket_count_;
    }
};

int main()
{
    // {
    //     std::unordered_map<std::string, int> umap;

    //     std::unordered_map<std::string, int> umap_init = {{"apple", 1}, {"banana", 2}, {"kiwi", 3}};

    //     std::map<std::string, int> ordered_map = {{"carrot", 1}, {"lettuce", 2}};
    //     std::unordered_map<std::string, int> umap_for_map(ordered_map.begin(), ordered_map.end());

    //     // 方法1：使用下标操作符
    //     umap["grape"] = 7;

    //     // 方法2：使用 insert
    //     umap.insert({"melon", 6});

    //     // 方法3：使用 emplace，直接在容器内部构造元素
    //     umap.emplace("kiwi", 4);

    //     // 使用下标操作符访问或插入
    //     int apple_count = umap["apple"]; // 如果 "apple" 不存在，会插入一个默认值

    //     // 使用 at() 方法访问，不存在时会抛出异常
    //     try
    //     {
    //         int banana_count = umap.at("banana");
    //     }
    //     catch (const std::out_of_range& e)
    //     {
    //         std::cerr << "Key not found." << std::endl;
    //     }

    //     // 使用 find() 方法查找
    //     auto it = umap.find("orange");
    //     if (it != umap.end())
    //     {
    //         std::cout << "Orange count: " << it->second << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "Orange not found." << std::endl;
    //     }

    //     // 根据键删除
    //     umap.erase("grape");

    //     // 根据迭代器删除
    //     auto itt = umap.find("banana");
    //     if (itt != umap.end())
    //     {
    //         umap.erase(itt);
    //     }

    //     // 清空整个容器
    //     umap.clear();

    //     for (const auto& pair : umap)
    //     {
    //         std::cout << pair.first << ": " << pair.second << std::endl;
    //     }

    //     // 使用迭代器
    //     for (auto it = umap.begin(); it != umap.end(); ++it)
    //     {
    //         std::cout << it->first << ": " << it->second << std::endl;
    //     }

    //     // 获取大小
    //     size_t size = umap.size();

    //     // 检查是否为空
    //     bool is_empty = umap.empty();

    //     // 获取桶的数量（用于哈希表内部结构）
    //     size_t bucket_count = umap.bucket_count();

    //     // 重新哈希，调整桶的数量
    //     umap.rehash(20);

    //     // 从一个容器中移交元素到另一个容器
    //     std::unordered_map<std::string, int> umap2 = std::move(umap);

    //     umap.reserve(100); // 预分配足够容纳100个元素的桶
    // }

    {
        MyHashMap<std::string, int> myMap;

        // 插入元素
        myMap.insert("apple", 3);
        myMap.insert("banana", 5);
        myMap.insert("orange", 2);
        myMap.insert("grape", 7);
        myMap.insert("cherry", 4);

        // 使用迭代器遍历元素
        std::cout << "Map contents:\n";
        for (auto it = myMap.begin(); it != myMap.end(); ++it)
        {
            std::cout << it->first << " => " << it->second << "\n";
        }

        // 查找元素
        std::string keyToFind = "banana";
        int* value = myMap.find(keyToFind);
        if (value != nullptr)
        {
            std::cout << "\nFound " << keyToFind << " with value: " << *value << "\n";
        }
        else
        {
            std::cout << "\n" << keyToFind << " not found.\n";
        }

        // 删除元素
        myMap.erase("apple");
        myMap.erase("cherry");

        // 再次遍历
        std::cout << "\nAfter erasing apple and cherry:\n";
        for (auto it = myMap.begin(); it != myMap.end(); ++it)
        {
            std::cout << it->first << " => " << it->second << "\n";
        }
    }
}