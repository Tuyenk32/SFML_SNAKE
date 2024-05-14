#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    :m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false),
    m_isExitButtonSelected(false), m_isExitButtonPressed(false), m_isDifficultyButtonPressed(false),
    m_isDifficultyButtonSelected(false), m_isInstructionButtonPressed(false), m_isInstructionButtonSelected(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "C:/Users/Admin/Desktop/GameC++/SFML_SNAKE/assets/fonts/Pacifico-Regular.ttf");

    //Title button
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setFillColor(sf::Color::Yellow);
    m_gameTitle.setString("Snake Game");
    //set the Tile to the center
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
        m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 100.f);

    //Play
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_playButton.setCharacterSize(20);


    //instruction 
    m_instructionButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_instructionButton.setString("Instruction");
    m_instructionButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2);
    m_instructionButton.setPosition(m_context->m_window->getSize().x / 2 - 25.f,
        m_context->m_window->getSize().y / 2);
    m_instructionButton.setCharacterSize(20);
    //choose mode
    m_difficultyButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_difficultyButton.setString("Difficulty");
    m_difficultyButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2);
    m_difficultyButton.setPosition(m_context->m_window->getSize().x / 2 - 25.f,
        m_context->m_window->getSize().y / 2 + 30.f);
    m_difficultyButton.setCharacterSize(20);
    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 60.f);
    m_exitButton.setCharacterSize(20);

}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                if (m_isPlayButtonSelected) {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                else if (m_isInstructionButtonSelected) {
                    m_isPlayButtonSelected = true;
                    m_isInstructionButtonSelected = false;
                }
                else if (m_isDifficultyButtonSelected) {
                    m_isInstructionButtonSelected = true;
                    m_isDifficultyButtonSelected = false;
                }
                else if (m_isExitButtonSelected) {
                    m_isDifficultyButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            case sf::Keyboard::Down:
                if (m_isPlayButtonSelected) {
                    m_isInstructionButtonSelected = true;
                    m_isPlayButtonSelected = false;
                }
                else if (m_isInstructionButtonSelected) {
                    m_isDifficultyButtonSelected = true;
                    m_isInstructionButtonSelected = false;
                }
                else if (m_isDifficultyButtonSelected) {
                    m_isExitButtonSelected = true;
                    m_isDifficultyButtonSelected = false;
                }
                else if (m_isExitButtonSelected) {
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            case sf::Keyboard::Return:
                m_isPlayButtonPressed = m_isPlayButtonSelected;
                m_isExitButtonPressed = m_isExitButtonSelected;
                m_isInstructionButtonPressed = m_isInstructionButtonSelected;
                m_isDifficultyButtonPressed = m_isDifficultyButtonSelected;
                break;
            }
        }
    }
}



void MainMenu::Update(const sf::Time& deltaTime)
{
    // Reset fill colors
    m_playButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
    m_instructionButton.setFillColor(sf::Color::White);
    m_difficultyButton.setFillColor(sf::Color::White);

    // Highlight selected button
    if (m_isPlayButtonSelected)
        m_playButton.setFillColor(sf::Color::Blue);
    if (m_isExitButtonSelected)
        m_exitButton.setFillColor(sf::Color::Blue);
    if (m_isInstructionButtonSelected)
        m_instructionButton.setFillColor(sf::Color::Blue);
    if (m_isDifficultyButtonSelected)
        m_difficultyButton.setFillColor(sf::Color::Blue);

    // Handle button press actions
    if (m_isPlayButtonPressed) {
        //go to play state
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed) {
        m_context->m_window->close();
    }
    else if (m_isInstructionButtonPressed) {
        // Transition to instruction state
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);

    }
    else if (m_isDifficultyButtonPressed) {
        // Transition to difficulty selection state
    }
}


void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Red);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_instructionButton);
    m_context->m_window->draw(m_difficultyButton);
    m_context->m_window->display();
}