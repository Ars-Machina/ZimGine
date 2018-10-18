#ifndef MODEL_H
#define MODEL_H

#include "..\Mesh\Mesh.h"
using namespace Assimp;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model {
public:
	Model(const char* path);
	Model(const char* path, double size, vec3 position);
	~Model();
	void Draw(Shader shader);
	void setPositionX(float newX);
	void setPositionY(float newy);
	void setPositionZ(float newZ);
	vec3 getPosition();
	void setSize(double newSize);
	double getSize();
	vector<Mesh> getMeshes();
	Mesh getMesh();
private:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	vec3 position;
	double size;
	Mesh modelMesh;
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif