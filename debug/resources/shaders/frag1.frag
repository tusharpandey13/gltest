#version 330 core
out vec4 FragColor;

//────INs───────────────────────────────────────────────────────────────────────────────────────────
//in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

//────FEILDS────────────────────────────────────────────────────────────────────────────────────────
struct PointLightInfo {
	bool islight;
	vec3 position;
	vec3 color;
	float ambient;
	float diffuse;
	float specular;
};


struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	//float gloss;
};

vec3 calcpointlighting(int LightIndex);

//────UNIFORMS──────────────────────────────────────────────────────────────────────────────────────
uniform vec3 camerapos;
#define NR_POINT_LIGHTS __nrpointlights__
uniform PointLightInfo pointlights[NR_POINT_LIGHTS];
uniform int lightindex;
uniform Material material;

//────FUNCTS────────────────────────────────────────────────────────────────────────────────────────

void main(){
	if(pointlights[lightindex].islight == true){
		FragColor = vec4(pointlights[lightindex].color, 1.0);
	}
	else{
		if(texture(material.emission, TexCoord).rgb == vec3(0.0)){
			int i = 0;
			vec3 tmpc = vec3(0.0);
			for(i; i < NR_POINT_LIGHTS; i++){
				tmpc += calcpointlighting(i);
			}
			FragColor = vec4(tmpc, 1.0);
		}
		else{
			FragColor = vec4(texture(material.emission, TexCoord).rgb, 1.0);
		}
	}
}


vec3 calcpointlighting(int LightIndex){
	vec3 lightDir = normalize(pointlights[LightIndex].position - FragPos);
	vec3 viewDir = normalize(camerapos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);

	float diff = max(dot(Normal, lightDir), 0.0); //diffuse
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32/*material.gloss*/);

	vec3 ambient = pointlights[LightIndex].ambient * pointlights[LightIndex].color
													* texture(material.diffuse, TexCoord).rgb;
	vec3 diffuse = pointlights[LightIndex].diffuse * pointlights[LightIndex].color * diff
													* texture(material.diffuse, TexCoord).rgb;
	vec3 specular = pointlights[LightIndex].specular * pointlights[LightIndex].color * spec
													* texture(material.specular, TexCoord).rgb;



	return (ambient + diffuse + specular);

}
