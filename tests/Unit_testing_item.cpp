#include <iostream>
#include "Item.h"


class TestItem : public Item {
public:
    TestItem(const std::string &name) : Item(name) {}

    void useItem() {
        std::cout << "Using item: " << name << std::endl;
    }

    void printInfo() {
        std::cout << "Item name: " << name << std::endl;
    }
};

int main() {
    // Test a few items
    TestItem item1("Health Potion");
    item1.printInfo();
    item1.useItem();

    TestItem item2("Mana Potion");
    item2.printInfo();
    item2.useItem();

    TestItem item3("Sword");
    item3.printInfo();
    item3.useItem();

    return 0;
}
