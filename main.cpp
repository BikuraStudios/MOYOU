#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Sprites.hpp"
#include <random>



//=============================================
//--------------STRUCTS------------------------
//=============================================

struct Coordinates
{
    int x;
    int y;
};

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

struct Tiles
{
    sf::Sprite sprite;
    Coordinates coord;
    float type;
    

    Tiles(const sf::Sprite& s, Coordinates c, float t)
        : sprite(s), coord(c), type(t)  {
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
std::vector<Tiles> tilelist;

//===========================================================================
//------------------------FUNCIONS-------------------------------------------
//===========================================================================
Tiles tileGenerator(Coordinates coord) {
    int getRandomTile= rand() % 9;
    float generateTileType = 0;
    sf::Sprite generateSprite = purpleTile;
    float generatecoordx = coord.x;
    float generatecoordy = coord.y;

    if (getRandomTile == 0) {
        generateSprite = purpleTile;
        generateTileType = 0;
    }
    if (getRandomTile == 1) {
        generateSprite = brownTile;
        generateTileType = 1;

    }
    if (getRandomTile == 2) {
        generateSprite = tealTile;
        generateTileType = 2;

    }
    if (getRandomTile == 3) {
        generateSprite = orangeTile;
        generateTileType = 3;

    }
    if (getRandomTile == 4) {
        generateSprite = greyTile;
        generateTileType = 4;

    }
    if (getRandomTile == 5) {
        generateSprite = mintTile;
        generateTileType = 5;

    }
    if (getRandomTile == 6) {
        generateSprite = yellowTile;
        generateTileType = 6;

    }
    if (getRandomTile == 7) {
        generateSprite = blackTile;
        generateTileType = 7;

    }
    if (getRandomTile == 8) {
        generateSprite = greenTile;
        generateTileType = 8;

    }
    generateSprite.setPosition({ generatecoordx,generatecoordy });
    return Tiles(generateSprite, coord, generateTileType);
    
}

void initTiles() {
    tilelist.clear();
    int currentTileIndex = 0;
    int prevTile = -1;
    int prePrevTile = -2;
    
    for (int y = 60; y <= 900; y += 120) {
        for (int x = 480; x <= 1320; x += 120) {

            Coordinates coord = { x, y };
            if (prevTile != prePrevTile){
            tilelist.emplace_back(tileGenerator(coord));
            prePrevTile = prevTile;
            prevTile = tilelist[currentTileIndex].type;
            currentTileIndex += 1;
            std::cout << prePrevTile << "\n";
            std::cout << prevTile << "\n";

            }
            if (prevTile == prePrevTile) {
                tilelist.emplace_back(tileGenerator(coord));
                while (tilelist[currentTileIndex].type == prevTile) {
                    tilelist.pop_back();
                    tilelist.emplace_back(tileGenerator(coord));
                }
                prePrevTile = prevTile;
                prevTile = tilelist[currentTileIndex].type;
                currentTileIndex += 1;
                std::cout << prePrevTile << "\n";
                std::cout << prevTile << "\n";
            }
        }
    }
}
void drawTiles(sf::RenderWindow& window, const std::vector<Tiles>& tiles)
{
    for (const Tiles& tile : tilelist) {
        window.draw(tile.sprite);
    }
}


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "MOYOU");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));
//---------------------------------------------------------------------------
    sf::Clock clock;
    srand(time(0));
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
                if ((keyPressed->scancode == sf::Keyboard::Scancode::Enter)) {
                    initTiles();
                }

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
        drawTiles(window, tilelist);
        }


        window.display();
    }
}
