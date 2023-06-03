#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

// Variable para decidir se se usa textura ou cor
uniform int cor;

// Variable para a tetxura
uniform sampler2D texture0;
// Variable para a cor do obxecto
uniform vec3 color;

void main() 
{
    // definimos unha cor de saida
    vec3 saida = vec3(0.0);

    // Iluminacion skyBox
    if(cor == 1){
        FragColor = vec4(color, 1.0f);
    } else { 
        FragColor = texture(texture0, TexCoord);
    }
}