#ifndef CONSOLEDEMO_H
#define CONSOLEDEMO_H

#include <ConsoleWindow.h>

class ConsoleDemo : public ConsoleWindow
{
 protected:
    virtual void onRefresh() override;
 public:
    ConsoleDemo();
};

#endif // CONSOLEDEMO_H
