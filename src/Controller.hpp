#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "Model.hpp"

class Controller {
  private:
    Model *model;

  public:
    Controller(Model *m) : model(m){};
    double add(double a);
    double sub(double a);
    double mult(double a);
    double div(double a);
    void reset();
};

#endif
