#type vertex
#version 330 core
			
layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Normal;
layout(location=2) in vec2 a_TexCoord;
			
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
	v_Position = a_Position;
	v_Normal = a_Normal;	// TODO
	v_TexCoord = a_TexCoord;
	gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core
			
layout(location=0) out vec4 color;
			
uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}