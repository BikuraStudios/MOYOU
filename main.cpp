#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Sprites.hpp"



//=============================================
//--------------STRUCTS------------------------
//=============================================

struct ParallaxLayer
{
    sf::Sprite sprite;
    float offset = 0.0f;
    float speed = 0.0f;
    float resetThreshhold = 1922.0f;

    ParallaxLayer(const sf::Texture& texture, float speed, float resetThreshhold = 1922.0f)
        : sprite(texture), speed(speed), resetThreshhold(resetThreshhold)
    {
    }

    void update(float deltaTime)
    {
        if (offset > -resetThreshhold)
            offset -= speed * deltaTime;
        if (offset <= -resetThreshhold)
            offset = 0.0f;

        sprite.setPosition(sf::Vector2(offset, 0.0f));
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

//===========================================================================
//------------------------STATES---------------------------------------------
//===========================================================================
bool startUpState{ 0 };
bool startMenuState{ 1 };
bool mainGameState{ 0 };



//===========================================================================
//------------------------VARIABLES------------------------------------------
//===========================================================================

ParallaxLayer parallaxClouds(texture_clouds, 30.0f);
ParallaxLayer parallaxCloudsTwo(texture_cloudsTwo, 75.0f);
ParallaxLayer parallaxBackCheck(texture_checkBack, 125.0f);

bool startQuit{ 0 };


//===========================================================================
//------------------------FUNCIONS-------------------------------------------
//===========================================================================


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1915u, 1075u }), "MOYOU");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1925.f, 1085.f }));
//---------------------------------------------------------------------------
    sf::Clock clock;
 //---------------------------------------------------------------------------



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
               
//--------------------------Start-Logo------------------------------------------------


//-------------------------/Start-Logo------------------------------------------------
//====================================================================================
//--------------------------Start-Menu------------------------------------------------                
                if (startMenuState){
                if ((keyPressed->scancode == sf::Keyboard::Scancode::Up) || (keyPressed->scancode == sf::Keyboard::Scancode::Down)){
                    startQuit = !startQuit;
                    std::cout << startQuit << "\n";
                }
                if ((keyPressed->scancode == sf::Keyboard::Scancode::Enter)) {
                    if (!startQuit) {
                        mainGameState = 1;
                        startMenuState = 0;
                    }
                    else {
                        window.close();
                    }
                }
                }
//---------------------------/Start-Menu-----------------------------------------------
//====================================================================================
//---------------------------Main-Game-----------------------------------------------
// 
//--------------------------/Main-Game-----------------------------------------------

                
            
            }
            if (event->is<sf::Event::Resized>())
            {
                sf::FloatRect viewport;
                sf::Vector2u size = window.getSize();
                auto [windowWidth, windowHeight] = size;
                float aspectRatio = windowWidth / windowHeight;
                float targetRatio{ 16.f / 9.f };


                if (aspectRatio > targetRatio)
                {
                    // Window is too wide — horizontal letterboxing
                    float width = targetRatio / aspectRatio;
                    viewport = sf::FloatRect({ ((1.f - width) / 2.f), 0.f }, { width, 1.f });
                }
                else
                {
                    // Window is too tall — vertical letterboxing
                    float height = aspectRatio / targetRatio;
                    viewport = sf::FloatRect({ 0.f, ((1.f - height) / 2.f) }, { 1.f, height });
                }

                gameView.setViewport(viewport);
            }
//---------------------------------------------------------------------------------------------------------------

            
//---------------------------------------------------------------------------------------------------------------
        }
        float deltaTime = clock.restart().asSeconds();
        parallaxClouds.update(deltaTime);
        parallaxBackCheck.update(deltaTime);
        parallaxCloudsTwo.update(deltaTime);

        window.setView(gameView);
        window.clear();

        //--------------------STARTUP------------------------------------------------------------------------------
        
        if (startMenuState) {
        parallaxBackCheck.draw(window);
        window.draw(titleScreen);
        startHighlight.setPosition({ 790.f,590.f });
        quitHighlight.setPosition({ 790.f,765.f });

        if (!startQuit) {            
            window.draw(startHighlight);
        }
        else {
            window.draw(quitHighlight);
        }
        }

        //-----------------Main-Game---------------------------------------------------------------------------------
        if (mainGameState){
        parallaxClouds.draw(window);
        parallaxCloudsTwo.draw(window);
        window.draw(gameBoard);
        }

        window.display();
    }
}
