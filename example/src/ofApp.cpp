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
    // also include some binary data
    unsigned char buffer[256];
    for (unsigned int i = 0; i < sizeof(buffer); i++)
        buffer[i] = i;

    // here we deposit a protein
    Protein protein(make_descrip("test-protein"),
                    make_ingests(   make_ingest("x", 67.7),
                                    make_ingest("n", 5),    // some ingest we will not metabolize
                                    make_ingest("key", "hello world"),
                                    make_buffer_ingest("data", buffer, 256),
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
            // also extract some binary data
            const unsigned char *retrieved = plasma.extractIngestAsBuffer(p, "data");
            int bytes = plasma.extractIngestBufferSize(p, "data");
            printf("bytes %d\n", bytes);
            printf("byte at index 199 is %d\n", retrieved[199]);
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
