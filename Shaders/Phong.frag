#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 uViewPos;

out vec4 FragColor;

void main()
{
	vec3 lightPos = vec3(500.0, 400.0, 300.0);
	vec3 objectColor = vec3(1.0, 0.0, 0.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = 0.1;
	vec3 ambient = lightColor * ambientStrength;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(FragPos - lightPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * diff;
	
	vec3 viewDir = normalize(FragPos - uViewPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
	vec3 result = objectColor * (ambient + diffuse + spec);
	FragColor = vec4(result, 1.0);
}