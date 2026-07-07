#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:

    void begin();

    void info(const String &message);

    void warning(const String &message);

    void error(const String &message);
};

#endif