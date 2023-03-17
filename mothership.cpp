#include "headers/mothership.h"

Mothership::Mothership(unsigned int *VAO, unsigned int rows, unsigned int columns) : m_VAO(VAO), m_Rows(rows), m_Columns(columns)
{
    m_EnemyArmy = new Enemy *[rows];
    //m_FrontRowEnemies = new Enemy[columns];
    m_FrontRowEnemies = new int[columns];
    for (int i = 0; i < rows; i++)
    {
        m_EnemyArmy[i] = new Enemy[columns];
    }
    for (int i = 0; i < columns; i++)
        m_FrontRowEnemies[i] = 0;
}

void Mothership::SetEnemies(Shader *shaderProgram, Texture *alien1, Texture *alien2, Texture *alien3, Texture *alien4)
{
    for (int i = 0; i < m_Rows; i++)
    {
        for (int j = 0; j < m_Columns; j++)
        {
            float spacing = 32.0f / float(WIDTH) * 8;
            float position[2] = {-0.4f + j * spacing, 0.4f + i * spacing};
            if (i % 4 == 0)
                m_EnemyArmy[i][j] = Enemy(shaderProgram, alien1, position);
            else if (i % 4 == 1)
                m_EnemyArmy[i][j] = Enemy(shaderProgram, alien2, position);
            else if (i % 4 == 2)
                m_EnemyArmy[i][j] = Enemy(shaderProgram, alien3, position);
            else if (i % 4 == 3)
                m_EnemyArmy[i][j] = Enemy(shaderProgram, alien4, position);
        }
    }
}

void Mothership::Move(float velocity, std::string direction)
{
    for (int i = 0; i < m_Rows; i++)
        for (int j = 0; j < m_Columns; j++)
            m_EnemyArmy[i][j].move(velocity, direction);
}

void Mothership::Movement(float boundary)
{
    bool hitRightWall = m_EnemyArmy[m_Rows - 1][m_Columns - 1].getX() >= boundary;
    bool hitLeftWall = m_EnemyArmy[0][0].getX() <= -1.0f * boundary;
    bool hitWall = hitRightWall || hitLeftWall;
    if (m_Direction == "NO DIRECTION")
    {
        m_Direction = "RIGHT";
        Move(m_Velocity, m_Direction);
    }
    else if (hitWall && m_Direction != "DOWN")
    {
        m_Direction = "DOWN";
        Move(1000 * m_Velocity, m_Direction);
    }
    else if (hitRightWall)
    {
        m_Direction = "LEFT";
        Move(m_Velocity, m_Direction);
    }
    else if (hitLeftWall)
    {
        m_Direction = "RIGHT";
        Move(m_Velocity, m_Direction);
    }
    else
        Move(m_Velocity, m_Direction);
}

void Mothership::UpdateFrontRow(int i, int j)
{
    if (m_FrontRowEnemies[j] == i)
    {
        if (i >= m_Rows - 1)
            m_FrontRowEnemies[j] = -1;
        else
            m_FrontRowEnemies[j]++;
    }
}

void Mothership::Collision(Gun *gun)
{
    for (int i = 0; i < m_Rows; i++)
    {
        for (int j = 0; j < m_Columns; j++)
        {
            if (m_EnemyArmy[i][j].isAlive())
            {
                float enemyPosition[2] = {m_EnemyArmy[i][j].getX(), m_EnemyArmy[i][j].getY()};
                if (gun->BulletHit(enemyPosition))
                {
                    m_EnemyArmy[i][j].kill();
                    UpdateFrontRow(i, j);
                    break;
                }
            }
        }
    }
}

void Mothership::SetGun(Shader *shader, Texture *texture)
{
    m_Gun = Gun(shader, texture, 0.003f, "DOWN");
}

void Mothership::Shoot()
{
    std::srand(int(1000 * glfwGetTime()));
    int r = std::rand() % m_Columns;
    int x = m_FrontRowEnemies[r];
    if (x >= 0)
        m_Gun.Fire(m_EnemyArmy[x][r].getPosition());
}

void Mothership::Draw()
{
    for (int i = 0; i < m_Rows; i++)
    {
        for (int j = 0; j < m_Columns; j++)
        {
            m_EnemyArmy[i][j].Draw(m_VAO);
        }
    }
}
void Mothership::BulletLoop()
{
    float time = glfwGetTime();
    time = time - float(floor(time)) + float(int(floor(time)) % 3);
    if (time >= 0.0f && time <= 0.007f)
        Shoot();
    m_Gun.Move();
}

void Mothership::BulletDraw()
{
    m_Gun.Draw(m_VAO);
}

bool Mothership::EnemiesWon()
{
    for (int i = 0; i < m_Rows; i++)
        for (int j = 0; j < m_Columns; j++)
            if (m_EnemyArmy[i][j].getPosition()[1] < -0.2f)
            {
                return true;
                break;
            }
    return false;
}
bool Mothership::EnemiesLoose()
{
    for (int i = 0; i < m_Rows; i++)
        for (int j = 0; j < m_Columns; j++)
            if (m_EnemyArmy[i][j].isAlive())
            {
                return false;
                break;
            }
    return true;
}
void Mothership::Delete()
{
    for (int i = 0; i < m_Rows; ++i)
        delete[] m_EnemyArmy[i];
    delete[] m_EnemyArmy;
}
