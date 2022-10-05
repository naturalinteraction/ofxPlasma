
#include "ofxPlasma.h"


void ofxPlasma::test(const std::string &pool_name)
{
        setup(pool_name);

        Protein foo(slaw_string ("descrip"));
        // say(foo.Descrips ().IsList ());
        // say(foo.Descrips ().Count () == 0);
        // say(foo.Descrips ().Nth (0) == Slaw ("descrip"));
        // Protein pro(slaw_map_inline_cc ("key1", "val1", "key2", "val2", NULL));
        Protein pro(slaw_map_inline_cf ("key1", make_slaw((float)65.5), "key2", make_slaw((int)7), "key3", make_slaw("ciao"), NULL));

        // say(pro.Descrips ().Count () == 1);
        Slaw ingests (pro.Ingests ());
        // say(ingests.IsMap ());
        // say(Slaw (65.5) == ingests.Find ("key1"));

        // say(ingests.Find("key1").Emit<float> ());
        // say(ingests.Find("key3").Emit<Str> ());

        std::string s = ingests.Find("key3").Emit<Str>().utf8();
        // say(s);

        // say(Slaw ("ciao") == ingests.Find ("key3"));
        // say(ingests.Count () == 3);

        Protein both(Slaw(slaw_string ("descrip2")), Slaw(slaw_map_inline_cf ("key1", make_slaw((float)65.5), "key2", make_slaw((int)7), "key3", make_slaw("ciao"), NULL)));

        printf("foo  %d\n", putProtein(foo));
        printf("pro  %d\n", putProtein(pro));
        printf("both %d\n", putProtein(both));

        ObRetort tort;

        for (;;)
        {
          Protein p = getNextProtein();
          if (! p.IsNull ())
          {
              if (false)
                p.Spew (std::cout);
              else
                {
                  Str s = p.ToSlaw ().ToString (&tort);
                  OB_DIE_ON_ERROR (tort.Code ());
                  std::cout << s.utf8 ();
                }
              std::cout.flush ();
          }
        }

        shutdown();
}

Protein ofxPlasma::getNextProtein(float timeout)
{
  return hose -> Next (timeout);
}

void ofxPlasma::shutdown()
{
    if (hose == NULL)
      return;

    OB_DIE_ON_ERROR (hose -> Withdraw ().Code ());
    hose -> Delete ();
}

bool ofxPlasma::putProtein(const Protein &protein)
{
    ObRetort_DepositInfo ret = hose -> Deposit (protein);

    if (ret.IsError ())
    {
        printf ("we couldn't deposit: %s\n", ret.Description().utf8());
        return false;
    }
    // printf ("deposited! ts/index: %d, %f\n", (int)ret.index, ret.timestamp);
    return true;
}

bool ofxPlasma::setup(const std::string &pool_name)
{
    Str pname = pool_name.c_str();

    if (hose != NULL)
    {
      printf("already participating\n");
      return false;
    }

    ObRetort tort;
    hose = Pool::Participate (pname, Pool::MMAP_MEDIUM, &tort);  // Pool::MMAP_SMALL

    if (tort.IsError ())
    {
        printf("Couldn't participate in '%s' because '%s'\n",
                    pname.utf8 (), tort.Description ().utf8 ());
        hose = NULL;
        return false;
    }

    return true;
}