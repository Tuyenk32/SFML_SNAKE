#pragma once
#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    //TITLE
    sf::Text m_gameOverTilte;
    //BUTTON to select in the GameOver
    sf::Text m_rePlayButton;
    sf::Text m_exitButton;
    //check replayButton
    bool m_rePlayButtonSelected;
    bool m_rePlayButtonPressed;
    //check exitButton
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    GameOver(std::shared_ptr<Context>& context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};