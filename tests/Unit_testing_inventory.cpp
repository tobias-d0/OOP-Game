#include "Inventory.h"
#include "Item.h"
#include <iostream>

int main() {
    // Create inventory
    Inventory inv;

    // Create items
    Item* torch = new Item("Torch");
    Item* spear = new Item("Spear");

    // Add items to inventory
    inv.addItem(torch);
    inv.addItem(spear);

    // Display current inventory contents
    inv.displayInventory();

    // Test hasItem by name
    std::cout << std::boolalpha;
    std::cout << "Has Torch? " << inv.hasItem("Torch") << std::endl;
    std::cout << "Has Spear? " << inv.hasItem("Spear") << std::endl;
    std::cout << "Has Shield? " << inv.hasItem("Shield") << std::endl;

    // Get and print names via getItem
    if (inv.getItem(0)) {
        std::cout << "Item in slot 0: " << inv.getItem(0)->getName() << std::endl;
    }
    if (inv.getItem(1)) {
        std::cout << "Item in slot 1: " << inv.getItem(1)->getName() << std::endl;
    }

    // Clean up allocated memory (since Inventory doesn't delete the items themselves)
    delete torch;
    delete spear;

    return 0;
}
