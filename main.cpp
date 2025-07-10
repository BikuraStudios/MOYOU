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
    float x;
    float y;
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

bool debug{ 1 };

//===========================================================================
//------------------------VARIABLES------------------------------------------
//===========================================================================

ParallaxLayer parallaxClouds(texture_clouds, 30.0f);
ParallaxLayer parallaxCloudsTwo(texture_cloudsTwo, 75.0f);
ParallaxLayer parallaxBackCheck(texture_checkBack, 125.0f);

bool startQuit{ 0 };
std::vector<Tiles> tilelist;
int selectorCurrentIndex{ 27 };
int swapIndex{ 64 };

std::vector<Coordinates> coordlist = {};
std::vector<int> matchlistvert = {};
std::vector<int> matchlisthorz = {};

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


void generateCoordlist() {
    coordlist.clear();
    for (float y = 60; y <= 900; y += 120) {
        for (float x = 480; x <= 1320; x += 120) {
            coordlist.push_back({ x, y });
        }
    }
}


void initTiles() {
    tilelist.clear();
    int currentTileIndex = 0;
    int prevTile = -1;
    int prePrevTile = -2;
    int prev8Tile = -8;
    int prev16Tile = -16;
    
    for (float y = 60; y <= 900; y += 120) {
        for (float x = 480; x <= 1320; x += 120) {

            Coordinates coord = { x, y };
            if (currentTileIndex - 8 >= 0) {
                prev8Tile = tilelist[currentTileIndex - 8].type;
                if (currentTileIndex - 16 >= 0) {
                    prev16Tile = tilelist[currentTileIndex - 8].type;
                }
            }
            if ((prevTile != prePrevTile) && (prev8Tile != prev16Tile)) {
            tilelist.emplace_back(tileGenerator(coord));

            prePrevTile = prevTile;
            prevTile = tilelist[currentTileIndex].type;
            
            currentTileIndex += 1;
            

            }
            if ((prevTile == prePrevTile) || (prev8Tile == prev16Tile)) {
                tilelist.emplace_back(tileGenerator(coord));
                while (tilelist[currentTileIndex].type == prevTile) {
                    tilelist.pop_back();
                    tilelist.emplace_back(tileGenerator(coord));
                }
                while (tilelist[currentTileIndex].type == prev8Tile) {
                    tilelist.pop_back();
                    tilelist.emplace_back(tileGenerator(coord));
                }
                prePrevTile = prevTile;
                prevTile = tilelist[currentTileIndex].type;
                currentTileIndex += 1;
                
            }
        }
    }
}

void tilelistValidate() {
    while (tilelist.size() > 64){
        tilelist.pop_back();
    }
}

void drawTiles(sf::RenderWindow& window, const std::vector<Tiles>& tiles)
{
    for (const Tiles& tile : tiles) {
        
        window.draw(tile.sprite);
    }
}

void moveSelector(int direction) {
    //------------(up)----------------------(-8)---------
    //----(left)----------(right)-----(-1)------------(1)                
    //-----------(down)----------------------(8)--------
    if (direction == (-8)) {
        if (selectTile.getGlobalBounds().position.y > 180) {
            selectTile.setPosition({ selectTile.getGlobalBounds().position.x, selectTile.getGlobalBounds().position.y - 120 });
            selectorCurrentIndex += direction;
        }
    }
    if (direction == (8)) {
        if (selectTile.getGlobalBounds().position.y < 880) {
            selectTile.setPosition({ selectTile.getGlobalBounds().position.x, selectTile.getGlobalBounds().position.y + 120 });
            selectorCurrentIndex += direction;

        }
    }
    if (direction == (1)) {
        if (selectTile.getGlobalBounds().position.x < 1320) {
            selectTile.setPosition({ selectTile.getGlobalBounds().position.x + 120, selectTile.getGlobalBounds().position.y });
            selectorCurrentIndex += direction;

        }
    }
    if (direction == (-1)) {
        if (selectTile.getGlobalBounds().position.x > 600) {
            selectTile.setPosition({ selectTile.getGlobalBounds().position.x - 120, selectTile.getGlobalBounds().position.y });
            selectorCurrentIndex += direction;

        }
    }
}

void placeHolder(float position) {
    targetTile.setPosition({ selectTile.getPosition().x,selectTile.getPosition().y});
}

void tileSwap(int selector, int swaptile) {
    std::swap(tilelist[selector], tilelist[swaptile]);
    tilelist[selector].coord.x = coordlist[selector].x;
    tilelist[selector].coord.y = coordlist[selector].y;
    tilelist[swaptile].coord.x = coordlist[swaptile].x;
    tilelist[swaptile].coord.y = coordlist[swaptile].y;
    tilelist[selector].sprite.setPosition({tilelist[selector].coord.x, tilelist[selector].coord.y});
    tilelist[swaptile].sprite.setPosition({ tilelist[swaptile].coord.x, tilelist[swaptile].coord.y });
    

}



int matchRecursionUp(int index) {
    matchlistvert.emplace_back(index);
    if (index - 8 < 0) {
        return 0;
    }
    if (tilelist[index].type != tilelist[index - 8].type) {
        return 0;
    }
    else {
        matchRecursionUp(index - 8);
        return 0;
    }
}

int matchRecursionRight(int index) {
    matchlisthorz.emplace_back(index);
    if ((index + 1 == 8) || (index + 1 == 16) || (index + 1 == 24) || (index + 1 == 32) || (index + 1 == 40) || (index + 1 == 48) || (index + 1 == 56) || (index + 1 == 64)) {
        return 0;
    }
    if (tilelist[index].type != tilelist[index + 1].type) {
        return 0;
    }
    else {
        matchRecursionRight(index + 1);
        return 0;
    }
}

int matchRecursionDown(int index) {
    matchlistvert.emplace_back(index);
    if (index + 8 > 63) {
        return 0;
    }
    if (tilelist[index].type != tilelist[index + 8].type) {
                return 0;
            }
    else {
        matchRecursionDown(index + 8);
        return 0;
            }
        }

int matchRecursionLeft(int index) {
    matchlisthorz.emplace_back(index);
    if ((index - 1 == -1) || (index - 1 == 7) || (index - 1 == 15) || (index - 1 == 23) || (index - 1 == 31) || (index - 1 == 39) || (index - 1 == 47) || (index - 1 == 55)) {
        return 0;
    }
    if (tilelist[index].type != tilelist[index - 1].type) {
        return 0;
    }
    else {
        matchRecursionLeft(index - 1);
        return 0;
    }
}
        
void erase3(std::vector <int> matchlist) {
    for (int i = 0; i < matchlist.size(); i++) {
        tilelist.erase(tilelist.begin() + matchlist[i]);
        tilelist.insert(tilelist.begin() + matchlist[i], tileGenerator(coordlist[matchlist[i]]));
    }
}


void match3check(int index) {
    matchlistvert.clear();
    matchlisthorz.clear();
    matchRecursionUp(index);
    matchRecursionDown(index);
    std::sort(matchlistvert.begin(), matchlistvert.end());
    auto last = std::unique(matchlistvert.begin(), matchlistvert.end());
    matchlistvert.erase(last, matchlistvert.end());
    matchRecursionRight(index);
    matchRecursionLeft(index);
    std::sort(matchlisthorz.begin(), matchlisthorz.end());
    auto final = std::unique(matchlisthorz.begin(), matchlisthorz.end());
    matchlisthorz.erase(final, matchlisthorz.end());
    
    if (matchlisthorz.size() >= 3) {
        erase3(matchlisthorz);
    }
    if (matchlistvert.size() >= 3) {
        erase3(matchlistvert);
    }

}




void setTiles() {
    for (int i = 0; i < coordlist.size();i++) {
        tilelist[i].coord.x = coordlist[i].x;
        tilelist[i].coord.y = coordlist[i].y;
        tilelist[i].sprite.setPosition({ coordlist[i].x, coordlist[i].y });
    }
    
}

void AlwaysBeChecking() {
    for (int i = 0; i < 63; i++) {
        match3check(i);

    }
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "MOYOU");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));
    selectTile.setPosition({ 841,421 });
//---------------------------------------------------------------------------
    sf::Clock clock;
    srand(time(0));
    generateCoordlist();
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
                    tilelistValidate();
                    setTiles();
                    AlwaysBeChecking();
                }
                if ((keyPressed->scancode == sf::Keyboard::Scancode::P)) {
                    int countup = 0;
                    for (const auto& s : tilelist) {
                        
                        std::cout << "Index "<< countup << " Type: " << s.type << std::endl;
                        countup += 1;
                    }
                }

                //===================SELECTOR-MOVEMENT=================================
                // ------------PRE-SELECTION-------------------------------------------
                if ((swapIndex == 64) || (swapIndex == selectorCurrentIndex)) {
                    if ((keyPressed->scancode == sf::Keyboard::Scancode::Up)) {
                        moveSelector(-8);
                    }
                    if ((keyPressed->scancode == sf::Keyboard::Scancode::Down)) {
                        moveSelector(8);
                    }
                    if ((keyPressed->scancode == sf::Keyboard::Scancode::Right)) {
                        moveSelector(1);
                    }
                    if ((keyPressed->scancode == sf::Keyboard::Scancode::Left)) {
                        moveSelector(-1);
                    }
                    if (swapIndex == 64) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::A)) {
                            placeHolder(selectorCurrentIndex);
                            swapIndex = selectorCurrentIndex;
                        }
                    }
                    if (swapIndex != 64) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::B)) {
                            swapIndex = 64;
                        }
                    }
                }
                // -------------SELECTION-------------------------------------------
                if ((swapIndex != selectorCurrentIndex) && (swapIndex < 64) ) {
                    if (swapIndex != 64) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::B)) {
                            swapIndex = 64;
                        }
                    }
                    if (swapIndex == (selectorCurrentIndex - 8)) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::Up)) {
                            moveSelector(-8);
                        }

                    }
                    if (swapIndex == (selectorCurrentIndex + 8)) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::Down)) {
                            moveSelector(8);
                        }
                    }
                    if (swapIndex == (selectorCurrentIndex - 1)) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::Left)) {
                            moveSelector(-1);
                        }
                    }
                    if (swapIndex == (selectorCurrentIndex + 1)) {
                        if ((keyPressed->scancode == sf::Keyboard::Scancode::Right)) {
                            moveSelector(1);
                        }
                    }
                    if ((keyPressed->scancode == sf::Keyboard::Scancode::A)) {
                        
                        tileSwap(selectorCurrentIndex, swapIndex);


                        match3check(selectorCurrentIndex);
                        for (const auto& num : matchlisthorz) {
                            std::cout << "Horizontal Matching Tiles: Selector:  " << num << "\n";
                        }
                        for (const auto& num : matchlistvert) {
                            std::cout << "Vertical Matching Tiles: Selector:  " << num << "\n";
                        }
                        match3check(swapIndex);
                        for (const auto& num : matchlisthorz) {
                            std::cout << "Horizontal Matching Tiles: Swapped Tile:  " << num << "\n";
                        }
                        for (const auto& num : matchlistvert) {
                            std::cout << "Vertical Matching Tiles: Swapped Tile:  " << num << "\n";
                        }
                        setTiles();
                        swapIndex = 64;
                    }
                        


                }
                std::cout << "Selector Current Index: " << selectorCurrentIndex << "\n";
                std::cout << "Swap Index: " << swapIndex << "\n";
                
                //===================/SELECTOR-MOVEMENT=================================

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
        if ((swapIndex < 64) && (swapIndex!=selectorCurrentIndex)){
            window.draw(targetTile);
        }
        window.draw(selectTile);

        }


        window.display();
    }
}
