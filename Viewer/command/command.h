#ifndef COMMAND_H
#define COMMAND_H

#include "../model/model.h"


namespace s21 {
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class MoveCommand : public Command {
private:
    ViewerFacade& viewer;
    double dx;
    double dy;
    double dz;

public:
    MoveCommand(ViewerFacade& m, double deltaX, double deltaY, double deltaZ) : viewer(m), dx(deltaX), dy(deltaY), dz(deltaZ) {}
    void execute() override;
};

class ScaleCommand : public Command {
private:
    ViewerFacade& viewer;
    double scale_cur;
    double scale_prev;

public:
    ScaleCommand(ViewerFacade& m, double cur, double prev) : viewer(m), scale_cur(cur), scale_prev(prev) {}

    void execute() override;
};

class RotateCommand : public Command {
private:
    ViewerFacade& viewer;
    double angle;
    double rx, ry, rz;

public:
    RotateCommand(ViewerFacade& m, double ang, double x, double y, double z) : viewer(m), angle(ang), rx(x), ry(y), rz(z) {}

    void execute() override;
};

class ParserCommand : public Command {
private:
    ViewerFacade& viewer;
    std::string &file;
    int *res;

public:
    ParserCommand(ViewerFacade& m, std::string &f, int *r) : viewer(m), file(f), res(r) {}

    void execute() override;
};
}


#endif // COMMAND_H
