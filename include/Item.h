#pragma once

#include <string>

class Item {
  private:
  std::string name;
  public:
  virtual void use() = 0;
};