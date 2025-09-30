class Entity {
 private:
  int health;
  float speed;
  float posX;
  float posY;

 public:
  Entity(int health = 100, float x = 0, float y = 0);

  virtual void takeDamage() = 0;

  void set_health(int health);
  int get_health() const;

  void move(float dx, float dy);
  void setPosition(float x, float y);
  float getX() const;
  float getY() const;

  bool isAlive() const;
};
