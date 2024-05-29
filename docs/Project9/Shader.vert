#version 330 core
layout (location = 0) in vec3 aPos;   // position attribute 0
layout (location = 1) in vec3 aColor; // color attribute 1
out vec3 ourColor; // output a color to the fragment shader

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}
