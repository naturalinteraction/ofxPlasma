
#include "ofxPlasma.h"


void ofxPlasma::test()
{
        bool rewind_flag = false, exit_flag = false, spew_flag = false;
        const Str pname = "update-pool";

        ObRetort tort;
        Hose *h = Pool::Participate (pname, &tort);

        if (tort.IsError ())
        OB_FATAL_ERROR ("Couldn't participate in '%s' because '%s'\n",
                        pname.utf8 (), tort.Description ().utf8 ());

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

        ObRetort_DepositInfo ret = h->Deposit (foo);

        if (ret.IsError ())
          printf ("we couldn't deposit: %s\n", ret.Description().utf8());
        else
          printf ("deposited! ts/index: %d, %f\n", (int)ret.index, ret.timestamp);

        ObRetort_DepositInfo ret2 = h->Deposit (pro);

        if (ret2.IsError ())
          printf ("we couldn't deposit: %s\n", ret2.Description().utf8());
        else
          printf ("deposited! ts/index: %d, %f\n", (int)ret2.index, ret2.timestamp);

        ObRetort_DepositInfo ret3 = h->Deposit (both);

        if (rewind_flag)
        OB_DIE_ON_ERROR (h->Rewind ().Code ());

        // either wait one second or forever, depending on -x option
        pool_timestamp timeout = (exit_flag ? 1.0 : Hose::WAIT);

        for (;;)
        {
          Protein p = h->Next (timeout);
          if (p.IsNull ())
            break;

          if (spew_flag)
            p.Spew (std::cout);
          else
            {
              Str s = p.ToSlaw ().ToString (&tort);
              OB_DIE_ON_ERROR (tort.Code ());
              std::cout << s.utf8 ();
            }
          std::cout.flush ();
        }

        OB_DIE_ON_ERROR (h->Withdraw ().Code ());
        h->Delete ();
}