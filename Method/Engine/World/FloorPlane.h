#ifndef FLOORPLANE_H
#define FLOORPLACE_H

#include "../Mesh/Mesh.h"
#include "../Model/Model.h"

class FloorPlane {
public:
	FloorPlane(int size);
	FloorPlane(int size, vec3 position);
	void Draw(Shader* shader);
	void setPos(vec3 newPos);
private:
	void setupMesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	int size;
	vec3 position;
};

#endif