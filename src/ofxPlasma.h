
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

    Protein getNextProtein()
    {
      return hose -> Next (1.0 / 100.0);
    }

    void shutdown()
    {
        if (hose == NULL)
          return;

        OB_DIE_ON_ERROR (hose -> Withdraw ().Code ());
        hose -> Delete ();
    }

    bool setup(const Str &pname)
    {
        if (hose != NULL)
        {
          printf("already participating\n");
          return false;
        }

        ObRetort tort;
        hose = Pool::Participate (pname, &tort);

        if (tort.IsError ())
        {
            printf("Couldn't participate in '%s' because '%s'\n",
                        pname.utf8 (), tort.Description ().utf8 ());
            hose = NULL;
            return false;
        }

        return true;
    }

};
