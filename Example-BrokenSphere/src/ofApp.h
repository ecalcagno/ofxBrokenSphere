#pragma once

#include "ofMain.h"


////////////////////////////////////////////////////////////////////////////////
//CLASE PARTSPHERE
////////////////////////////////////////////////////////////////////////////////
class ofEsfera{
   
public:
    void draw();
    void rotationON();
    void rotationOFF();
    void modo1();
    void modo2();
    void trans1(vector<ofMeshFace> origenT);
    void trans2(vector<ofVec3f> orig);
    void trans3(vector<ofVec3f> orig);
    
    ofEsfera(float size, ofPoint(posicion));
    
    float x;
    float y;
    //Variables
    ofSpherePrimitive esfera;
    vector<ofMeshFace> triangulo;
    vector <ofVec3f> vert;
    vector<ofMeshFace> orig;
    float rot;
    ofVboMesh deformPlane;
    
private:
};


class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
    bool bFill;
    bool bWireframe;
    bool bDrawNormals;
    bool bDrawAxes;
    bool bDrawLights;
    bool bInfoText;
    bool bMousePressed;
    bool bSplitFaces;
    
    ofImage texture1;
    ofImage texture2;
    ofImage texture3;
    
    
    ofVideoGrabber vidGrabber;
    ofVideoPlayer hands;
    
    int mode;
    
    float rot = 0;
    bool pressRot = false;
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;

    ofBoxPrimitive boxe;
    
    ofPlanePrimitive plano;
    
    ofEsfera *esfe;
    ofEsfera *esfe2;
    ofEsfera *esfe3;
    
    ofShader shader;	//objeto para el shader
	ofFbo fbo;			//buffer para el dibujo

    vector<ofMeshFace> origenBox;
    vector<ofMeshFace> origenPlano;
    
    
    
    vector<ofVec3f> OrigenVertices;
};




