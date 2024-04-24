#ifndef MENUSCENE_H
#define MENUSCENE_H

 enum State{
     // KEEP THE NUMBERS THE SAME FOR LEVELS.
     // ENEMY HANDLER DEPENDENT ON THAT
     State_LandingPage = 0,
     State_MainMenu = 1,
     State_Game = 2,
     State_Help = 3,
     State_Level2 = 4,
     State_Level3 = 5,
     State_Final = 6
    };

class MenuScene
{
    public:
        MenuScene();
        virtual ~MenuScene();
        State gState = State_LandingPage; //Set Initial State to LandingPage
        void DisplayMainMenu(); //Draw main menu here
        void DisplayGame(); // Draw game here
        void display(); //GLUT callback

    protected:

    private:
};

#endif // MENUSCENE_H
