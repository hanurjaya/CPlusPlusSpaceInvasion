
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "RenderingManager.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free
#include "windows.h"

void SpawnAllObjects(bool onlyEnemy)
{
    if (!onlyEnemy)
    {
        //Player
        GameObjectManager::GetInstance()->AddGameObject(new Player(new SDL_FRect{ 0, 0, 60, 30 }, m_width, m_height, RenderingManager::GetInstance()->LoadTexture("player.png")));
    }
    //enemy
    float enemyAssetWidth{ 40 };
    float enemyAssetHeight{ 32 };
    for (int i = 0; i < 40; ++i)
    {
        const char* temp{};
        float yPos{ (enemyAssetHeight + 20) * (i / 8) + 60 };
        float scoreWight{0.0f};
        if (i < 8)
        {
            scoreWight = 100.0f;
            temp = "red.png";
        }
        else if (i < 24)
        {
            scoreWight = 50.0f;
            temp = "green.png";
        }
        else
        {
            scoreWight = 20.0f;
            temp = "yellow.png";
        }
        SDL_FRect* enemyDestPost{ new SDL_FRect{ (240 + ((m_width / 2) - (enemyAssetWidth / 2)) - ((enemyAssetWidth + 20) * (i % 8))), yPos, enemyAssetWidth, enemyAssetHeight } };
        GameObjectManager::GetInstance()->AddGameObject(new Enemy(new SDL_FRect{ 0, 0, enemyAssetWidth, enemyAssetHeight }, enemyDestPost, RenderingManager::GetInstance()->LoadTexture(temp), scoreWight));
    }
}
int main(int argc, char* argv[])
{
    //For Memory Leak Checker
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld); //take a snapshot

    if (!RenderingManager::GetInstance()->TryInit(m_width, m_height))
    {
        GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
    }

    GameStateManager::GetInstance()->SetGameState(GameStateManager::StartMenu);

    const char* titleUp{ "=============================================================================" };
    const char* title{ "Invasion from Space By Hanbolana!" };
    const char* instruction{ "Press Enter to Play!" };
    const char* instructionExit{ "Press Esc to Exit :(" };
    const char* score{ "Total Score: " };
    const char* scoreDown{ "*********************************************************************************" };
    const char* gameOver{ "Game Over!" };
    const char* endResultText{ "Play Again? Y / N" };
    UIManager::GetInstance()->AddText( "titleUp", titleUp, UIManager::CenterTextXPos(strlen(titleUp), m_width), (float)((m_height / 6) - (2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE)), GameStateManager::StartMenu);
    UIManager::GetInstance()->AddText( "title", title, UIManager::CenterTextXPos(strlen(title), m_width), (float)(m_height / 6), GameStateManager::StartMenu);
    UIManager::GetInstance()->AddText( "titleDown", titleUp, UIManager::CenterTextXPos(strlen(titleUp), m_width), (float)((m_height / 6) + (2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE)), GameStateManager::StartMenu);
    UIManager::GetInstance()->AddText( "instruction",instruction, UIManager::CenterTextXPos(strlen(instruction), m_width), (float)(m_height / 2), GameStateManager::StartMenu);
    UIManager::GetInstance()->AddText( "instructionExit", instructionExit, UIManager::CenterTextXPos(strlen(instructionExit), m_width), (float)((m_height / 2) + (2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE)), GameStateManager::StartMenu);
    UIManager::GetInstance()->AddText( "score", score, 0.0f, (float)(SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), GameStateManager::InGame, 1.5f);
    UIManager::GetInstance()->AddText( "scoreDown", scoreDown, UIManager::CenterTextXPos(strlen(scoreDown), m_width), (float)(4 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), GameStateManager::InGame);
    UIManager::GetInstance()->AddText( "GameOver", gameOver, UIManager::CenterTextXPos(strlen(gameOver), m_width), (float)(m_height / 6), GameStateManager::GameOver);
    UIManager::GetInstance()->AddText("EndScore", score, UIManager::CenterTextXPos(strlen(score), m_width), (float)(m_height / 6) + (2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), GameStateManager::GameOver);
    UIManager::GetInstance()->AddText("endResultText", endResultText, UIManager::CenterTextXPos(strlen(endResultText), m_width), (float)(m_height / 6) + (4 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), GameStateManager::GameOver);

    GameObjectManager::GetInstance()->SetRenderer(RenderingManager::GetInstance()->GetRenderer());
    
    while (GameStateManager::GetInstance()->GetGameState() != GameStateManager::Exit)
    {
        InputManager::GetInstance()->Update();
        if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame && GameObjectManager::GetInstance()->GetPlayer() == nullptr)
        {
            GameObjectManager::GetInstance()->DestroyAllGameObject();
            SpawnAllObjects(false);
        }
        else if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame && GameObjectManager::GetInstance()->IsNeedToRespawnEnemy())
        {
            SpawnAllObjects(true);
        } 
        //Update Score
        std::string tempFinalScoreText{ score };
        tempFinalScoreText += std::to_string(GameObjectManager::GetInstance()->GetTotalScore());
        UIManager::GetInstance()->UpdateText("score", 
            tempFinalScoreText.c_str(),
            0.0f,
            (float)(SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE),
            GameStateManager::InGame);

        UIManager::GetInstance()->UpdateText("EndScore", 
            tempFinalScoreText.c_str(),
            UIManager::CenterTextXPos(strlen(tempFinalScoreText.c_str()), m_width),
            (float)(m_height / 6) + (2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), 
            GameStateManager::GameOver);

        UIManager::GetInstance()->Update();
        RenderingManager::GetInstance()->Update();
        if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame)
        {
            GameObjectManager::GetInstance()->Update();
        }
    }
    GameObjectManager::GetInstance()->DestroyAllGameObject();
    delete UIManager::GetInstance();
    delete InputManager::GetInstance();
    delete GameObjectManager::GetInstance();
    delete GameStateManager::GetInstance();
    delete RenderingManager::GetInstance();
    
    //For Memory Leak Checker
    _CrtMemCheckpoint(&sNew); //take a snapshot 
    if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
    {
        OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
        _CrtMemDumpStatistics(&sDiff);
        OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
        _CrtMemDumpAllObjectsSince(&sOld);
        OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
        _CrtDumpMemoryLeaks();
    }    
    else
    {
        OutputDebugString(L"----------- NoMemoryLeakDetected ---------");
    }
    return 0;
}