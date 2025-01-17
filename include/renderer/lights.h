#pragma once
#include <glm/glm.hpp>

#define VECTOR_ZERO glm::vec3(0.f)

struct DirLight {
	glm::vec3 direction = VECTOR_ZERO;

	glm::vec3 ambient = VECTOR_ZERO;
	glm::vec3 diffuse = VECTOR_ZERO;
	glm::vec3 specular = VECTOR_ZERO;
};

struct PointLight {
	bool is_on = false;
	glm::vec3 position = VECTOR_ZERO;

	glm::vec3 ambient = VECTOR_ZERO;
	glm::vec3 diffuse = VECTOR_ZERO;
	glm::vec3 specular = VECTOR_ZERO;

	float constant = 1.f;
	float linear = 1.f;
	float quadratic = 1.f;
};

struct SpotLight {
	bool is_on = false;
	glm::vec3 position = VECTOR_ZERO;
	glm::vec3 direction = VECTOR_ZERO;

	glm::vec3 ambient = VECTOR_ZERO;
	glm::vec3 diffuse = VECTOR_ZERO;
	glm::vec3 specular = VECTOR_ZERO;

	float constant = 1.f;
	float linear = 1.f;
	float quadratic = 1.f;

	float cutOff = 0.f;
	float outerCutOff = 0.f;
};