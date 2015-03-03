#include "ofApp.h"
float time1;

//--------------------------------------------------------------
void ofApp::setup(){

    //Color de fondo
	ofBackground(255);

    //Cargando el video y reproduciendolo

    hands.loadMovie("fireworks.mov");
    hands.play();
    
    //Modo por default
    mode = 1;
    
    //////////////////////////////////////////////
    //CONFIGURACION DE LUCES
    //////////////////////////////////////////////
    //Seteo de luces
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 255.f, 255.f, 255.f ));
    pointLight2.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));
    
    //////////////////////////////////////////////
    //CONFIGURACION DE LA ESFERA
    //////////////////////////////////////////////
    esfe= new ofEsfera(150.0, ofPoint(ofGetWidth()/2,ofGetHeight()/2,0));
    esfe2= new ofEsfera(80.0, ofPoint(ofGetWidth()/4,ofGetHeight()/2,0));
    esfe3= new ofEsfera(80.0, ofPoint(ofGetWidth()/1.325,ofGetHeight()/2,0));
    //Habilito las luces
    ofEnableLighting();
    
    boxe.set(ofGetWidth()*0.20 );
    boxe.setResolution(28);
    origenBox = boxe.getMesh().getUniqueFaces();
   
    plano.set(ofGetWidth()*0.3, ofGetWidth()*0.3);
    plano.setResolution(210, 210);
    origenPlano = plano.getMesh().getUniqueFaces();
    OrigenVertices = plano.getMesh().getVertices();

    //Cargamos los shaders, un solo objeto contendr‡ los diferentes
    //shaders creados. Esto no solo carga los shaders sino que tambiŽn
    //los compila
	shader.load( "shaderVert.c", "shaderFrag.c" );
    
    //Alojamos memoria para el fbo
	fbo.allocate( ofGetWidth(), ofGetHeight() );
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //PUNTOS DE LUZ
    pointLight.setPosition((ofGetWidth()/2), ofGetHeight()/2, 0);
    
    pointLight2.setPosition(ofGetWidth()/2 + cos(ofGetElapsedTimef()*.5) * 200 ,ofGetHeight()*.5 , 1000);
    
    //Actualizo el video
    hands.update();
    
    time1 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    //Habilito la tercera dimensi—n
    ofEnableDepthTest();
    
    // Box //
    boxe.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    boxe.rotate(sin(ofGetElapsedTimef())*5,1,1,0);
    //boxe.draw();
    
    // Plano //
    plano.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    //plano.draw();
    
    
    //Habilito las luces
    //pointLight.enable();
    //pointLight2.enable();
   
    //Control de rotaci—n
    if(pressRot)
    {
        esfe->rotationON();
        esfe2->rotationON();
        esfe3->rotationON();
        
    }else
    {
        esfe->rotationOFF();
        esfe2->rotationOFF();
        esfe3->rotationOFF();
    }

    if(mode==1)
    {
        esfe->modo1();
        esfe2->modo1();
        esfe3->modo1();
    }
    
    if(mode==2)
    {
        esfe->modo2();
        esfe2->modo2();
        esfe3->modo2();
    }
    
    if(mode==3)
    {
        esfe->trans1(origenBox);
        esfe2->trans1(origenBox);
        esfe3->trans1(origenBox);
    }
  
    if(mode==4)
    {
        esfe->trans2(OrigenVertices);
        esfe2->trans2(OrigenVertices);
        esfe3->trans2(OrigenVertices);
    }
    
    if(mode==5)
    {
        esfe->trans3(OrigenVertices);
        esfe2->trans3(OrigenVertices);
        esfe3->trans3(OrigenVertices);
    }
    
    fbo.begin();
    
    //Este es el color de fondo posta
    ofBackground(0);
    
    //Dibujo y texturizo la esfera
    hands.getTextureReference().bind();
    esfe->esfera.mapTexCoordsFromTexture( hands.getTextureReference() );
    esfe->draw();
    hands.getTextureReference().unbind();
  
    /*
    hands.getTextureReference().bind();
    plano.mapTexCoordsFromTexture( hands.getTextureReference() );
    plano.draw();
    hands.getTextureReference().unbind();
    */
    
    /*
    hands.getTextureReference().bind();
    esfe2->esfera.mapTexCoordsFromTexture( hands.getTextureReference() );
    esfe2->draw();
    hands.getTextureReference().unbind();
    
    hands.getTextureReference().bind();
    esfe3->esfera.mapTexCoordsFromTexture( hands.getTextureReference() );
    esfe3   ->draw();
    hands.getTextureReference().unbind();
    */
    
    fbo.end();
    
    //Muestro o no los spot de luces
    if(bDrawLights)
    {
        pointLight.draw();
    }
    
    float time = ofGetElapsedTimef();
    
    //Si quiero cambiar vertice por vertice
    /*
    for(int i = 0; i < sphere1.getMesh().getNumVertices() ; i++)
    {
        
        sphere1.getMesh().setVertex(i, ofVec3f(vertices[i].x + ofRandom(sin(time*0.01)*30), vertices[i].y ,vertices[i].z));
        
    }
     */
    
    
    shader.begin();
	//dibujamos el fbo
	fbo.draw( 0, 0 );
    
	shader.end();		//deshabilitamos el shader
    
    
    ofDisableLighting();
    ofDisableDepthTest();
    /*
    ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(esfe->esfera.getMesh().getNumIndices()), 100,100);
    ofNoFill();

    ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(esfe2->esfera.getMesh().getNumIndices()), 200,100);
    ofNoFill();
    
    

    ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(boxe.getMesh().getNumIndices()), 400,100);
    ofNoFill();
  
    ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(plano.getMesh().getVertices()), 500,100);
    ofNoFill();
     
    Cambio las posiciones de los tri‡ngulos de la esfera
    
                ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(OrigenVertices.size()), 100,200);
                ofNoFill();
   
    ofSetColor(255, 255, 255); //Defino un texto en blanco
    ofDrawBitmapString(ofToString(esfe3->esfera.getMesh().getNumIndices()), 100,100);
    ofNoFill();
    */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
        case '1':
            mode = 1;
            break;
        case '2':
            mode = 2;
            break;
        case '3':
            mode = 3;
            break;
        case '4':
            mode = 4;
            break;
        case '5':
            mode = 5;
            break;
        case '6':
            mode = 6;
            break;
        case 'r':
            pressRot = !pressRot;
            break;
        case 'n':
            bDrawNormals = !bDrawNormals;
            break;
        case 'l':
            bDrawLights = !bDrawLights;
            break;
        
	}
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

///////////////////////////////////////////////////
//METODOS DE LA CLASE
///////////////////////////////////////////////////

/////////////////////////////////////////////////////
//CONSTRUCTOR
ofEsfera::ofEsfera(float size, ofPoint(posicion))
{
    //Radio de la esfera
    esfera.setRadius( size );
    
    esfera.rotate(180, 0.0, 1.0, 0.0);
    //Resolucion de la esfera
    esfera.setResolution(48);
    
    esfera.setPosition(posicion);
    
    vert = esfera.getMesh().getVertices();
    
    orig = esfera.getMesh().getUniqueFaces();
    
    rot = 0;
}

//////////////////////////////////////////////////
//Dibujar la esfera
void ofEsfera::draw()
{
    //esfera.drawWireframe();
    esfera.draw();
}

/////////////////////////////////////////////////////
//Iniciar la rotaci—n
void ofEsfera::rotationON()
{
    rot +=0.01;
    if(rot > 1.0) rot = 1.0;
    
    esfera.rotate(rot, 0.0, 1.0, 0.0);
}

/////////////////////////////////////////////////////
//Apagar rotaci—n
void ofEsfera::rotationOFF()
{
    rot -=0.01;
    
    if(rot < 0) rot = 0;
    esfera.rotate(rot, 0.0, 1.0, 0.0);
}

/////////////////////////////////////////////////////
void ofEsfera::modo1()
{
    //Cambiamos el modo a dibujo con triangulos para poder actuar sobre los
    //triangulos
    esfera.setMode( OF_PRIMITIVE_TRIANGLES );
    //Guardamos la info en triangles
    triangulo = esfera.getMesh().getUniqueFaces();
    
    //Normales
    ofVec3f faceNormal2;
    
    //Cambio las posiciones de los tri‡ngulos de la esfera
    for(int i = 0; i < orig.size(); i++ )
    {
        //Se guarda la normal de cada tri‡ngulo
        faceNormal2 = triangulo[i].getFaceNormal();
        
        
        //Se recorre cada vertice del triangulo y se reubica
        for(int j = 0; j < 3; j++ )
        {
            
            //ofSetColor(255, 255, 255);
            //ofDrawBitmapString(ofToString(plane.getMesh().getVertex(i)), 200*j,10*i);
            //ofNoFill();
            
            
            //triangles[i].setVertex( j, triangles[i].getVertex(j) + (plane.getMesh().getVertex(i) - triangles[i].getVertex(j))*0.01);
            
            
            triangulo[i].setVertex( j, triangulo[i].getVertex(j) + (orig[i].getVertex(j) - triangulo[i].getVertex(j))*0.01);
            
            
            
            //ofPushMatrix();
            //ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
            //ofRotate(rot);
            
            //ofLine(triangles[i].getVertex(j),original2[i].getVertex(j));
            //ofPopMatrix();
        }
    }
    
    //SETEO LAS NUEVAS POSICIONES DE LOS TRIANGULOS
    esfera.getMesh().setFromTriangles(triangulo);
}

/////////////////////////////////////////////////////
void ofEsfera::modo2()
{
    //Cambiamos el modo a dibujo con triangulos para poder actuar sobre los
    //triangulos
    esfera.setMode( OF_PRIMITIVE_TRIANGLES );
    //Guardamos la info en triangles
    triangulo = esfera.getMesh().getUniqueFaces();
    
    //Normales
    ofVec3f faceNormal;
    
    //PUEDO INDICAR EN QUE LUGAR VA A ESTAR CADA TRIANGULO DE LA ESFERA
    for(int i = 0; i < triangulo.size(); i++ )
    {
        //GUARDO LA NORMAL ACTUAL DE CADA TRIANGULO
        faceNormal = triangulo[i].getFaceNormal();
        
        //RECORRO CADA VERTICE DEL TRIANGULO Y LO REUBICO
        for(int j = 0; j < 3; j++ )
        {
            
            //Explosion
            triangulo[i].setVertex( j, triangulo[i].getVertex(j) + faceNormal * sin( ofRandom(0, 0.5))* 2 );
            
            //Bola de espejo
            //triangles[i].setVertex( j, triangles[i].getVertex(j) + faceNormal * sin( ofNoise(0, 0.5))* 2 );
            
        }
    }
    
    //Nuevas posiciones de los tri‡ngulos
    esfera.getMesh().setFromTriangles( triangulo );
}

/////////////////////////////////////////////////////
void ofEsfera::trans1(vector<ofMeshFace> origenT)
{
    //Cambiamos el modo a dibujo con triangulos para poder actuar sobre los
    //triangulos
    esfera.setMode( OF_PRIMITIVE_TRIANGLES );
    //Guardamos la info en triangles
    triangulo = esfera.getMesh().getUniqueFaces();
    
    
    
    //Normales
    ofVec3f faceNormal2;
    
    //Cambio las posiciones de los tri‡ngulos de la esfera
    for(int i = 0; i < origenT.size(); i++ )
    {
        if (i < orig.size())
        {
        
        
            //Se guarda la normal de cada tri‡ngulo
            faceNormal2 = triangulo[i].getFaceNormal();
        
        
            //Se recorre cada vertice del triangulo y se reubica
            for(int j = 0; j < 3; j++ )
            {
            
            //ofSetColor(255, 255, 255);
            //ofDrawBitmapString(ofToString(plane.getMesh().getVertex(i)), 200*j,10*i);
            //ofNoFill();
            
            
            //triangles[i].setVertex( j, triangles[i].getVertex(j) + (plane.getMesh().getVertex(i) - triangles[i].getVertex(j))*0.01);
            
            
            triangulo[i].setVertex( j, triangulo[i].getVertex(j) + (origenT[i].getVertex(j) - triangulo[i].getVertex(j))*0.01);
            
            
            
            //ofPushMatrix();
            //ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
            //ofRotate(rot);
            
            //ofLine(triangles[i].getVertex(j),original2[i].getVertex(j));
            //ofPopMatrix();
            }
        }
    }
    
    //SETEO LAS NUEVAS POSICIONES DE LOS TRIANGULOS
    esfera.getMesh().setFromTriangles(triangulo);
}

/////////////////////////////////////////////////////
void ofEsfera::trans2(vector<ofVec3f> orig)
{
    //Cambiamos el modo a dibujo con triangulos para poder actuar sobre los
    //triangulos
    esfera.setMode( OF_PRIMITIVE_TRIANGLES );
    //esfera.getMesh().setupIndicesAuto();
    esfera.getMesh().getUniqueFaces();

    float vertEsf = esfera.getMesh().getVertices().size();
    float vertPlan = orig.size();
    //Cambio las posiciones de los tri‡ngulos de la esfera
    //for(int i = 0; i < esfera.getMesh().getVertices().size(); i++ )
    
    int j = 0;
    
    //La cuenta para arriba es resolucion de la esfera * 6
    
    //Punta de arriba de la esfera
    for(int i = 0; i < 288; i+=3 )
    {
        j++;
        
            esfera.getMesh().setVertex(i, esfera.getMesh().getVertex(i) + (orig[210*4 + j*2] - esfera.getMesh().getVertex(i))*0.01);
    
            esfera.getMesh().setVertex(i+1, esfera.getMesh().getVertex(i+1) + (orig[210*4 + j*2] - esfera.getMesh().getVertex(i+1))*0.01);
    
            esfera.getMesh().setVertex(i+2, esfera.getMesh().getVertex(i+2) + (orig[210*4 + j*2+2] - esfera.getMesh().getVertex(i+2))*0.01);
    }
    
    j=0;
    
    ////////////////////////////////////////////////////////////////////////////////
    //CENTRO

    //La cuenta para el centro es resolucion esfera * 6 y luego por 3 (limites)
    //Ejemplo: si es 24, desde 144 (resolucion * 6) hasta 432 (lo anterior por 3) en pasos
    //de lo anterior * 2
    
    int r = 1;
    
    for(int k=0; k < 46 ; k++)
    {
   
    for(int i = 288 + k*576; i < 864 + k*576; i+=6 )
    {
        j++;

    //1
    esfera.getMesh().setVertex(i, esfera.getMesh().getVertex(i) + (orig[(r)*210*4+j*2] - esfera.getMesh().getVertex(i))*0.01);
    //2
    esfera.getMesh().setVertex(i+1, esfera.getMesh().getVertex(i+1) + (orig[210*(r*4+4)+j*2] - esfera.getMesh().getVertex(i+1))*0.01);
    //3
    esfera.getMesh().setVertex(i+2, esfera.getMesh().getVertex(i+2) + (orig[(r)*210*4+j*2+2] - esfera.getMesh().getVertex(i+2))*0.01);
    
    //4
    esfera.getMesh().setVertex(i+3, esfera.getMesh().getVertex(i+3) + (orig[(r)*210*4+j*2+2] - esfera.getMesh().getVertex(i+3))*0.01);
    //5
    esfera.getMesh().setVertex(i+4, esfera.getMesh().getVertex(i+4) + (orig[210*(r*4+4)+j*2] - esfera.getMesh().getVertex(i+4))*0.01);
    //6
    esfera.getMesh().setVertex(i+5, esfera.getMesh().getVertex(i+5) + (orig[210*(r*4+4)+j*2+2] - esfera.getMesh().getVertex(i+5))*0.01);
        
    }
        
        r = r + 1;
       
        j=0;
    
   
    }
    
    
///////////////////////////////////////////////////////////////////////////
    
    for(int i = 26784; i < 27072; i+=3 )
    {
        j++;
    esfera.getMesh().setVertex(i, esfera.getMesh().getVertex(i) + (orig[210*4*47+j*2] - esfera.getMesh().getVertex(i))*0.01);
 
    esfera.getMesh().setVertex(i+1, esfera.getMesh().getVertex(i+1) + (orig[210*4*47+j*2] - esfera.getMesh().getVertex(i+1))*0.01);
   
    esfera.getMesh().setVertex(i+2, esfera.getMesh().getVertex(i+2) + (orig[210*4*47+j*2+2] - esfera.getMesh().getVertex(i+2))*0.01);
    

    }
    j=0;
    
    /////////////////////////////////////////
    
}
/////////////////////////////////////////////////////
void ofEsfera::trans3(vector<ofVec3f> orig)
{
    
    
    //Cambiamos el modo a dibujo con triangulos para poder actuar sobre los
    //triangulos
    esfera.setMode( OF_PRIMITIVE_TRIANGLES );
    
    //float vertEsf = esfera.getMesh().getVertices().size();
    //float vertPlan = orig.size();
    //Cambio las posiciones de los tri‡ngulos de la esfera
    //for(int i = 0; i < esfera.getMesh().getVertices().size(); i++ )
    
    
    /////////////////////////////////////////////////////////////////////////
    //PLANO OSCILANTE
    //Cambio los vertices a partir del agregado de ruido en un loop anidado
	for (int y=0; y<210; y++)
    {
		for (int x=0; x<210; x++)
        {
            //Indice de los vertices, igual que antes
			int i = x + 210 * y;
            //Obtengo el vertice
			ofPoint p = esfera.getMesh().getVertex( i );
            
            //Podemos agregar una respuesta senoidal al cambio de las coordenadas x e y.
            float value = ofNoise( sin(time1*0.01)*x * 0.05, sin(time1*0.01)*y * 0.05, time1*0.5 );
            
			//Cambio la coordenada Z de los vertices mediante
            //value, pero puedo amplificar la profundidad
            p.z = value*20;

			esfera.getMesh().setVertex(i, p);
		}
	}
    
    
    ////////////////////////////////////////////////////
    /*
    for(int i = 0; i < vertEsf; i++ )
    {
        ofPoint p = esfera.getMesh().getVertex( i );
       // if (i < vertPlan)
       // {
            //TRANSFORMACION EN ALEATORIO
            //esfera.getMesh().setVertex(i, esfera.getMesh().getVertex(i) + (orig[ofRandom(0,vertPlan)] - esfera.getMesh().getVertex(i))*0.01);
        
            //MOVIMIENTO OSCILATORIO TOTAL
            //esfera.getMesh().setVertex(i, esfera.getMesh().getVertex(i)+sin(time1*30));

        
        float value = ofNoise( sin(time1*0.1)*i * 0.005, sin(time1*0.1)*i * 0.005, time1*0.05 );
        
        p.z = value*200;
        
        esfera.getMesh().setVertex(i, p);
        
       // }
    }
    */
    
}


