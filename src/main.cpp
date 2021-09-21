#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include<Renderer.h>
using namespace sf;
int main()
{
    ContextSettings ctxSettings;
    ctxSettings.antialiasingLevel = 1;
    ctxSettings.depthBits = 24;
    ctxSettings.majorVersion = 3;
    ctxSettings.minorVersion = 3;
    ctxSettings.stencilBits = 0;
    Window window(VideoMode(1280, 720), "mirror-example", Style::Close, ctxSettings);
    window.setPosition(Vector2i(75, 0));
    Renderer::instance().init();
    while (1)
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                return 0;
                break;
            default:
                break;
            }
        }
        Renderer::instance().render();
        window.display();
    }
    Renderer::instance().terminate();
}