
#pragma once

#include <libPlasma/c++/Plasma.h>
#include <iostream>

using namespace oblong::plasma;


class ofxPlasma
{

public:

    ofxPlasma()  {}

    void test(const std::string &pool_name);
    bool setup(const std::string &pool_name);
    bool putProtein(const Protein &protein);
    Protein getNextProtein(float timeout = 1.0 / 100.0);
    void shutdown();

    inline bool proteinDescripIs(const Protein &p, const char* value)
    {
        return (p.Descrips ().Nth (0).Emit<Str> () == value);
    }

    inline std::string extractIngestAsString(const Protein &p, const char *name)
    {
        std::string s = p.Ingests ().Find(name).Emit<Str> ().utf8();
        return s;
    }

    inline float extractIngestAsFloat(const Protein &p, const char *name)
    {
        return p.Ingests ().Find(name).Emit<float> ();
    }

protected:

    Hose * hose = NULL;
};

#define make_descrip(descrip)   (Slaw(slaw_string(descrip)))
#define make_ingests(...)       (Slaw(slaw_map_inline_cf(__VA_ARGS__)))
#define make_ingest(key, value) key, make_slaw(value)