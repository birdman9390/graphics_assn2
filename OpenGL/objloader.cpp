#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

//#include <glm/glm.hpp>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

void InsertVertices(
	int mode,
	int startOffset,
	int indices_size,
	std::vector<vec3> &temp_vertices,
	std::vector<unsigned int> &vertexIndices,
	std::vector<vec3> &out_vertices,
	std::vector<vec4> &out_colors
) {
	for (unsigned int i = startOffset; i<indices_size; i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		if(mode==0)//player
			out_colors.push_back(vec4(0, 0, 1, 1));
		if (mode == 1)
			out_colors.push_back(vec4(1, 0, 0, 1));
	}
}

bool  loadEnemyOBJ(
	const char * path,
	std::vector<vec3> * out_vertices,
	std::vector<vec4> * out_colors
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<vec3> temp_vertices;

	int unit_count = 0;

	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d %d/%d %d/%d/\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1],  &uvIndex[1], &vertexIndex[2],  &uvIndex[2]);
			//if (matches != 6) {
			//	printf("File can't be read by our simple parser :-( Try exporting with other options\n");
			//	fclose(file);
			//	return false;
			//}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else if (strcmp(lineHeader, "s") == 0) {
			if (unit_count == 8)
				break;
			unit_count++;
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];

		// Put the attributes in buffers
		out_vertices[0].push_back(vertex);
		out_colors[0].push_back(vec4(1, 0, 0, 1));


	}
	fclose(file);
	return true;
}
bool loadCubeOBJ(
	int mode,
	const char * path,
	std::vector<vec3> * out_vertices,
	std::vector<vec4> * out_colors
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<vec3> temp_vertices;



	FILE * file;
	fopen_s(&file,path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader,128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];

		// Put the attributes in buffers
		out_vertices[mode].push_back(vertex);
		out_colors[mode].push_back(vec4(0, 0, 0, 1));
	}
	fclose(file);
	return true;
}

bool loadGunOBJ(
	const char * path,
	std::vector<vec3> * out_vertices,
	std::vector<vec4> * out_colors
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<vec3> temp_vertices;

	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];

		// Put the attributes in buffers
		out_vertices[0].push_back(vertex);
		out_colors[0].push_back(vec4(0, 0, 0, 1));
	}
	fclose(file);
	return true;
}
bool loadDummyOBJ(
	int mode,
	const char * path,
	std::vector< vec3> * out_vertices,
	std::vector<vec4> * out_colors
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector< vec3> temp_vertices;
	int indices_size[10];

	int unit_count = 0;
	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader,128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			 vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}

		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else if (strcmp(lineHeader, "g") == 0) {
			if (unit_count == 3) 
				indices_size[Torso] = vertexIndices.size();
			if (unit_count == 5) 
				indices_size[RightUpperArm] = vertexIndices.size();
			if (unit_count == 9)
				indices_size[RightLowerArm] = vertexIndices.size();
			if (unit_count == 11)
				indices_size[LeftUpperArm] = vertexIndices.size();
			if (unit_count == 15)
				indices_size[LeftLowerArm] = vertexIndices.size();
			if (unit_count == 17)
				indices_size[Head] = vertexIndices.size();
			if (unit_count == 19)
				indices_size[RightUpperLeg] = vertexIndices.size();
			if (unit_count == 23)
				indices_size[RightLowerLeg] = vertexIndices.size();
			if (unit_count == 25)
				indices_size[LeftUpperLeg] = vertexIndices.size();
			if (unit_count == 29) {
				indices_size[LeftLowerLeg] = vertexIndices.size();
				break;
			}
			unit_count++;
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle

	
	InsertVertices(mode,0, indices_size[Torso], temp_vertices, vertexIndices, out_vertices[Torso], out_colors[Torso]);
	for (int i = 1; i < 10; i++)
		InsertVertices(mode,indices_size[i - 1], indices_size[i], temp_vertices, vertexIndices, out_vertices[i], out_colors[i]);
	
	fclose(file);
	return true;
}
