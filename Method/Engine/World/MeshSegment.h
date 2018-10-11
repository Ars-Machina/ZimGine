#ifndef MESHSEGMENT_H
#define MESHSEGMENT_H

#include "../Mesh/Mesh.h"
#include "../Model/Model.h"

class MeshSegment {
public:
	MeshSegment(vec3 pos);
	~MeshSegment();
	void Draw(Shader* shader);
	vector<Vertex> getVert();
	vector<unsigned int> getIndex();
	vector<Texture> getTex();
private:
	void setupMesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	vec3 position;
};

#endif