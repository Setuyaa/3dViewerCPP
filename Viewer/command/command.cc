#include "command.h"


namespace s21 {

void MoveCommand::execute() {
    viewer.s21_move(dx, dy, dz);
}
void ScaleCommand::execute() {
    viewer.s21_scale(scale_cur,scale_prev);
}
void RotateCommand::execute() {
    viewer.s21_rotate(angle, rx, ry, rz);
}
void ParserCommand::execute() {
    viewer.main_parcer(file, res);
}
}
