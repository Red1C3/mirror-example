#include<Renderer.h>
Renderer::Renderer(){}
Renderer& Renderer::instance(){
    static Renderer renderer;
    return renderer;
}
void Renderer::init(){
    glewExperimental = true;
    int err = glewInit();
    assert(err == GLEW_OK);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}
void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}