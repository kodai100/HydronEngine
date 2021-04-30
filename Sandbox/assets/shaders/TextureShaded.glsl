#type vertex
#version 330 core
			
layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Normal;
layout(location=2) in vec2 a_TexCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
	v_Position = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	v_Normal =  normalize(a_Normal);
	v_TexCoord = a_TexCoord;
	gl_Position =  u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core
			
layout(location=0) out vec4 color;

uniform mat4 u_InvModelMatrix;			
uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;
uniform vec3 u_CameraPos;
uniform vec4 u_AmbientColor;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

void main()
{

	vec3 eyeDir = normalize(u_CameraPos - v_Position);

	vec3  invLight  = normalize(u_InvModelMatrix * vec4(-u_LightDirection, 0.0)).xyz;
    vec3  invEye    = normalize(u_InvModelMatrix * vec4(eyeDir, 0.0)).xyz;
    vec3  halfLE    = normalize(invLight + invEye);

    float diffuse   = clamp(dot(v_Normal, invLight), 0.0, 1.0);
    float specular  = pow(clamp(dot(v_Normal, halfLE), 0.0, 1.0), 50.0);
    vec4  destColor = texture(u_Texture, v_TexCoord) * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0) + u_AmbientColor;

	color = destColor;
}