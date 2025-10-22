#include <iostream>
#include <fstream>
#include "../include/Item.h"
#include "../include/Inventory.h"

// Minimal InventoryManager for file I/O testing
class InventoryManager {
private:
    std::string _filename;
public:
    InventoryManager(std::string filename) : _filename(filename) {}

    void save(Inventory &inventory) {
        std::ofstream outFile(_filename);
        if (!outFile.is_open()) { std::cerr << "Error opening file!" << std::endl; return; }

        outFile << inventory.getSize() << "\n";
        for (int i = 0; i < 10; i++) {
            Item* item = inventory.getItem(i);
            if (item) outFile << item->getName() << "\n";
        }
        outFile.close();
    }

    void load(Inventory &inventory) {
        std::ifstream inFile(_filename);
        if (!inFile.is_open()) { std::cerr << "Error opening file!" << std::endl; return; }

        int size; inFile >> size; inFile.ignore();
        for (int i = 0; i < size; i++) {
            std::string name; std::getline(inFile, name);
            inventory.addItem(new Item(name));
        }
        inFile.close();
    }
};

int main() {
    Inventory inv;
    inv.addItem(new Item("Sword"));
    inv.addItem(new Item("Shield"));
    inv.addItem(new Item("Potion"));

    InventoryManager manager("inventory.txt");
    manager.save(inv);

    Inventory loaded;
    manager.load(loaded);

    std::cout << "Loaded Inventory:" << std::endl;
    loaded.displayInventory();

    return 0;
}
