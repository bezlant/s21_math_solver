#include "Controller.hpp"

double Controller::add(double a) {
    model->add(a);
    return model->getData();
}

double Controller::sub(double a) {
    model->add(-a);
    return model->getData();
}

double Controller::mult(double a) {
    model->mult(a);
    return model->getData();
}

double Controller::div(double a) {
    model->mult(1.0 / a);
    return model->getData();
}

void Controller::reset() {
    model->reset();
}
