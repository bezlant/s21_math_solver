#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

class Model {
  private:
    double data;

  public:
    Model() : data(0){};
    void add(double a);
    void mult(double a);
    void reset();
    double getData();
};

#endif
