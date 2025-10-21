#include "Item.h"

Item::Item(const std::string &name)
    : GameObject(), name(name), size(0, 0)
{
}

Item::Item(const std::string &name, const std::string &texturePath)
    : GameObject(texturePath), name(name)
{
    size = texture.getSize();
}
