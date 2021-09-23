/*
MIT License

Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
    glGenRenderbuffers(1, &mirrorRb);
    glBindRenderbuffer(GL_RENDERBUFFER, mirrorRb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, MIRRORMAP, MIRRORMAP);
    glGenFramebuffers(1, &mirrorFb);
    glBindFramebuffer(GL_FRAMEBUFFER, mirrorFb);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mirrorTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mirrorRb);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    camPosition = vec3(0, 0, -10);
    camView = vec3(0, 0, 2);
    mirrorPosition = vec3(0, 0, 2);
    mirrorNormal = vec3(0, 0, -1);
    meshes.push_back(Mesh("./Assets/Cube.glb", vec3(2, 1, 0)));
    mirror = new Mesh("./Assets/Mirror.glb", mirrorPosition);
    mainShader = Shader("./Assets/mainShader.vert", "./Assets/mainShader.frag");
    mainShader.registerUniform("MVP");
    mainShader.registerUniform("isMirror");
    mirrorShader = Shader("./Assets/mirrorShader.vert", "./Assets/mirrorShader.frag");
    mirrorShader.registerUniform("MVP");
    downScaleFactor = 5.0f;
    assert(glGetError() == 0);
}
void Renderer::render()
{
    vec3 camToMirror = mirrorPosition - camPosition;
    float camToMirrorLen = clamp(length(camToMirror), 0.0f, 100.0f) / 100.0f;
    vec3 reflectedCamToMirror = reflect(camToMirror, mirrorNormal);
    float FOV = clamp(((1.0f) / camToMirrorLen - 1) / downScaleFactor, 0.0f, half_pi<float>());
    mat4 perspectiveMat, viewMat;
    /*First Render Pass*/
    perspectiveMat = perspective(FOV, 1.0f, 0.1f, 100.0f);
    viewMat = lookAt(mirrorPosition, reflectedCamToMirror + mirrorPosition, vec3(0, 1, 0));
    glViewport(0, 0, MIRRORMAP, MIRRORMAP);
    glBindFramebuffer(GL_FRAMEBUFFER, mirrorFb);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(mirrorShader.id);
    for (Mesh mesh : meshes)
    {
        mirrorShader.updateUniform("MVP", perspectiveMat * viewMat * mesh.model);
        mesh.draw();
    }
    /*Second Render Pass*/
    glViewport(0, 0, 1280, 720);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(mainShader.id);
    perspectiveMat = perspective(radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    viewMat = lookAt(camPosition, camView, vec3(0, 1, 0));
    for (Mesh mesh : meshes)
    {
        mainShader.updateUniform("MVP", perspectiveMat * viewMat * mesh.model);
        mesh.draw();
    }
    mainShader.updateUniform("isMirror", 1);
    mainShader.updateUniform("MVP", perspectiveMat * viewMat * mirror->model);
    mirror->draw();
    mainShader.updateUniform("isMirror", 0);
    assert(glGetError() == 0);
}
void Renderer::translateCamera(vec3 pos)
{
    camPosition += pos;
    camView += pos;
}
void Renderer::terminate()
{
    glDeleteRenderbuffers(1, &mirrorRb);
    glDeleteTextures(1, &mirrorTex);
    glDeleteFramebuffers(1, &mirrorFb);
    glDeleteProgram(mainShader.id);
    glDeleteProgram(mirrorShader.id);
    delete mirror;
    assert(glGetError() == 0);
}