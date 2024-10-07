#include "memento.h"
namespace s21 {
StateSettings::StateSettings() {
  state.moveX = 0;
  state.moveY = 0;
  state.moveZ = 0;
  state.rotateX = 0;
  state.rotateY = 0;
  state.rotateZ = 0;
  state.scale = 0;
  state.projection = 0;
  state.edgesScale = 0;
  state.edgesType = 0;
  state.edgesColor = 0;
  state.verticesScale = 0;
  state.verticesType = 0;
  state.verticesColor = 0;
  state.bgColor = 0;
}
Settings StateSettings::getSettings() const { return state; }

Memento::Memento() { state = new StateSettings(); }

StateSettings* Memento::getState() const { return state; }
}  // namespace s21
