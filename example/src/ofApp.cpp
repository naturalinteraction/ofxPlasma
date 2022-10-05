#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    // the ofxPlasma class encapsulates a 'Hose'
    // here we participate in a pool (which must exist)
    plasma.setup("test-pool");
    // plasma.test("test-pool");
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    unsigned char buffer[64] = {3};

    // here we deposit a protein
    Protein protein(make_descrip("test-protein"),
                    make_ingests(   make_ingest("x", 67.7),
                                    make_ingest("n", 5),    // some ingest we will not metabolize
                                    make_ingest("key", "hello world"),
                                    make_buffer_ingest("data", buffer, 64),
                                    NULL)
                                );
    printf("%d\n", plasma.putProtein(protein));
}

//--------------------------------------------------------------
void testApp::update()
{
    // here we show how we listen for proteins deposited in the pool
    for (;;)
    {
        Protein p = plasma.getNextProtein();
        if (p.IsNull ())
        {
            // say("no protein");
            break;
        }

        if (! plasma.proteinDescripIs(p, "test-protein"))
        {
            printf("no test protein");
            // p.Spew (std::cout);
            // std::cout.flush ();
        }
        else  // it is a test protein
        {
            float x = plasma.extractIngestAsFloat(p, "x");
            string val = plasma.extractIngestAsString(p, "key");
            printf("%f %s\n", x, val.c_str());
            const unsigned char *retrieved = plasma.extractIngestAsBuffer(p, "data");
            printf("size of retrieved buffer is %ld\n", sizeof(retrieved));  // 8, not 64
            printf("one byte is %d\n", (int)retrieved[0]);
        }
    }  // for
}

//--------------------------------------------------------------
void testApp::exit()
{
    // here we withdraw the hose from the pool
    plasma.shutdown();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)  {}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)  {}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)  {}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)  {}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)  {}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)  {}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)  {}

//--------------------------------------------------------------
void testApp::draw()  {}

//--------------------------------------------------------------
void testApp::keyPressed(int key)  {}
