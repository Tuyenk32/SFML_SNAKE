#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    //TITLE
    sf::Text m_gameTitle;
    //BUTTON to select in the mainMenu
    sf::Text m_playButton;
    sf::Text m_exitButton;
    sf::Text m_instructionButton;
    sf::Text m_difficultyButton;
    //check buttonPlay
    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    //choose Difficultty 

    //check exitButton
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

    bool m_isDifficultyButtonPressed;
    bool m_isDifficultyButtonSelected;
    bool m_isInstructionButtonPressed;
    bool m_isInstructionButtonSelected;
public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};