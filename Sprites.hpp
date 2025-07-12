//=================================================
//--------------------TEXTURES--------------------
//=================================================
sf::Texture texture_atlas("atlas.png");
sf::Texture texture_title("title.png");
sf::Texture texture_gameBoard("gameBoard.png");
sf::Texture texture_checkBack("checkBack.png");
sf::Texture texture_clouds("clouds.png");
sf::Texture texture_cloudsTwo("cloudsTwo.png");
sf::Texture texture_logo("logo.png");
sf::Texture texture_gameOver("gameOver.png");




//=================================================
//  --------------------RECTS--------------------
//=================================================

//--------------------tiles--120x120px--------------------


inline const sf::IntRect purpleTileRect({ 0, 0 }, { 120, 120 });
inline const sf::IntRect brownTileRect({ 120, 0 }, { 120, 120 });
inline const sf::IntRect tealTileRect({ 240, 0 }, { 120, 120 });
inline const sf::IntRect orangeTileRect({ 360, 0 }, { 120, 120 });
inline const sf::IntRect greyTileRect({ 480, 0 }, { 120, 120 });
inline const sf::IntRect mintTileRect({ 600, 0 }, { 120, 120 });
inline const sf::IntRect yellowTileRect({ 720, 0 }, { 120, 120 });
inline const sf::IntRect blackTileRect({ 840, 0 }, { 120, 120 });
inline const sf::IntRect greenTileRect({ 960, 0 }, { 120, 120 });
inline const sf::IntRect whiteTileRect({ 1080, 0 }, { 120, 120 });
inline const sf::IntRect BG1TileRect({ 0, 120 }, { 120, 120 });
inline const sf::IntRect BG2TileRect({ 120, 120 }, { 120, 120 });
inline const sf::IntRect BG3TileRect({ 240, 120 }, { 120, 120 });
inline const sf::IntRect BG4TileRect({ 360, 120 }, { 120, 120 });
inline const sf::IntRect swapTileRect({ 480, 120 }, { 120, 120 });
inline const sf::IntRect targetTileRect({ 600, 120 }, { 120, 120 });
inline const sf::IntRect selectTileRect({ 720, 120 }, { 120, 120 });
inline const sf::IntRect vertTileRect({ 840, 120 }, { 120, 120 });
inline const sf::IntRect horzTileRect({ 960, 120 }, { 120, 120 });
inline const sf::IntRect crossTileRect({ 1080, 120 }, { 120, 120 });
inline const sf::IntRect keyTileRect({ 720,240 }, { 120,120 });
inline const sf::IntRect keyHoleTileRect({ 720,360 }, { 120,120 });

//--------------------controller-mockup--200x200px--------------------
inline const sf::IntRect controllerRect({ 0, 240 }, { 200, 200 });
inline const sf::IntRect confirmRect({ 200, 240 }, { 200, 200 });
inline const sf::IntRect cancelRect({ 400, 240 }, { 200, 200 });

//--------------------start-menu-buttons--339x103px--------------------
inline const sf::IntRect startRect({ 861, 265 }, { 339, 103 });
inline const sf::IntRect quitRect({ 861, 377 }, { 339, 103 });

//----------------------Misc-------------------------------------------
inline const sf::IntRect heartRect({ 600,240 }, { 25,25 });









//=================================================
// --------------------SPRITES--------------------
//=================================================

extern sf::Texture texture_atlas;

//----------------tiles------------------------------------
inline sf::Sprite purpleTile(texture_atlas, purpleTileRect);
inline sf::Sprite brownTile(texture_atlas, brownTileRect);
inline sf::Sprite tealTile(texture_atlas, tealTileRect);
inline sf::Sprite orangeTile(texture_atlas, orangeTileRect);
inline sf::Sprite greyTile(texture_atlas, greyTileRect);
inline sf::Sprite mintTile(texture_atlas, mintTileRect);
inline sf::Sprite yellowTile(texture_atlas, yellowTileRect);
inline sf::Sprite blackTile(texture_atlas, blackTileRect);
inline sf::Sprite greenTile(texture_atlas, greenTileRect);
inline sf::Sprite whiteTile(texture_atlas, whiteTileRect);
inline sf::Sprite BG1Tile(texture_atlas, BG1TileRect);
inline sf::Sprite BG2Tile(texture_atlas, BG2TileRect);
inline sf::Sprite BG3Tile(texture_atlas, BG3TileRect);
inline sf::Sprite BG4Tile(texture_atlas, BG4TileRect);
inline sf::Sprite swapTile(texture_atlas, swapTileRect);
inline sf::Sprite targetTile(texture_atlas, targetTileRect);
inline sf::Sprite selectTile(texture_atlas, selectTileRect);
inline sf::Sprite vertTile(texture_atlas, vertTileRect);
inline sf::Sprite horzTile(texture_atlas, horzTileRect);
inline sf::Sprite crossTile(texture_atlas, crossTileRect);

//---------------controller--------------------------------
inline sf::Sprite controllerSprite(texture_atlas, controllerRect);
inline sf::Sprite confirmSprite(texture_atlas, confirmRect);
inline sf::Sprite cancelSprite(texture_atlas, cancelRect);

//--------------title-menu-buttons-------------------------
inline sf::Sprite startHighlight(texture_atlas, startRect);
inline sf::Sprite quitHighlight(texture_atlas, quitRect);

//-------------backgrounds---------------------------------
inline sf::Sprite titleScreen(texture_title);
inline sf::Sprite gameBoard(texture_gameBoard);
inline sf::Sprite clouds(texture_clouds);
inline sf::Sprite cloudsTwo(texture_cloudsTwo);
inline sf::Sprite checkBackground(texture_checkBack);
inline sf::Sprite gameOver(texture_gameOver);

//--------------------misc-----------------------------------
inline sf::Sprite logo(texture_logo);
inline sf::Sprite heart(texture_atlas,heartRect);
inline sf::Sprite heart2(texture_atlas, heartRect);

inline sf::Sprite heart3(texture_atlas, heartRect);





//=================================================
//  --------------------FONTS--------------------
//=================================================
sf::Font font("PressStart2P.ttf");


//=================================================
//  --------------------AUDIO--------------------
//=================================================
