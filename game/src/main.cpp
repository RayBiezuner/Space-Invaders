#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/shader.h"
#include "../include/player.h"
#include "../include/texture.h"
#include "../include/bullet.h"
#include "../include/enemy.h"
#include "../include/square.h"
#include "../include/mothership.h"

#include "stb_image.h"
// IMGUI
/*
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"*/

#include <iostream>
#include <cmath>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Player *player);
// void enemyControl(Enemy aliens[][4]);
// void enemyControl(Enemy aliens[][4]);
void bindBuffers(const float (&vertices)[20], const unsigned int (&indices)[6], unsigned int *VBO, unsigned int *VAO, unsigned int *EBO);
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
// Tamanho da janela
const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;
// TEXTURES
/*
Texture* ALIEN1_TEXTURE = &Texture("sprites/alien1.png");
Texture* ALIEN2_TEXTURE = &Texture("sprites/alien2.png");
Texture* ALIEN3_TEXTURE = &Texture("sprites/alien3.png");
Texture* ALIEN4_TEXTURE = &Texture("sprites/alien4.png");
Texture* ALIEN_BULLET_TEXTURE = &Texture("sprites/alienBullet.png");
*/
const float VERTEX_DATA[20] = {
    // COORDINATES          //TEXTURE COORDINATES
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
const float BACKGROUND_VERTEX_DATA[20] = {
    // COORDINATES          //TEXTURE COORDINATES
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
const unsigned int INDICES[6] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
bool GAME_PAUSED = false;
bool RESTART_GAME = false;
bool DEBUG_MODE = false;
bool ITERATE = false;
bool START = true;
void resetGlobalVariables()
{
    GAME_PAUSED = false;
    RESTART_GAME = false;
    DEBUG_MODE = false;
    ITERATE = false;
    START = true;
}
int main()
{
    // glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    // inicialização e configuração de contexto
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_TRUE);
    glfwWindowHint(GLFW_ICONIFIED, GL_TRUE);
    //  criação da janela e verificação de erros
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Space Invaders", NULL, NULL);

    GLFWimage images[1];
    images[0].pixels = stbi_load("sprites/alien1.png", &images[0].width, &images[0].height, 0, 4); // rgba channels
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    if (window == NULL)
    {
        std::cout << "Falha na criacao da janela" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    // GLAD: Carregamento dos ponteiros de funções para utilizar OpenGL moderno
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Falha na inicializacao do GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setup Dear ImGui context
    /*
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    */
    // ImGui::StyleColorsClassic();
    //  Setup Platform/Renderer backends

    /*
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);*/

    //-------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        resetGlobalVariables();
        // Shader program used to render squares
        Shader shaderProgram1("shaders/vertex.glsl", "shaders/fragment.glsl");
        Shader shaderProgram2("shaders/vertex.glsl", "shaders/spaceshipFragment.glsl");
        // Texture creation
        Texture spaceshipTexture("sprites/spaceship.png");
        Texture spaceshipBulletTexture("sprites/spaceshipLasers.png");

        Texture ALIEN1_TEXTURE("sprites/alien1.png");
        Texture ALIEN2_TEXTURE("sprites/alien2.png");
        Texture ALIEN3_TEXTURE("sprites/alien3.png");
        Texture ALIEN4_TEXTURE("sprites/alien4.png");
        Texture ALIEN_BULLET_TEXTURE("sprites/alienBullet.png");

        unsigned int VBO1, VAO1, EBO1;
        unsigned int VBO2, VAO2, EBO2;
        bindBuffers(VERTEX_DATA, INDICES, &VBO1, &VAO1, &EBO1);

        float initialPosition[2] = {0.0f, -0.7f};
        float enemyInitialPosition[2] = {-0.4f, 0.4f};
        // Bullet bullet(&shaderProgram1, &spaceshipBulletTexture, initialPosition, 10);
        Player player(&shaderProgram2, &shaderProgram1, &VAO1, &spaceshipTexture, &spaceshipBulletTexture);

        Mothership mothership(&VAO1, 5, 8);
        mothership.SetEnemies(&shaderProgram1, &ALIEN1_TEXTURE, &ALIEN2_TEXTURE, &ALIEN3_TEXTURE, &ALIEN4_TEXTURE);
        mothership.SetGun(&shaderProgram1, &ALIEN_BULLET_TEXTURE);

        Texture backgroundTexture("sprites/espaco.png");
        bindBuffers(BACKGROUND_VERTEX_DATA, INDICES, &VBO2, &VAO2, &EBO2);
        Square background(&backgroundTexture, &shaderProgram1);

        Texture startTexture("sprites/start.png");
        bindBuffers(BACKGROUND_VERTEX_DATA, INDICES, &VBO2, &VAO2, &EBO2);
        Square start(&startTexture, &shaderProgram1);

        Texture winTexture("sprites/youwin.png");
        bindBuffers(BACKGROUND_VERTEX_DATA, INDICES, &VBO2, &VAO2, &EBO2);
        Square win(&winTexture, &shaderProgram1);

        Texture gameoverTexture("sprites/youloose.png");
        bindBuffers(BACKGROUND_VERTEX_DATA, INDICES, &VBO2, &VAO2, &EBO2);
        Square gameover(&gameoverTexture, &shaderProgram1);

        bool show_another_window = true;
        while (!glfwWindowShouldClose(window))
        {

            processInput(window, &player);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            background.Draw(&VAO2, 0.25f);
            mothership.Draw();
            mothership.BulletDraw();
            player.Draw();
            player.bulletDraw();

            if (START == true)
            {
                start.Draw(&VAO2, 2.0f);
            }
            if (!GAME_PAUSED && !DEBUG_MODE && !START)
            {
                player.playerLoop(mothership.getGun());
                player.bulletLoop();
                player.Draw();
                mothership.Movement(0.65f);
                mothership.Collision(player.getGun());
                mothership.BulletLoop();
                // If enemies enter player zone or player dies
                if (mothership.EnemiesLoose())
                {
                    win.Draw(&VAO2, 2.0f);
                }
                else if (mothership.EnemiesWon() || !player.isAlive())
                {
                    gameover.Draw(&VAO2, 2.0f);
                }
            }
            else if (DEBUG_MODE && ITERATE)
            {
                player.playerLoop(mothership.getGun());
                player.bulletLoop();
                player.Draw();
                mothership.Movement(0.65f);
                mothership.Collision(player.getGun());
                mothership.BulletLoop();
                // If enemies enter player zone or player dies
                if (mothership.EnemiesLoose())
                {
                    win.Draw(&VAO2, 2.0f);
                }
                else if (mothership.EnemiesWon() || !player.isAlive())
                {
                    gameover.Draw(&VAO2, 2.0f);
                }
                ITERATE = false;
            }
            /*
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (DEBUG_MODE)
            {
                ImGui::Begin("Jogador e suas balas");
                player.PrintData();
                player.getGun()->PrintPositions();
                ImGui::End();
                ImGui::Begin("Inimigos");
                mothership.PrintEnemies();
                ImGui::End();
                ImGui::Begin("Balas dos Inimigos");
                mothership.getGun()->PrintPositions();
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            */
            glfwSwapBuffers(window);
            glfwPollEvents();
            if (RESTART_GAME == true)
            {
                RESTART_GAME = false;
                break;
            }
        }
        glDeleteVertexArrays(1, &VAO1);
        glDeleteBuffers(1, &VBO1);
        glDeleteBuffers(1, &EBO1);
        // Desalocar memória dos objetos instanciados
        mothership.Delete();
    }

    /*
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();*/

    // ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate(); // Faz a limpeza dos recursos utilizados pelo GLFW
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window, Player *player)
{
    // CLOSE SCREEN
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    // MOVE PLAYER
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    float normalizedMousePosition[2] = {2 * (float)(xPos) / WIDTH - 1, -0.7f};
    if (!GAME_PAUSED && !DEBUG_MODE)
    {
        player->setPosition(normalizedMousePosition);
    }
    // SHOOT LASERS
    static int oldStateLeft = GLFW_PRESS;
    int newStateLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (newStateLeft == GLFW_PRESS && oldStateLeft == GLFW_RELEASE && !GAME_PAUSED)
    {
        START = false;
        player->fireBullet();
    }
    oldStateLeft = newStateLeft;

    // PAUSE GAME
    static int oldStateRight = GLFW_PRESS;
    int newStateRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (newStateRight == GLFW_PRESS && oldStateRight == GLFW_RELEASE)
    {
        START = false;
        if (!DEBUG_MODE)
        {
            GAME_PAUSED = !GAME_PAUSED;
        }
        else
        {
            GAME_PAUSED = false;
            DEBUG_MODE = false;
        }
    }

    oldStateRight = newStateRight;
    // RESTART GAME
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        RESTART_GAME = true;
        std::cout << "restart" << std::endl;
    }
    // SHOW DATA
    static int oldStateMiddle = GLFW_PRESS;
    int newStateMiddle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    if (newStateMiddle == GLFW_PRESS && oldStateMiddle == GLFW_RELEASE)
    {
        GAME_PAUSED = false;
        DEBUG_MODE = true;
        ITERATE = true;
    }

    oldStateMiddle = newStateMiddle;
}
// Função executada toda vez que há um redimensionamento de janela
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}

void bindBuffers(const float (&vertices)[20], const unsigned int (&indices)[6], unsigned int *VBO, unsigned int *VAO, unsigned int *EBO)
{
    // Vertices information

    // Generate VAO, VBO and EBO
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    // Bind buffers
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}