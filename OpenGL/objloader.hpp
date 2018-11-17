#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
//#include <glm/glm.hpp>
#include "Angel.h"

enum {
	Torso = 0,
	RightUpperArm = 1,
	RightLowerArm = 2,
	LeftUpperArm = 3,
	LeftLowerArm = 4,
	Head = 5,
	Head1 = 5,
	RightUpperLeg = 6,
	RightLowerLeg = 7,
	LeftUpperLeg = 8,
	LeftLowerLeg = 9,
	
	Head2 = 10,
	Gun = 11,
	NumNodes,
	Quit
};

bool loadEnemyOBJ(
	const char *path,
	std::vector<vec3> *out_vertices,
	std::vector<vec4> *out_colors
);
bool loadGunOBJ(
	const char *path,
	std::vector<vec3> *out_vertices,
	std::vector<vec4> *out_colors
);
bool loadCubeOBJ(
	int mode,
	const char *path,
	std::vector<vec3> *out_vertices,
	std::vector<vec4> *out_colors
);
bool loadDummyOBJ(
	int mode,
	const char * path,
	std::vector<vec3> *out_vertices,
	std::vector<vec4> *out_colors

);

#endif