#include <GLScene.h>
#include<GLLight.h>
#include<GLTexture.h>
#include<GLModel.h>
#include<GLInputs.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>
#include<GLObject.h>
#include<MenuScene.h>
#include<enemy.h>
#include<EnemyLevelHandler.h>
#include<projectile.h>
#include<GLHUD.h>

#include<GLCollisions.h>
//Initializing Objects based on classes (parallax (static or background images), object (image that needs to be in front of background), MenuScene (state controller for navigation)
GLInputs *KbMs = new GLInputs();
GLParallax *landingPage = new GLParallax();
GLParallax *mainMenu = new GLParallax();
GLParallax *helpPage = new GLParallax();
GLParallax *tutorialMap = new GLParallax();
GLParallax *pausePopup = new GLParallax();
GLParallax *levelTwo = new GLParallax();
GLParallax *levelThree = new GLParallax();
GLParallax *levelFinal = new GLParallax();
GLObject *startButton = new GLObject();
GLObject *helpButton = new GLObject();
GLObject *exitButton = new GLObject();
GLObject *titleBanner = new GLObject();
MenuScene *menuState = new MenuScene();

GLPlayer *player = new GLPlayer();

EnemyLevelHandler *enemies = new EnemyLevelHandler();

projectile *enemy_projectiles = new projectile();
projectile *player_projectiles = new projectile();


GLCheckCollision *hit = new GLCheckCollision();
GLCollisions *tutorialDoor = new GLCollisions();
GLCollisions *levelThreeLeftCornerRightSide = new GLCollisions();
GLCollisions *levelThreeLeftCornerTopSide = new GLCollisions();

bool isPaused = false;
bool needHelp = false;

vec3 playerPos;

MenuScene *prevGameState;


GLHUD *HUD = new GLHUD(); // initializing hud


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // for smooth render
    glClearColor(0.0f,0.0f,0.0f,0.0f); // clear background to black
    glClearDepth(2.0f);            // depth test for layers
    glEnable(GL_DEPTH_TEST);       // activate depth test
    glDepthFunc(GL_LESS);         // depth function type

    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    glEnable(GL_BLEND);             // Transparent effect of pngs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);  //enable textures

    landingPage->parallaxInit("images/forestWithMushroomsLanding.png"); // Load static Landing image
    mainMenu->parallaxInit("images/forestWithMushrooms.png"); // load parallax main menu image
    helpPage->parallaxInit("images/helpPage.png"); // Load static help page image
    tutorialMap->parallaxInit("images/SpawnNoEnmHighRes.png"); // Load tutorial map
    pausePopup->parallaxInit("images/PauseMenuDone.png"); // Pause menu popup during game
    levelTwo->parallaxInit("images/InsideCave.png"); //Level 2 Map Forge (Fire Enemies)
    levelThree->parallaxInit("images/Level2.png"); //Level 3 Transition Map (Hideout)
    levelFinal->parallaxInit("images/Castle.png"); //Final Level (Castle)
    startButton->initObject(1, 1, "images/NewGameBannerBottles.png"); // Load start button object texture
    helpButton->initObject(1, 1, "images/HelpBanner.png"); // Load help button object texture
    exitButton->initObject(1, 1, "images/ExitBanner.png"); // Load exit button object texture
    titleBanner->initObject(1, 1, "images/Title.png"); // Load title banner object texture
    player->initPlayer(6, 10, "images/player.png"); // Load player texture
    player->actionTrigger = player->STAND; // Player does not move until player makes a keypress

    enemy_projectiles->initProj();
    enemies->initEnemies(1, enemy_projectiles);

    // resized to the number of gStates
    player->bounds.resize(7);

    // follows pattern of left, top, right, down
    player->bounds[2] = { -2.9, 1.7, 2.9, -1.5 };   // bounds of tutorial map
    player->bounds[4] = { -2.9, 1.4, 2.9, -1.5 };   // bounds of level 2
    player->bounds[5] = { -2.0, 1.1, 2.0, -0.75 };  // bounds of level 3
    player->bounds[6] = { -2.9, 1.55, 2.9, -1.55 }; // bounds of final level

    // setting the door thats under the tree in tutorial map
    tutorialDoor->pos = vec2({0.0, 1.0});
    tutorialDoor->length = 0.25;
    tutorialDoor->width = 0.05;

    // setting the door from second level to third level
    levelThreeLeftCornerRightSide->pos = vec2({0.0, -0.45});
    levelThreeLeftCornerRightSide->length = 0.05;
    levelThreeLeftCornerRightSide->width = 0.35;

    // setting the door from second level to third level
    levelThreeLeftCornerTopSide->pos = vec2({-1.4, -0.1});
    levelThreeLeftCornerTopSide->length = 1.4;
    levelThreeLeftCornerTopSide->width = 0.05;

    prevGameState=menuState;

    HUD->initHUD(); // initializing hud



    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
                              // DO NOT ABUSE ME
{



    if(prevGameState->gState!=menuState->gState){
        cout << "GAME STATE CHANGED"<<endl;
    }

   if (isPaused)
   {
       pauseGame();
       return true;
   }
   if(needHelp)
   {
       needsHelp();
       return true;
   }
   else
   {
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each iteration
       glLoadIdentity();
       glColor3f(1.0,1.0,1.0);     //color the object red
   }
   switch (menuState->gState)
   {
   case State_LandingPage: // Landing Page State

       glPushMatrix();  //Loading static landing page with Title and Info graphic
        glScalef(3.5,3.2,1.0);
        glDisable(GL_LIGHTING);
        landingPage->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();
       break;

   case State_MainMenu: // Main Menu State

       glDisable(GL_DEPTH_TEST); // Disabling depth_test since 2D game and was messing with parallax layering

       glPushMatrix();      //Loading background w/ Parallax
        glScalef(3.5,3.2,1.0);
        glDisable(GL_LIGHTING);
        mainMenu->parallaxDraw(screenWidth, screenHeight);
        mainMenu->parallaxScroll(true, "right", 0.0005);
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();  //Adding Start Button in front of Parallax Background
        // We can manipulate the position of our buttons via 'objPosition' before the drawObject function.
        // NOTE: (-0.5, -0.2) = BTM_LEFT | (0.5, 0.2) = TOP_RIGHT | NO_CHANGE = SLIGHT BTM CENTER SCREEN
        startButton->objPosition.y = -0.04;
        glScalef(1.0, 1.0, 0.175);
        glDisable(GL_LIGHTING);
        startButton->drawObject();
        glEnable(GL_LIGHTING);
       glPopMatrix();

       // Help Button
       glPushMatrix();  //Adding Help Button in front of Parallax Background
        helpButton->objPosition.y = -0.10; // Adjust Y position to separate from startButton
        glScalef(1.0, 1.0, 0.175); // Adjust scale as needed
        glDisable(GL_LIGHTING);
        helpButton->drawObject();
        glEnable(GL_LIGHTING);
       glPopMatrix();

        // Exit Button
       glPushMatrix();  //Adding Exit Button in front of Parallax Background
        exitButton->objPosition.y = -0.15; // Adjust Y position to separate from helpButton
        glScalef(1.0, 1.0, 0.175); // Adjust scale as needed
        glDisable(GL_LIGHTING);
        exitButton->drawObject();
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();  //Adding Title Header in front of Parallax Background
        titleBanner->objPosition.y = 0.035; // Adjust Y position to separate from helpButton
        glScalef(1.0, 1.0, 0.175); // Adjust scale as needed
        glDisable(GL_LIGHTING);
        titleBanner->drawObject();
        glEnable(GL_LIGHTING);
       glPopMatrix();

       break;

   case State_Game: // Game State

       glPushMatrix();      //Loading tutorial map
        glScalef(3.5,3.5,1.0);
        glDisable(GL_LIGHTING);
        tutorialMap->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();          // drawing player
        glScalef(0.5, 0.5, 1.0);
        glDisable(GL_LIGHTING);
        player->boundsCheck(menuState->gState);
        if (player->hit_check(enemy_projectiles)) {
            
            if (HUD->hearts > 0) {
                HUD->hearts--;
                cout<<"HUD Hearts: " <<HUD->hearts<<endl;
            }
            
            // if (HUD->hearts < 3) {
            //     HUD->hearts++;
            //     cout<<"HUD Hearts: " <<HUD->hearts<<endl;
            // }


        }
        if (hit->isAABBCollision(vec2({player->plPosition.x, player->plPosition.y}), tutorialDoor->pos, tutorialDoor->length, tutorialDoor->width )) {
            menuState->gState = State_Level2;
        }
        if(HUD->hearts > 0) 
            player->drawPlayer();
        player->actions();
        playerPos=player->getPos();        
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();          // drawing enemies
       glScalef(0.5, 0.5, 1.0);
        enemies->setTarget(playerPos);
         enemies->drawEnemies();

       glPopMatrix();

       glPushMatrix();          // drawing projectiles
        enemy_projectiles->draw_projectiles();
       glPopMatrix();

       glPushMatrix();          // drawing HUD
        glScalef(0.1, 0.1, 1.0);
        glDisable(GL_LIGHTING);
        HUD->hudDraw();
        glEnable(GL_LIGHTING);
       glPopMatrix();


       break;

   case State_Level2:
       glPushMatrix();      //Loading Level 2 map
        glScalef(3.5,3.5,1.0);
        glDisable(GL_LIGHTING);
        levelTwo->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();
        glScalef(0.5, 0.5, 1.0);
        glDisable(GL_LIGHTING);
        player->boundsCheck(menuState->gState);
        if(HUD->hearts > 0)
            player->drawPlayer(); 
        player->actions();
        glEnable(GL_LIGHTING);
       glPopMatrix();

        break;

   case State_Level3:

       glPushMatrix();      //Loading Level 3 map
        glScalef(3.5,3.5,1.0);
        glDisable(GL_LIGHTING);
        levelThree->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();
        glScalef(0.5, 0.5, 1.0);
        glDisable(GL_LIGHTING);
        player->boundsCheck(menuState->gState);
        if (hit->isAABBCollision(vec2({player->plPosition.x, player->plPosition.y}), levelThreeLeftCornerRightSide->pos, levelThreeLeftCornerRightSide->length, levelThreeLeftCornerRightSide->width )) {
            player->plPosition.x = levelThreeLeftCornerRightSide->pos.x + levelThreeLeftCornerRightSide->length;
        }
        if (hit->isAABBCollision(vec2({player->plPosition.x, player->plPosition.y}), levelThreeLeftCornerTopSide->pos, levelThreeLeftCornerTopSide->length, levelThreeLeftCornerTopSide->width )) {
            player->plPosition.y = levelThreeLeftCornerTopSide->pos.y + levelThreeLeftCornerTopSide->width;
        }
        if(HUD->hearts > 0) 
            player->drawPlayer();
        player->actions();
        glEnable(GL_LIGHTING);
       glPopMatrix();

        break;
   case State_Final:


       glPushMatrix();      //Loading Final Level map
        glScalef(3.5,3.5,1.0);
        glDisable(GL_LIGHTING);
        levelFinal->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();
        glScalef(0.5, 0.5, 1.0);
        glDisable(GL_LIGHTING);
        player->boundsCheck(menuState->gState);
        if(HUD->hearts > 0)
            player->drawPlayer(); 
        player->actions();
        glEnable(GL_LIGHTING);
       glPopMatrix();


    break;

   case State_Help: // Help State

       glPushMatrix();  //Loading static help page
        glScalef(3.2,3.2,1.0);
        glDisable(GL_LIGHTING);
        helpPage->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();
       break;
   }


   return true;
   prevGameState=menuState;
}

GLvoid GLScene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; // keep track of the ratio
    glViewport(0,0,width,height); // adjusting the view port
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspectRatio,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN: // On Player key press
        //KbMs->wParam = wParam;
        //KbMs->keyPress(player);
        player->keyStates[wParam] = true;
        player->update();
        switch(wParam)
        {
            case VK_RETURN: // if press is 'Enter'
                {
                    if(menuState->gState == State_LandingPage) // And if the current state is at the Landing Page
                        {
                            menuState->gState = State_MainMenu; // Change to Main Menu page
                        }
                    else if(isPaused == true)
                    {
                        requestExit = true;
                    }
                    break;
                }
            case VK_ESCAPE:     // if press is 'Esc'
                {
                    if(menuState->gState == State_Help) // And if the current state is at the help page
                    {
                        menuState->gState = State_MainMenu; // go back to the main menu
                    }
                    else if (menuState->gState == State_MainMenu) // Or if the current state is the Main Menu
                    {
                        requestExit = true;     // Send request to exit, (main watches this via a function call 'ShouldExit()' quits game if true
                    }
                    break;
                }
            case VK_SPACE: // if press is 'N'
                if(menuState->gState == State_Game){


                    enemies->meleAttack(playerPos);


                }


                break;
            case 'N': // if press is 'N'
                {
                    if(menuState->gState == State_MainMenu) // And if the current state is Main Menu
                        {
                            // This is where we should initialize enemies
                            menuState->gState = State_Game;
                        }
                    else if (menuState->gState == State_Game)
                    {
                        menuState->gState = State_Level2;
                    }
                    else if (menuState->gState == State_Level2)
                    {
                        menuState->gState = State_Level3;
                    }
                    else if (menuState->gState == State_Level3)
                    {
                        menuState->gState = State_Final;
                    }
                    break;
                }
            case 'H':   // if press is 'H'
                {
                    if(menuState->gState == State_MainMenu) // and current state is Main Menu
                        {
                            menuState->gState = State_Help;    // Switch to Help page
                        }
                    break;
                }
            case 'L':   // if press is 'L'
                {
                    if(menuState->gState == State_MainMenu)     // And current state is Main Menu
                        {
                            menuState->gState = State_LandingPage; // Go back to Landing Page
                        }
                    break;
                }
            case 'R':   // if press is 'R'
                HUD->hearts = 3;    // Reset hearts to 3
                break;




        }
         break;

    case WM_KEYUP:
        //KbMs->wParam = wParam;
        //KbMs->keyUP(player);
        player->keyStates[wParam] = false;
        player->update();

        switch (wParam)
        {
        case VK_ESCAPE:
            if (menuState->gState == State_Game || menuState->gState == State_Level2 || menuState->gState == State_Level3 || menuState->gState == State_Final)
            {
                if(isPaused == false)
                {
                    isPaused = true;
                }
                else if(isPaused == true)
                {
                    isPaused = false;
                }
            }
            break;
        case 'H':
            if ((menuState->gState == State_Game || menuState->gState == State_Level2 || menuState->gState == State_Level3 || menuState->gState == State_Final) && needHelp == false)
            {
                needHelp = true;
            }
            else
            {
                needHelp = false;
            }
        }
        break;        



    case WM_LBUTTONDOWN:
        {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            KbMs->mousEventDown(enemy_projectiles, LOWORD(lParam), HIWORD(lParam));

            cout << LOWORD(lParam)<<endl;
            cout << HIWORD(lParam)<<endl;

            cout << screenWidth << endl;
            cout << screenHeight <<endl;


            cout << playerPos.x << endl;
            cout << playerPos.y << endl;

            cout <<"\n"<<endl;




            return 0;

            break;

        }




    case WM_RBUTTONDOWN:


         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;

    case WM_MOUSEMOVE:

         break;
    case WM_MOUSEWHEEL:


       break;
    }
}
GLint GLScene::pauseGame()
{

     glPushMatrix();      //Loading background w/ Parallax
        glScalef(3.5,3.5,1.0);
        glDisable(GL_LIGHTING);
        pausePopup->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
     glPopMatrix();
}
GLint GLScene::needsHelp()
{
       glPushMatrix();  //Loading static help page
        glScalef(3.2,3.2,1.0);
        glDisable(GL_LIGHTING);
        helpPage->parallaxDraw(screenWidth, screenHeight);
        glEnable(GL_LIGHTING);
       glPopMatrix();
}



