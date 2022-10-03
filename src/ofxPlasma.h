
#pragma once

#include <libPlasma/c++/Plasma.h>
#include <iostream>

using namespace oblong::plasma;


class ofxPlasma
{

public:

    Hose * hose = NULL;

    ofxPlasma()  {}

    void test();
    Protein getNextProtein();
    void shutdown();
    bool setup(const Str &pname);

};
