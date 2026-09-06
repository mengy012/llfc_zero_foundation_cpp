#pragma once

#include <string>
#include <vector>

// 定义商品结构体
struct Product
{
    int id;
    std::string name;
    int quantity;
};

// 管理库存中的商品信息，包括添加、删除、更新和显示商品。每个商品包含商品ID、名称和数量。

class Inventory_system

{
  private:
    std::vector<Product> products_;

  public:
    Inventory_system(/* args */);
    ~Inventory_system();

    // 添加商品
    bool add_product(int id, std::string name, int quantity);

    // 删除商品
    bool remove_product(int id);

    // 更新商品 -> 修改商品信息 -> 修改商品数量
    bool update_product_info(int id, int quantity);

    // 显示商品
    void show_products();

    // 命令行操控
    void run_command();
};
