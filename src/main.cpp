#include "consoleView.hpp"
// The model is responsible for managing the data of the application.
// It receives user input from the controller.
// The view renders presentation of the model in a particular format.
// The controller responds to the user input and performs interactions on the
// data model objects. The controller receives the input, optionally validates
// it and then passes the input to the model.

int main() {
    ExampleModel model;
    ExampleController controller(&model);
    ConsoleView view(&controller);
    view.startEventLoop();
    return 1;
}
