#include "View.hpp"
// The model is responsible for managing the data of the application.
// It receives user input from the controller.
// The view renders presentation of the model in a particular format.
// The controller responds to the user input and performs interactions on the
// data model objects. The controller receives the input, optionally validates
// it and then passes the input to the model.

int main() {
    Model model;
    Controller controller(&model);
    View view(&controller);
    view.startEventLoop();
    return 1;
}
