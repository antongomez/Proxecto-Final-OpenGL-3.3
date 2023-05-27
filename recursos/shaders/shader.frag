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
#define NR_SPOT_LIGHTS 2
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

// Propiedades do obxecto
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

// Variables para usar ou non distintos tipos de luz
uniform int spot;

// Funcion que calcula o efecto da luz direccional
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
// Funcion que calcula o efecto dos puntos de luz
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
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

    // do the same for all point lights
    //for(int i = 0; i < nr_of_point_lights; i++) {
        //saida += CalcPointLight(pointLights[i], Normal, FragPos, viewDir);
        //}

    if(spot == 1) {
        for(int i = 0; i < NR_SPOT_LIGHTS; i++) {
            saida += CalcSpotLight(spotLights[i], Normal, FragPos, viewDir);
        }
    }
    
    FragColor = vec4(saida, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
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
        // specular shading
        vec3 reflectDir = reflect(lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        diffuse  += light.diffuse  * diff * material.diffuse;
        specular += light.specular * spec * material.specular;

        // Comprobamos se o fragmento se atopa entre o innerCutOff e o outrerCutOff
        if(theta < light.innerCutOff)
        {
            float intensity = clamp((theta - light.outerCutOff)/(light.innerCutOff - light.outerCutOff), 0.0, 1.0);
            diffuse *= intensity;
            specular *= intensity;
        }
    }

    return (diffuse + specular);
} 