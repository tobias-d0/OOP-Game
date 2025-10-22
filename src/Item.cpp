#include "Item.h"

Item::Item(const std::string &name)
    : GameObject("assets/textures/placeholder.png"), name(name)
{
}

Item::Item(const std::string &name, const std::string &texturePath)
    : GameObject(texturePath), name(name)
{
    size = texture.getSize();
}
