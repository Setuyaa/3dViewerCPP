#ifndef MEMENTO_H
#define MEMENTO_H
namespace s21 {

struct Settings {
  int moveX;
  int moveY;
  int moveZ;
  int rotateX;
  int rotateY;
  int rotateZ;
  int scale;
  int projection;
  int edgesScale;
  int edgesType;
  int edgesColor;
  int verticesScale;
  int verticesType;
  int verticesColor;
  int bgColor;
};

class StateSettings {
 private:
  Settings state;

 public:
  StateSettings();
  explicit StateSettings(const Settings state_) : state(state_) {}
  Settings getSettings() const;
};

class Memento {
 private:
  StateSettings* state;

 public:
  Memento();
  explicit Memento(StateSettings* state_) : state(state_) {}
  StateSettings* getState() const;
};

}  // namespace s21

#endif  // MEMENTO_H
