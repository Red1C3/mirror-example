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
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <Renderer.h>
using namespace sf;
using namespace glm;
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
    float speed = 1.0f;
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
            case Event::KeyPressed:
                if (event.key.code == Keyboard::W)
                {
                    Renderer::instance().translateCamera(vec3(0, 0, speed));
                }
                if (event.key.code == Keyboard::S)
                {
                    Renderer::instance().translateCamera(vec3(0, 0, -speed));
                }
                if (event.key.code == Keyboard::D)
                {
                    Renderer::instance().translateCamera(vec3(-speed, 0, 0));
                }
                if (event.key.code == Keyboard::A)
                {
                    Renderer::instance().translateCamera(vec3(speed, 0, 0));
                }
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