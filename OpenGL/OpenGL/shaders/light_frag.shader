#version 450 core

	out vec4 FragColor;

	uniform vec3 lightColor;
	uniform bool hasLightColor;

	void main()
	{
		if (hasLightColor) {
			FragColor = vec4(lightColor, 1.0);
		}
		else {
			FragColor = vec4(1.0);
		}
	}