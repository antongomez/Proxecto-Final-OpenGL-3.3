#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;   
in vec2 TexCoord;

out vec4 fragColor;

uniform int obxecto_cargado;
uniform vec3 cor_luz;
uniform vec3 cor_obxecto;

void main()
{
	if(obxecto_cargado == 1) {
		fragColor = vec4(cor_obxecto, 1.0f);
	} else {
		fragColor = vec4(Color, 1.0f);
	}
	
}