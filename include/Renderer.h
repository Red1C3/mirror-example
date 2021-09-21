#pragma once
#include <GL/glew.h>
#include <vector>
#include <assert.h>
#include <Mesh.h>
#include<Shader.h>
class Renderer
{
private:
    std::vector<Mesh> meshes;
    Mesh* mirror;
    GLuint mirrorTex, mirrorFb;
    Shader mainShader, mirrorShader;
    glm::vec3 camLocation, camView;
    Renderer();

public:
    static Renderer &instance();
    void init();
    void render();
    void terminate();
};