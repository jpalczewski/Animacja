#version 330 core

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
	sampler2D texture;
	float shininess;
};


in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;
uniform Light light;
uniform Material material; 





void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.texture, TexCoord));
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture, TexCoord));

	    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.texture, TexCoord));
    
    // Attenuation
    float distance2    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance2 + light.quadratic * (distance2 * distance2));    

    ambient  *= attenuation;  
    diffuse  *= attenuation;
    specular *= attenuation;  
	color = vec4(ambient + diffuse + specular, 1.0f);  
 //   color = texture(Texture0, TexCoord);
}
