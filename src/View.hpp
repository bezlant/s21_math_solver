#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "Controller.hpp"

enum Choice {
    SUM = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    RES = 5,
    EXIT = 0,
    NONE = -1
};

class View {
  private:
    Controller *controller;

  public:
    View(Controller *c);
    void displayMenu();
    int performChoice();
    double performNumericInput();
    void startEventLoop();
};

#endif
