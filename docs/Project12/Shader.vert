#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 outPosition;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outPosition = aPos;
}
