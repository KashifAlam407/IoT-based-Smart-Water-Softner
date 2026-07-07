#include <Arduino.h>

#include "app/app.h"

App app;  // creates one global object

void setup()
{
    app.begin();
}

void loop()
{
    app.update();
}