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