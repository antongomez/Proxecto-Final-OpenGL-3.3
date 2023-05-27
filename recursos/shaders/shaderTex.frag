#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

// Luz direccional: sol
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

// Puntos de luz: emiten luz en todas as direccions
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 1  
uniform PointLight pointLights[NR_POINT_LIGHTS];

// Focos
struct SpotLight {
    vec3  position;
    vec3  direction;
    float innerCutOff;
    float outerCutOff;

    vec3 diffuse;
    vec3 specular;
};    
#define NR_SPOT_LIGHTS 2
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

// Variables para usar ou non distintos tipos de luz
uniform int spot;
// Variable para determinar se estamos iluminando o skyBox
uniform int skyBox;

// Variable para a tetxura
uniform sampler2D texture0;

// Funcion que calcula o efecto da luz direccional
vec3 CalcDirLight(DirLight light, vec3 normal);
// Funcion que calcula o efecto dos focos de luz
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos);

void main() 
{
    // definimos unha cor de saida
    vec3 saida = vec3(0.0);

    // Iluminacion skyBox
    if(skyBox == 1){
        saida = vec3(texture(texture0, TexCoord));
    } else { 
        // add the directional light's contribution to the output
        saida += CalcDirLight(dirLight, Normal);

        if(spot == 1) {
            for(int i = 0; i < NR_SPOT_LIGHTS; i++) {
                saida += CalcSpotLight(spotLights[i], Normal, FragPos);
            }
        }
    }
    
    FragColor = vec4(saida, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(texture0, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture0, TexCoord));
    return (ambient + diffuse);
}  

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos)
{

    vec3 diffuse  = vec3(0.0);

    vec3 lightDir = normalize(fragPos - light.position);
    float theta = dot(lightDir, normalize(light.direction));

    //normal = vec3(0, 1, 0);
    
    if(theta > light.outerCutOff) 
    {       
        // diffuse shading
        float diff = max(dot(normal, -lightDir), 0.0);

        // Axustamos a cor da textura para que destaque mais en comparacion coa iluminacion dos obxectos non texturizados
        diffuse  += light.diffuse  * diff * 10.0f * vec3(texture(texture0, TexCoord));

        // Comprobamos se o fragmento se atopa entre o innerCutOff e o outrerCutOff
        if(theta < light.innerCutOff)
        {
            float intensity = clamp((theta - light.outerCutOff)/(light.innerCutOff - light.outerCutOff), 0.0, 1.0);
            diffuse *= intensity;
        }
    }

    return (diffuse);
} 