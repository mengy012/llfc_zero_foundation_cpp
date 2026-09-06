#include "InventoryItem.h"

#include <iostream>

int main()
{
    Inventory_system sys;

    // // 添加功能
    // {
    //     if (!sys.add_product(1, "apple", 10))
    //     {
    //         std::cout << "add failed!" << std::endl;
    //     }

    //     if (!sys.add_product(2, "banana", 20))
    //     {
    //         std::cout << "add failed!" << std::endl;
    //     }

    //     if (!sys.add_product(3, "orange", 30))
    //     {
    //         std::cout << "add failed!" << std::endl;
    //     }

    //     if (!sys.add_product(2, "ddddd", 20))
    //     {
    //         std::cout << "add failed!" << std::endl;
    //     }

    //     // sys.show_products();
    // }

    // // 删除功能
    // {
    //     if (!sys.remove_product(2))
    //     {
    //         std::cout << "remove failed" << std::endl;
    //     }

    //     if (!sys.remove_product(99))
    //     {
    //         std::cout << "remove failed" << std::endl;
    //     }

    //     // sys.show_products();
    // }

    // // 更新商品信息
    // {
    //     sys.show_products();
    //     if (!sys.update_product_info(1, 42))
    //     {
    //         std::cout << "update failed" << std::endl;
    //     }

    //     if (!sys.update_product_info(99, 42))
    //     {
    //         std::cout << "update failed" << std::endl;
    //     }
    //     sys.show_products();
    // }

    sys.run_command();
}