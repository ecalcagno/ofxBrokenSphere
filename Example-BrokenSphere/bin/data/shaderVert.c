//Version de GLSL
#version 120
//Caracteristicas de texturas y shaders
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

void main() {
    //Se translada la posición del vertice procesado al sistema
    //de coordenadas de la pantalla. En este caso solo se dibuja
    //una imagen en el fbo, por lo que el vertex shader dibuja solo 4 vertices.
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    //Se iguala la coordenada de la textura a la de la imagen
    //que se va a dibujar. Realiza una interpolación entre estos
    //dos elementos.
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
