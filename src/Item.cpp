#include "Item.h"

// Constructor that initializes an item with a name

Item::Item(const std::string &name)
    : GameObject("assets/textures/placeholder.png"), name(name)
{
}

// Constructor that initializes an item with a name and a custom texture
Item::Item(const std::string &name, const std::string &texturePath)
    : GameObject(texturePath), name(name)
{
    size = texture.getSize();
}
