#include "Light.h"

unsigned int Light::directional_light_counter = 0;
unsigned int Light::point_light_counter = 0;
unsigned int Light::spot_light_counter = 0;

/* Constructor */
Light::Light()
{
}

/* De-constructor */
Light::~Light()
{
}

Light::Type Light::getType()
{
	return type;
}

bool Light::is(Type type)
{
	return (this->type == type);
}

void Light::enable()
{
	enabled = true;
	switch (type)
	{
	case DIRECTIONAL:
		++directional_light_counter;
	case POINT:
		++point_light_counter;
	case SPOT:
		++spot_light_counter;
	}

}

void Light::disable()
{
	enabled = false;
	switch (type)
	{
	case DIRECTIONAL:
		--directional_light_counter;
	case POINT:
		--point_light_counter;
	case SPOT:
		--spot_light_counter;
	}
}

bool Light::isEnabled() {
	return enabled;
}

bool Light::drawLight(const Shader * shader)
{
	if (shader == nullptr)
		return false;

	if (is(DIRECTIONAL) && enabled)
	{
		shader->setVec3("directionalLights[" + std::to_string(id) + "].direction", direction);
		shader->setVec3("directionalLights[" + std::to_string(id) + "].ambient", vec3::scale(color, ambient));
		shader->setVec3("directionalLights[" + std::to_string(id) + "].diffuse", vec3::scale(color, diffuse));
		shader->setVec3("directionalLights[" + std::to_string(id) + "].specular", vec3::scale(color, specular));
		return true;
	}
	else if (is(DIRECTIONAL) && !enabled)
	{
		shader->setVec3("directionalLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader->setVec3("directionalLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader->setVec3("directionalLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	else if (is(POINT) && enabled)
	{
		shader->setVec3("pointLights[" + std::to_string(id) + "].position", position);
		shader->setVec3("pointLights[" + std::to_string(id) + "].ambient", vec3::scale(color, ambient));
		shader->setVec3("pointLights[" + std::to_string(id) + "].diffuse", vec3::scale(color, diffuse));
		shader->setVec3("pointLights[" + std::to_string(id) + "].specular", vec3::scale(color, specular));
		shader->setFloat("pointLights[" + std::to_string(id) + "].constant", constant);
		shader->setFloat("pointLights[" + std::to_string(id) + "].linear", linear);
		shader->setFloat("pointLights[" + std::to_string(id) + "].quadratic", quadratic);
		return true;
	}
	else if (is(POINT) && !enabled)
	{
		shader->setVec3("pointLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader->setVec3("pointLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader->setVec3("pointLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	else if (is(SPOT) && enabled)
	{
		if (camera != nullptr)
		{
			shader->setVec3("spotLights[" + std::to_string(id) + "].position", camera->Position);
			shader->setVec3("spotLights[" + std::to_string(id) + "].direction", camera->Front);
		}
		else
		{
			shader->setVec3("spotLights[" + std::to_string(id) + "].position", position);
			shader->setVec3("spotLights[" + std::to_string(id) + "].direction", direction);
		}
		shader->setVec3("spotLights[" + std::to_string(id) + "].ambient", ambient);
		shader->setVec3("spotLights[" + std::to_string(id) + "].diffuse", diffuse);
		shader->setVec3("spotLights[" + std::to_string(id) + "].specular", specular);
		shader->setFloat("spotLights[" + std::to_string(id) + "].constant", constant);
		shader->setFloat("spotLights[" + std::to_string(id) + "].linear", linear);
		shader->setFloat("spotLights[" + std::to_string(id) + "].quadratic", quadratic);
		shader->setFloat("spotLights[" + std::to_string(id) + "].cutOff", glm::cos(glm::radians(cutOff)));
		shader->setFloat("spotLights[" + std::to_string(id) + "].outerCutOff", glm::cos(glm::radians(outerCutOff)));
		return true;
	}
	else if (is(SPOT) && !enabled)
	{
		shader->setVec3("spotLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader->setVec3("spotLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader->setVec3("spotLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	return false;
}

bool Light::operator==(const Light & right) const
{
	return (this->type == right.type);
}

unsigned int Light::numDirectionalLights()
{
	return directional_light_counter;
}

unsigned int Light::numPointLights()
{
	return point_light_counter;
}

unsigned int Light::numSpotLights()
{
	return spot_light_counter;
}