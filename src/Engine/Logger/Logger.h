
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger
{
public:
      static void Logg(const std::string &message);
      static void Err(const std::string &message);
};

#endif
