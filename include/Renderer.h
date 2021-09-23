#pragma once
#include <GL/glew.h>
#include <vector>
#include <assert.h>
#include <Mesh.h>
#include <Shader.h>
class Renderer
{
private:
    std::vector<Mesh> meshes;
    Mesh *mirror;
    GLuint mirrorTex, mirrorFb,mirrorRb;
    Shader mainShader, mirrorShader;
    glm::vec3 camPosition, camView;
    glm::vec3 mirrorPosition, mirrorNormal;
    float downScaleFactor;
    Renderer();

public:
    static Renderer &instance();
    void init();
    void render();
    void translateCamera(glm::vec3 pos);
    void terminate();
};