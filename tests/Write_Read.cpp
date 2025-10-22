#include <iostream>
#include <fstream>
#include <string>

class Item {
public:
    std::string name;
    int quantity;
};

int main() {
    
    Item item1;
    item1.name = "Sword";
    item1.quantity = 3;

    
    std::ofstream outFile("item.txt");  
    if (outFile.is_open()) {
        outFile << item1.name << "\n";    
        outFile << item1.quantity << "\n"; 
        outFile.close();                  
        std::cout << "Item written to file.\n";
    }


    Item itemFromFile;
    std::ifstream inFile("item_swoard.txt");   
    if (inFile.is_open()) {
        std::getline(inFile, itemFromFile.name);  
        inFile >> itemFromFile.quantity;         
        inFile.close();                        
        std::cout << "Item read from file:\n";
        std::cout << "Name: " << itemFromFile.name << "\n";
        std::cout << "Quantity: " << itemFromFile.quantity << "\n";
    }

    return 0;
}
