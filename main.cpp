#include "GameEngine.h"

#define DEBUG 1

const int LARGURA = 700;
const int ALTURA = 650;

ALLEGRO_BITMAP *al_logo = NULL;
ALLEGRO_FONT *fontFrame = NULL;
ALLEGRO_FONT *fontFrame26 = NULL;

void debug_FPS(unsigned FPS, unsigned frames, double teF);
void debug_Joystick(const Joystick &joy);
void debug_Mouse(const Mouse &mouse);
void debug_Allegro();

void init();

int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *ev_queue = NULL;

    bool done = false;
    unsigned frames = 0;
    unsigned FPS = 0;

    long double start = 0.0l;

    init();

    janela = al_create_display(LARGURA, ALTURA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar a janela\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao criar Janela",
                                   "No foi possivel criar um Janela.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(janela,"My SpaceShooter");

    //carregar a fonte

    ev_queue = al_create_event_queue();
    al_register_event_source(ev_queue,al_get_display_event_source(janela));
    al_register_event_source(ev_queue,al_get_mouse_event_source());
    al_register_event_source(ev_queue,al_get_keyboard_event_source());
    al_register_event_source(ev_queue,al_get_joystick_event_source());

    fontFrame = al_load_font("acmesab.ttf", 14, 0);
    fontFrame26 = al_load_font("acmesab.ttf", 26, 0);

    JoystickHandler::init();

    Joystick &joy = JoystickHandler::getJoystick(1);

    Keyboard kb;

    Mouse mo;


    if (!fontFrame)
    {
        fprintf(stderr, "Falha ao carregar Fonte ttf\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao carregar Fonte ttf",
                                   "No foi possivel encontrar a fonte especificada.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    bool paused = false;

    SpaceShip sShip(3);
    sShip.setVelocity(320);

    TextFont myText("acmesab.ttf",18);
    myText.setPos(5,5);
    myText.setFontColor(al_map_rgba(100,60,50,200));
    myText.setText(std::string("Life: 3"));

    TextFont textPaused("acmesab.ttf",40);
    textPaused.hide();
    textPaused.setText("GAME PAUSED");
    textPaused.setPosX(LARGURA/2);
    textPaused.setCenterPosY(ALTURA/2);
    textPaused.setAlignmentCenter();
    textPaused.setFontColor(al_map_rgba(0,0,200,100));

    AsteroidGenerator asteroidGenerator(0,LARGURA-60,3);
    ExplosionHandler explosionHandler;
    FireBulletHandler fireHandler(Bullet(nullptr,0,0,600),5);

    Scene myScene;
    myScene.addObject(&sShip);
    myScene.addObject(&asteroidGenerator);
    myScene.addObject(&explosionHandler);
    myScene.addObject(&fireHandler);
    myScene.addObject(&myText);
    myScene.addObject(&textPaused);

    long double lastTeF = start = al_get_time();
    while (!done)
    {
        ALLEGRO_EVENT ev;

        while (!al_is_event_queue_empty(ev_queue))
        {
            al_wait_for_event(ev_queue, &ev);
            if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                default:
                    break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                done = true;
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT)
            {
                paused = true;
                textPaused.show();
            }

        }

        //preScene()
        al_clear_to_color(al_map_rgb(255, 255, 255));

        //updates
        long double current = al_current_time();
        if (current - start >= 1.0f)
        {
            FPS = frames;
            start = current;
            frames = 0;
        }

        long double teF = current - lastTeF;
        lastTeF = current;

        //limitar frames
        long double tmeF = (current - start)/frames;
        long double idealTeF = 1.0l/60;
        if ( tmeF < idealTeF)
            al_rest(idealTeF);


        //if (teF < 1.0l/60)
        //   al_rest(1.0l/60 - teF);

        joy.update();
        kb.update();
        mo.update();
        //end preScene



        std::list<Asteroid *> asteroids = asteroidGenerator.getAsteroids();
        for(std::list<Asteroid *>::const_iterator it = asteroids.begin() ; it != asteroids.end() ; ++it)
            if ((*it)->getPosY() > ALTURA)
                asteroidGenerator.explodeAsteroid(*it);

        if (!sShip.isExploded())
        {
            asteroids = asteroidGenerator.getAsteroids();
            for(auto it = asteroids.cbegin() ; it != asteroids.cend() ; ++it)
                if (CollideWith((*it)->getSprite(),sShip.getSprite()))
                {
                    asteroidGenerator.explodeAsteroid(*it);
                    explosionHandler.newExplosion((*it)->getCenterPosX(),(*it)->getCenterPosY());
                    explosionHandler.newExplosion(sShip.getCenterPosX(),sShip.getCenterPosY());
                    sShip.explode();
                    myText.setText(std::string("Life: ") + std::to_string(sShip.getLife()));
                }
        }

        std::list<Bullet *> bullets = fireHandler.getBulletsFired();
            for(auto bul : bullets)
                if(bul->getPosY() <= 0)
                {
                    fireHandler.explodeBullet(bul);
                }

        asteroids = asteroidGenerator.getAsteroids();
        for(auto it = asteroids.cbegin() ; it != asteroids.cend() ; )
        {
            bool add = true;
            bullets = fireHandler.getBulletsFired();
            for(auto itB = bullets.cbegin() ; itB != bullets.cend() && it != asteroids.cend(); ++itB)
            {
                if (CollideWith((*it)->getSprite(),(*itB)->getSprite()))
                {
                    fireHandler.explodeBullet(*itB);
                    asteroidGenerator.explodeAsteroid(*it);
                    explosionHandler.newExplosion((*it)->getCenterPosX(),(*it)->getCenterPosY());
                    add = false;
                    it = asteroids.erase(it);
                }
            }
            if (add)
                ++it;
        }

        if(joy.hasBeenPressed(9) || kb.hasBeenPressed(ALLEGRO_KEY_ENTER))
        {
            paused = !paused;
            if (paused)
                textPaused.show();
            else
                textPaused.hide();
        }

        if(joy.hasBeenPressed(1) || kb.hasBeenPressed(ALLEGRO_KEY_R))
            if(sShip.isExploded())
                sShip.reborn();

        if(joy.hasBeenPressed(2) || kb.hasBeenPressed(ALLEGRO_KEY_SPACE) || mo.leftHasBeenPressed())

            if(fireHandler.canFire())
                fireHandler.newBullet(sShip.getCenterPosX(),sShip.getPosY());

        if (joy.centerIsPressed() &&
            !kb.isPressed(ALLEGRO_KEY_LEFT) &&
            !kb.isPressed(ALLEGRO_KEY_RIGHT) &&
            !kb.isPressed(ALLEGRO_KEY_UP) &&
            !kb.isPressed(ALLEGRO_KEY_DOWN)
            )
            sShip.moveStop();

        if (joy.leftIsPressed() || kb.isPressed(ALLEGRO_KEY_LEFT) || mo.hasMovedLeft())
            if(sShip.getCenterPosX() > 0)
                sShip.moveLeft();
        if (joy.rightIsPressed() || kb.isPressed(ALLEGRO_KEY_RIGHT) || mo.hasMovedRight())
            if (sShip.getCenterPosX() < LARGURA)
                sShip.moveRight();

        if (joy.upIsPressed() || kb.isPressed(ALLEGRO_KEY_UP) || mo.hasMovedUp())
            if (sShip.getPosY() > ALTURA*3.0/7.0)
                sShip.moveUp();
        if (joy.downIsPressed() || kb.isPressed(ALLEGRO_KEY_DOWN) || mo.hasMovedDown())
            if (sShip.getCenterPosY() < ALTURA)
                sShip.moveDown();


        if (!paused)
            myScene.update(teF);

        //desenhos aqui

        myScene.draw();



#if DEBUG == 1
        debug_FPS(FPS,frames,teF);
        debug_Allegro();
        debug_Joystick(joy);
        debug_Mouse(mo);
#endif // DEBUG

        al_flip_display();
        frames++;
    }

    al_destroy_display(janela);
    al_destroy_event_queue(ev_queue);
    al_destroy_font(fontFrame);
    al_destroy_font(fontFrame26);
    al_destroy_bitmap(al_logo);

    return 0;
}

void debug_FPS(unsigned FPS, unsigned frames, double teF)
{
    al_draw_filled_rounded_rectangle(5, ALTURA - 100, 160, ALTURA-5,10,10, al_map_rgba(0,0,200,50));
    al_draw_rounded_rectangle(5, ALTURA - 100, 160, ALTURA-5,10,10, al_map_rgba(70,130,180,200),3);

    al_draw_textf(fontFrame, al_map_rgb(65,105,225),15, ALTURA - 85,ALLEGRO_ALIGN_LEFT,"FPS: %d", FPS);
    al_draw_textf(fontFrame, al_map_rgb(65,105,225),15, ALTURA - 63,ALLEGRO_ALIGN_LEFT,"Frame: %d", frames);
    al_draw_textf(fontFrame, al_map_rgb(65,105,225),15, ALTURA - 41,ALLEGRO_ALIGN_LEFT,"Tempo: %4.2f", al_current_time());
//    al_draw_textf(fontFrame, al_map_rgb(65,105,225),15, ALTURA - 19,ALLEGRO_ALIGN_LEFT,"T ev: %g", teF);

}

void debug_Mouse(const Mouse &mouse)
{
    if (mouse.leftIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-180, ALTURA - 70,ALLEGRO_ALIGN_CENTER,"LEFT");
    if (mouse.rightIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-20, ALTURA - 70,ALLEGRO_ALIGN_CENTER,"RIGHT");
    if (mouse.centerIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-100, ALTURA - 100,ALLEGRO_ALIGN_CENTER,"CENTER");

}

void debug_Joystick(const Joystick &joy)
{
    for (unsigned i = 0 ; i < joy.getNumButtons() ; i++)
        if (joy.isPressed(i))
            al_draw_textf(fontFrame26, al_map_rgb(65,100,125),LARGURA/2 + 80 + (50 * (i%4)), ALTURA - 100 + 30 * (i/4),ALLEGRO_ALIGN_CENTER,"%s",joy.getButtonName(i));

    if (joy.leftIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-180, ALTURA - 70,ALLEGRO_ALIGN_CENTER,"LEFT");
    else if (joy.rightIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-20, ALTURA - 70,ALLEGRO_ALIGN_CENTER,"RIGHT");
    if (joy.upIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-100, ALTURA - 100,ALLEGRO_ALIGN_CENTER,"UP");
    else if (joy.downIsPressed())
        al_draw_text(fontFrame26, al_map_rgb(65,100,125),LARGURA/2-100, ALTURA - 40,ALLEGRO_ALIGN_CENTER,"DOWN");
}

void debug_Allegro()
{
    if (al_logo == NULL)
        al_logo = al_load_bitmap("allegro_logo.png");

    al_draw_tinted_scaled_bitmap(al_logo,al_map_rgba(20,20,20,100),0,0,al_get_bitmap_width(al_logo),al_get_bitmap_height(al_logo),
                                 LARGURA - al_get_bitmap_width(al_logo)*.333f+3-5,ALTURA - al_get_bitmap_height(al_logo)*.333f+2-5,
                                 al_get_bitmap_width(al_logo)*.333f,al_get_bitmap_height(al_logo)*.333f,0);
    al_draw_scaled_bitmap(al_logo,0,0,al_get_bitmap_width(al_logo),al_get_bitmap_height(al_logo),
                          LARGURA - al_get_bitmap_width(al_logo)*.333f-5,ALTURA - al_get_bitmap_height(al_logo)*.333f-5,
                          al_get_bitmap_width(al_logo)*.333f,al_get_bitmap_height(al_logo)*.333f,0);
}

void init()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro 5\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao inicializar Allegro 5",
                                   "No foi possivel inicializar a biblioteca Allegro 5. As Bibliotecas foram instaladas?",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    //inicializacao de addons
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar primitivas graficas do Allegro 5\n");
        al_show_native_message_box(NULL,"Mensagem de Erro","Falha ao inicializar primitivas graficas do Allegro 5",
                                   "No foi possivel inicializar as primitivas graficas",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha no Teclado\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao carregar o teclado",
                                   "Impossivel carregar driver do teclado.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    if (!al_install_joystick())
    {
        fprintf(stderr, "Falha no Joystick\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao carregar o Joystick",
                                   "Impossivel carregar driver do joystick.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha no Mouse\n");
        al_show_native_message_box(NULL,"Mensagem de Erro", "Falha ao carregar o Mouse",
                                   "Impossivel carregar driver do mouse.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
}
