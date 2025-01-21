#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include "Lobby.h"
#include <iostream>

using namespace sf;

//text settings
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color lobby_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

void GameStart(RenderWindow& Play);

int main()
{
    srand(time(NULL));
    RenderWindow win(VideoMode({ 1280, 720 }), "SpaceDiver");

    Image icon;
    if (!icon.loadFromFile("textures/player1.png")) return 13;
    win.setIcon(48, 48, icon.getPixelsPtr());

    win.setMouseCursorVisible(false);

    win.setVerticalSyncEnabled(true);

    const int width = 1280;
    const int height = 720;

    RectangleShape LobBack(Vector2f(width, height));
    Texture LobbyBackgroundTex;
    if (!LobbyBackgroundTex.loadFromFile("textures/logowidem.png")) return 4;;
    LobBack.setTexture(&LobbyBackgroundTex);

    Font GameFont;
    if (!GameFont.loadFromFile("fonts/Oswald-Regular.ttf")) return 11;

    RectangleShape TBG(Vector2f(430, 550));
    TBG.setFillColor(Color(195, 195, 195, 100));
    TBG.setPosition(0, 60);

    Text Info;
    Info.setFont(GameFont);
    InitText(Info, 20, 70, 
        "   C O N T R O L  K E Y S:\n- Menu navigation: \n    move - arrows Up/Down\n    confirm selection - Enter\n    quit - Esc\n- Game navigation: \n    move - keys W/S\n    pause - Home\n    quit - Backspace", 
        40, Color::Yellow, 3);

    Music lobby_ambient;
    if (!lobby_ambient.openFromFile("sounds/oggs/lobby1.ogg")) exit(14);
    lobby_ambient.setLoop(true);
    lobby_ambient.play();

    String name_menu[2]{ "PLAY", "QUIT"};
    int lenmenu = sizeof(name_menu) / sizeof(name_menu[0]);
    game::Lobby mymenu(win, 645, 475, name_menu, lenmenu, 50, 100);

    std::cout << "Lobby created with " << lenmenu << " menu items.\n";

    mymenu.setColorTextMenu(Color(195, 195, 195), Color(255, 242, 0), Color::Black);
    mymenu.AlignMenu(2);

    while (win.isOpen())
    {
        Event event;

        while (win.pollEvent(event)) {
            if (event.type == Event::Closed || event.key.code==Keyboard::Escape) {
                win.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    mymenu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    mymenu.MoveDown();
                }
                if (event.key.code == Keyboard::Return) {
                    switch (mymenu.getSelectedMenuNumber()) {
                    case 0:
                        lobby_ambient.stop();
                        std::cout << "Starting Game\n";
                        GameStart(win);
                        break;
                   
                    case 1:
                        std::cout << "Exiting Game\n";
                        win.close();
                        break;
                    }
                }
            }
        }

        win.clear();
        win.draw(LobBack);
        win.draw(TBG);
        win.draw(Info);
        mymenu.draw();
        win.display();
    }
    return 0;
}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, 
    Color lobby_text_color, int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(lobby_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}

void GameStart(RenderWindow& Play)
{
    Font GameFont;
    if (!GameFont.loadFromFile("fonts/Oswald-Regular.ttf")) exit(11);

    //sound
    Music game_ambient;
    if (!game_ambient.openFromFile("sounds/oggs/ambient2.ogg")) exit(14);
    game_ambient.setLoop(true);
    game_ambient.play();

    Sound falsound, soundM, soundB, soundV;
    SoundBuffer fal, sM, sB, sV;
    fal.loadFromFile("sounds/wavs/collision1.wav");
    falsound.setBuffer(fal);
    sM.loadFromFile("sounds/wavs/shield_sound.wav");
    soundM.setBuffer(sM);
    sB.loadFromFile("sounds/wavs/collision2.wav");
    soundB.setBuffer(sB);
    sV.loadFromFile("sounds/oggs/end.ogg");
    soundV.setBuffer(sV);

    //game background
    Texture GameBackground;
    if (!GameBackground.loadFromFile("textures/backgroundwide.png")) exit(1);
    RectangleShape BackBack(Vector2f(1400, 700));
    BackBack.setTexture(&GameBackground);
    BackBack.setPosition(Vector2f(0, 20));
    RectangleShape BackBack2(Vector2f(1400, 700));
    BackBack2.setTexture(&GameBackground);
    BackBack2.setPosition(Vector2f(1400, 20));

    //game panel
    Texture InfoPanel;
    InfoPanel.loadFromFile("textures/top_panel.png");
    RectangleShape GameInfoPanel(Vector2f(1280, 100));
    GameInfoPanel.setTexture(&InfoPanel);
    GameInfoPanel.setPosition(Vector2f(0, 0));
    Texture PanelIcon;
    PanelIcon.loadFromFile("textures/energy.png");
    RectangleShape GameIconPanel(Vector2f(48, 48));
    GameIconPanel.setTexture(&PanelIcon);
    GameIconPanel.setPosition(Vector2f(1024, 15));

    //path
    CircleShape Rcircle(5.f);
    Rcircle.setFillColor(Color::Green);
    Rcircle.setOutlineThickness(2.f);
    Rcircle.setOutlineColor(Color::Black);
    Rcircle.setOrigin(2.5f, 2.5f);
    Rcircle.setPosition(495, 50);

    //fuel
    int popup = 0;
    double tmpfull = 0;
    unsigned int full = 100;
    Text text_full, plusfull, text_pause, end_game, game_over;

    //bool minusfull = false;
    Full canister("textures/energy.png", 48, 48);

    //fuel visualisation
    text_full.setFont(GameFont);
    InitText(text_full, 1070, 20, IntToStr(full) + " %", 30, Color::Yellow);
    /*text_full.setFillColor(Color::Yellow);
    text_full.setCharacterSize(30);
    text_full.setPosition(1070, 20);*/

    //fuel popup
    plusfull.setFont(GameFont);
    plusfull.setFillColor(Color::Yellow);
    plusfull.setCharacterSize(25);

    //end level
    end_game.setFont(GameFont);
    InitText(end_game, 190, 330, "This is just the beginning", 100, Color::Red);
    //end_game.setFillColor(Color::Red);
    //end_game.setCharacterSize(100);
    //end_game.setString("This is just the beginning"); //190 330
    //end_game.setPosition(190, 330);

    //pause
    text_pause.setFont(GameFont);
    InitText(text_pause, 560, 330, "P A U S E", 50, Color::Magenta);
    //text_pause.setFillColor(Color::Magenta);
    //text_pause.setCharacterSize(50);
    //text_pause.setString("P A U S E"); //560 330
    //text_pause.setPosition(560, 330);

    //game over
    game_over.setFont(GameFont);
    InitText(game_over, 430, 330, "G A M E   O V E R", 70, Color::Red, 5);
    //game_over.setFillColor(Color::Red);
    //game_over.setCharacterSize(70);
    //game_over.setString("G A M E   O V E R"); //470 330
    //game_over.setPosition(430, 330);

    //variables
    bool GameOver = false, GamePause = false, inGame = true;
    Vector2f pos;
    Clock clock, clockAnimText, clocktime;
    float time, timePlayer, timeBackground, timeobs;

    //player
    Vector2f moveRec;
    Texture texplayer;
    if (!texplayer.loadFromFile("textures/player1right.png")) exit(19);
    Sprite player;
    player.setTexture(texplayer);
    player.setOrigin(24, 24);
    player.setPosition(Vector2f(380, 380));

    //planet
    Texture texPlanet;
    if (!texPlanet.loadFromFile("textures/planet.png")) exit(33);
    RectangleShape Planet(Vector2f(800, 800));
    Planet.setTexture(&texPlanet);
    Planet.setPosition(Vector2f(1400, 100));

    //destruction
    Texture texdest;
    if (!texdest.loadFromFile("textures/bangb.png")) exit(6);
    Sprite destruction;
    destruction.setTexture(texdest);
    destruction.setOrigin(48, 48);

    //obstacle array
    Obstacle obstacles[15];
    const unsigned int nobstcl = 15;

    while (inGame && Play.isOpen()) {
        Event event_play;

        time = clock.getElapsedTime().asMicroseconds();
        timePlayer = time / 2000;
        timeBackground = time / 6000;
        timeobs = time / 3000;
        clock.restart();

        while (Play.pollEvent(event_play)) {

            if (event_play.type == Event::Closed) Play.close();
            if (event_play.type==Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::BackSpace) inGame = false;
            }

            // control
                switch (event_play.type)
                {
                case Event::KeyPressed:
                    if (event_play.key.code == Keyboard::Home) GamePause = !GamePause;
                   
                    if ((event_play.key.code == Keyboard::W) || (event_play.key.code == Keyboard::Up))
                        if (full != 0) {
                            moveRec.y = -0.3 * timePlayer;
                            full--;
                        }
                    
                    if ((event_play.key.code == Keyboard::S) || (event_play.key.code == Keyboard::Down))
                        if (full != 0) {
                            moveRec.y = 0.3 * timePlayer;
                            full--;
                        }
                    break;
                case Event::KeyReleased:
                    if ((event_play.key.code == Keyboard::W) || (event_play.key.code == Keyboard::Up))
                    {
                        moveRec.y = 0;
                    }
                    if ((event_play.key.code == Keyboard::S) || (event_play.key.code == Keyboard::Down))
                    {
                        moveRec.y = 0;
                    }
                    break;
                default:
                    break;
                }
        }

        if (!GamePause) {
            if (Rcircle.getPosition().x <= 850) {
                if (GameOver) {
                    player.setPosition(Vector2f(380, 380));
                    for (int i = 0;i < nobstcl;i++)
                        obstacles[i].restart();
                    canister.restart();
                    Rcircle.setPosition(495, 33);
                    popup = 0;
                    full = 100;
                    game_ambient.stop();
                    if (clockAnimText.getElapsedTime() > seconds(5))
                        inGame = false;
                }
                else {
                    Rcircle.move(0.01 * timeBackground, 0);
                    if (full!=0 && clocktime.getElapsedTime() > seconds(2)) {
                        full--;
                        clocktime.restart();
                    }
                    if (clockAnimText.getElapsedTime() > milliseconds(50)) {
                        clockAnimText.restart();
                        if (popup > 0) {
                            popup--;
                            plusfull.move(0, -1);
                        }
                    }

                    // background
                    BackBack.move(-0.5 * timeBackground, 0);
                    pos = BackBack.getPosition();
                    if (pos.x < -1400) BackBack.setPosition(1400, pos.y);
                    BackBack2.move(-0.5 * timeBackground, 0);
                    pos = BackBack2.getPosition();
                    if (pos.x < -1400) BackBack2.setPosition(1400, pos.y);

                    //player move
                    PlayerMove(player, moveRec);

                    for (int i = 0;i < nobstcl;i++) {
                        if (obstacles[i].newborn) Correct(canister, i, obstacles, nobstcl);

                        obstacles[i].move(timeobs);

                        if (obstacles[i].collision(player.getGlobalBounds())) {
                            falsound.play();
                            GameOver = true;
                            destruction.setPosition(player.getPosition().x, player.getPosition().y);
                            break;
                        }
                    }

                    if (canister.newborn) CorrectFull(canister, obstacles, nobstcl);
                    
                    canister.move(timeobs);

                    if (canister.collision(player.getGlobalBounds())) {
                        if (full <= 100) {
                            tmpfull = 10 + rand() % 90;
                            full += tmpfull;
                            if (tmpfull > 50) soundB.play();
                            else soundM.play();
                        }
                        plusfull.setString(IntToStr(tmpfull));
                        plusfull.setPosition(canister.getposbonus().x, canister.getposbonus().y);
                        popup = 40;
                        canister.restart();
                    }
                }

                //fuel on infopanel
                if (full >= 100)text_full.setFillColor(Color::Green);
                if (full < 100 && full >= 50)text_full.setFillColor(Color::Yellow);
                if (full < 50) text_full.setFillColor(Color::Red);
                text_full.setString(IntToStr(full) + " %");

                Play.clear();
                Play.draw(BackBack2);
                Play.draw(BackBack);
                Play.draw(GameInfoPanel);
                
                if (GameOver) 
                {
                    
                    Play.draw(destruction);
                    Play.draw(game_over);
                }
                else 
                {
                    Play.draw(GameIconPanel);
                    Play.draw(Rcircle);
                    Play.draw(player);
                    for (int i = 0;i < nobstcl;i++) obstacles[i].draw(Play);
                    canister.draw(Play);
                    Play.draw(text_full);
                    if (popup > 0) Play.draw(plusfull);
                }

                Play.display();

                if (Rcircle.getPosition().x > 850)
                {
                    game_ambient.stop();
                    soundV.play();
                }
            }
            else {
                
                if (Planet.getPosition().x >= 850)
                    Planet.move(-2 * timeBackground, 0);

                Play.clear();
                Play.draw(BackBack2);
                Play.draw(BackBack);
                Play.draw(GameInfoPanel);
                Play.draw(player);
                Play.draw(Planet);
                Play.draw(end_game);
                Play.display();

                if (clockAnimText.getElapsedTime() > seconds(20))
                    inGame = false;
            }
        }
        else {
            Play.draw(text_pause);
            Play.display();
        }
    }
}
