#include "InventoryItem.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <charconv>
#include <windows.h>
#include <utility>

template <typename T>
static bool parse_str(const std::string& s, T& value)
{
    T result{};

    auto* p_left = s.data();
    auto* p_right = s.data() + s.size();

    auto [ptr, ec] = std::from_chars(p_left, p_right, result);
    if (ec == std::errc{} && ptr == p_right)
    {
        value = result;
        return true;
    }
    return false;
}

Inventory_system::Inventory_system(/* args */)
{
    SetConsoleOutputCP(CP_UTF8);
}

Inventory_system::~Inventory_system() {}

bool Inventory_system::add_product(int id, std::string name, int quantity)
{
    auto it = std::find_if(products_.begin(), products_.end(), [id](const Product& obj) { return obj.id == id; });
    if (it == products_.end())
    {
        products_.emplace_back(id, name, quantity);
        return true;
    }
    return false;
}

bool Inventory_system::remove_product(int id)
{
    auto it = std::find_if(products_.begin(), products_.end(), [id](const Product& obj) { return obj.id == id; });
    if (it != products_.end())
    {
        products_.erase(it);
        return true;
    }

    return false;
}

bool Inventory_system::update_product_info(int id, int quantity)
{
    auto it = std::find_if(products_.begin(), products_.end(), [id](const Product& obj) { return obj.id == id; });

    if (it != products_.end())
    {
        it->quantity = quantity;
        return true;
    }
    return false;
}

void Inventory_system::show_products()
{
    std::cout << ">>>>>>>>>>>>>>>>>>>>>BEGIN>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << "id\tname\tquantity" << std::endl;
    for (const auto& [id, name, quantity] : products_)
    {
        // std::cout << "-----------------------------------------------" << std::endl;
        // std::cout << "id: " << id << std::endl;
        // std::cout << "name: " << name << std::endl;
        // std::cout << "quantity: " << quantity << std::endl;
        // std::cout << "-----------------------------------------------" << std::endl;

        std::cout << id << '\t' << name << '\t' << quantity << std::endl;
    }
    std::cout << ">>>>>>>>>>>>>>>>>>>>>END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

void Inventory_system::run_command()
{
    std::string line{};
    int number{};
    bool is_running{true};

    while (is_running)
    {
        std::cout << "\n=== Inventory Management System ===\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Delete Product\n";
        std::cout << "3. Update Product Quantity\n";
        std::cout << "4. Display All Products\n";
        std::cout << "5. Exit\n";
        while (std::getline(std::cin, line))
        {
            if (parse_str(line, number) && number >= 1 && number <= 5)
            {
                break;
            }
            else
            {
                std::cout << "请输入数字1-5." << std::endl;
            }
        }

        if (!std::cin)
        {
            return; // 结束整个交互，不再执行命令
        }

        switch (number)
        {
        case 1:
        {
            Product product{};
            std::string line;
            std::cout << "id: ";
            while (std::getline(std::cin, line))
            {
                if (parse_str(line, product.id))
                {
                    break;
                }
                else
                {
                    std::cout << "id是int类型" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }

            std::cout << "name: ";
            while (std::getline(std::cin, line))
            {
                if (!line.empty())
                {
                    product.name = line;
                    break;
                }
                else
                {
                    std::cout << "name不能为空" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }

            std::cout << "quantity: ";
            while (std::getline(std::cin, line))
            {
                if (parse_str(line, product.quantity))
                {
                    break;
                }
                else
                {
                    std::cout << "quantity是int类型" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }

            // products_.push_back(std::move(product));

            if (!add_product(product.id, std::move(product.name), product.quantity))
            {
                std::cout << "添加失败：商品 ID 已存在" << std::endl;
            }
            else
            {
                std::sort(products_.begin(), products_.end(), [](const Product& o1, const Product& o2) { return o1.id < o2.id; });
            }
        }
        break;
        case 2:
        {
            std::string line;
            int id{};
            std::cout << "id: ";
            while (std::getline(std::cin, line))
            {
                if (parse_str(line, id))
                {
                    break;
                }
                else
                {
                    std::cout << "id是int类型" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }
            remove_product(id);
        }

        break;
        case 3:
        {
            std::string line;
            int id{};
            std::cout << "id: ";
            while (std::getline(std::cin, line))
            {
                if (parse_str(line, id))
                {
                    break;
                }
                else
                {
                    std::cout << "id是int类型" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }

            std::cout << "quantity: ";
            int quantity{};
            while (std::getline(std::cin, line))
            {
                if (parse_str(line, quantity))
                {
                    break;
                }
                else
                {
                    std::cout << "quantity是int类型" << std::endl;
                }
            }
            if (!std::cin)
            {
                return; // 结束整个交互，不再执行命令
            }

            update_product_info(id, quantity);
        }

        break;
        case 4:
            show_products();

            break;
        case 5:
            is_running = false;
            break;

        default:

            break;
        }
    }
}
