#include <Renderer.h>
#define MIRRORMAP 1024
using namespace std;
using namespace glm;
Renderer::Renderer() {}
Renderer &Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}
void Renderer::init()
{
    glewExperimental = true;
    int err = glewInit();
    assert(err == GLEW_OK);
    glEnable(GL_DEPTH_TEST);
    glGenTextures(1, &mirrorTex);
    glBindTexture(GL_TEXTURE_2D, mirrorTex);
    glTextureParameteri(mirrorTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(mirrorTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, MIRRORMAP, MIRRORMAP, 0, GL_RGBA, GL_FLOAT, nullptr);
    glGenFramebuffers(1, &mirrorFb);
    glBindFramebuffer(GL_FRAMEBUFFER, mirrorFb);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mirrorTex, 0);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    meshes.push_back(Mesh("./Assets/Cube.glb", vec3(2, 0, 0)));
    mirror = new Mesh("./Assets/Mirror.glb", vec3(0, 0, 2));
    camLocation = vec3(0, 0, -10);
    camView = vec3(0, 0, 2);
    mainShader = Shader("./Assets/mainShader.vert", "./Assets/mainShader.frag");
    mainShader.registerUniform("MVP");
    mainShader.registerUniform("isMirror");
    assert(glGetError() == 0);
}
void Renderer::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(mainShader.id);
    mat4 perspectiveMat = perspective(radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    mat4 viewMat = lookAt(camLocation, camView, vec3(0, 1, 0));
    for (Mesh mesh : meshes)
    {
        mainShader.updateUniform("MVP", perspectiveMat * viewMat * mesh.model);
        mesh.draw();
    }
    //mainShader.updateUniform("isMirror", 1);
    mainShader.updateUniform("MVP", perspectiveMat * viewMat * mirror->model);
    mirror->draw();
    mainShader.updateUniform("isMirror", 0);
    assert(glGetError() == 0);
}
void Renderer::terminate()
{
    delete mirror;
    assert(glGetError() == 0);
}