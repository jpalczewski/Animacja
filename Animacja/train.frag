#version 330 core
in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
out vec4 color;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Material {
	float shininess;
};

uniform Material material;
uniform vec3 viewPos;
uniform Light light;


void main()
{
  color = vec4(ourColor,1.0);
  vec3 ambient = light.ambient * ourColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * ourColor;

	    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * ourColor;
    
    // Attenuation
    float distance2    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance2 + light.quadratic * (distance2 * distance2));    

    ambient  *= attenuation;  
    diffuse  *= attenuation;
    specular *= attenuation;  
	color = vec4(ambient + diffuse + specular, 1.0f);  
}
