
#pragma once

#include <libPlasma/c++/Plasma.h>
#include <iostream>

using namespace oblong::plasma;


class ofxPlasma
{

public:

    Hose * hose = NULL;

    ofxPlasma()  {}

    void test(const std::string &pool_name);
    bool setup(const std::string &pool_name);
    bool putProtein(const Protein &protein);
    Protein getNextProtein(float timeout = 1.0 / 100.0);
    void shutdown();
};
