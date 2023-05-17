#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;   
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

// Puntos de luz: emiten luz en todas as direccions

// Focos

// Propiedades do obxecto
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

// Funcion que calcula o efecto da luz direccional
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
// Funcion que calcula o efecto dos puntos de luz
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

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

  // and add others lights as well (like spotlights)
  //saida += someFunctionToCalculateSpotLight();
  
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
    vec3 ambient  = light.ambient  * material.diffuse;
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