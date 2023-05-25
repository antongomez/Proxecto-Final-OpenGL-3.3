#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

// Punto de vista do espectador
uniform vec3 viewPos;

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
uniform SpotLight spotLight;

// Variables para usar ou non distintos tipos de luz
uniform int spot;

// Variable para a tetxura
uniform sampler2D texture0;

// Funcion que calcula o efecto da luz direccional
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
// Funcion que calcula o efecto dos focos de luz
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() 
{

    // Calculamos a direccion dende a que ve o espectador a escena
    vec3 viewDir = normalize(viewPos - FragPos);

    // definimos unha cor de saida
    vec3 saida = vec3(0.0);

    // add the directional light's contribution to the output
    saida += CalcDirLight(dirLight, Normal, viewDir);

    if(spot == 1) {
        saida += CalcSpotLight(spotLight, Normal, FragPos, viewDir);
    }
    
    FragColor = vec4(saida, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(texture0, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture0, TexCoord));
    return (ambient + diffuse);
}  

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{

    vec3 diffuse  = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec3 lightDir = normalize(fragPos - light.position);
    float theta = dot(lightDir, normalize(light.direction));
    
    if(theta > light.outerCutOff) 
    {       
        // diffuse shading
        float diff = max(dot(normal, -lightDir), 0.0);

        diffuse  += light.diffuse  * diff * vec3(texture(texture0, TexCoord));

        // Comprobamos se o fragmento se atopa entre o innerCutOff e o outrerCutOff
        if(theta < light.innerCutOff)
        {
            float intensity = clamp((theta - light.outerCutOff)/(light.innerCutOff - light.outerCutOff), 0.0, 1.0);
            diffuse *= intensity;
        }
    }

    return (diffuse);
} 