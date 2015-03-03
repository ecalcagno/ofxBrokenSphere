//Version 1.2 de GLSL
#version 120
//Algunas características especiales de  la GPU
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

//Con esta linea indicamos que los
//shaders utilizarán algún tipo de
//textura texture0
uniform sampler2DRect texture0;

void main(){
    //aloja la coordenada del pixel actual
    //de la textura.
	vec2 pos = gl_TexCoord[0].xy;

	//Luego toma el color de ese pixel de la
    //textura
	vec4 color = texture2DRect(texture0, pos);

    //Setea el color del fragment shader y
    //lo devuelve
	gl_FragColor = color;
}
