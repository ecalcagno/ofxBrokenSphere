#include "ofApp.h"

//--------------------------------------------------------------
int main(){
    //Esta funci—n configura el aspecto y el modo de la ventana
    //principal
	ofSetupOpenGL(1366, 768, OF_WINDOW);
    
    
	ofRunApp(new ofApp()); // start the app
}
