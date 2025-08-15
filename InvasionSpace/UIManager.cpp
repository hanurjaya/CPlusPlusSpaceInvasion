#include "UIManager.h"

UIManager* UIManager::m_UIManagerInstance = nullptr;

UIManager::UIManager()
{

}

float UIManager::CenterTextXPos(size_t textLength, size_t screenWidth, float scale)
{
	return (float)((screenWidth / 2) - ((textLength / 2) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale));;
}

UIManager* UIManager::GetInstance()
{
	if (m_UIManagerInstance == nullptr)
	{
		m_UIManagerInstance = new UIManager();
	}
	return m_UIManagerInstance;
}

const std::map<std::string, UIManager::TextInfo> UIManager::GetCurrentTextsList()
{
	return m_currentList;
}

void UIManager::AddText(const char* textname, const char* textContent, float posX, float posY, GameStateManager::GameState gameState, float renderScale)
{
	m_stringList[gameState].insert(std::pair { textname, TextInfo{textContent, posX, posY , renderScale}});
}

void UIManager::UpdateText(const char* textName, const char* textContent, float posX, float posY, GameStateManager::GameState gameState)
{
	auto checkState = m_stringList.find(gameState);
	if (checkState != m_stringList.end())
	{
		auto checkName = m_stringList[gameState].find(textName);
		if (checkName != m_stringList[gameState].end())
		{
			m_stringList[gameState][textName].text = textContent;
			m_stringList[gameState][textName].x = posX;
			m_stringList[gameState][textName].y = posY;
		}
	}
}

void UIManager::Update()
{
	if (m_lastState != GameStateManager::GetInstance()->GetGameState())
	{
		m_currentList.clear();
		m_currentList = m_stringList[GameStateManager::GetInstance()->GetGameState()];
	}
}

