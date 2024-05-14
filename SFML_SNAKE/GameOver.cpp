#include "GameOver.hpp"
#include "SFML/Window/Event.hpp"
#include "GamePlay.hpp"
GameOver::GameOver(std::shared_ptr<Context>& context)
    :m_context(context), m_rePlayButtonSelected(true), m_rePlayButtonPressed(false),
    m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{
}
GameOver::~GameOver() {

}

void GameOver::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "D:/2D-Snake-Game/assets/fonts/Pacifico-Regular.ttf");

    //Title button
    m_gameOverTilte.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTilte.setFillColor(sf::Color::Yellow);
    m_gameOverTilte.setString("Game Over");
    //set the Tile to the center
    m_gameOverTilte.setOrigin(m_gameOverTilte.getLocalBounds().width / 2,
        m_gameOverTilte.getLocalBounds().height / 2);
    m_gameOverTilte.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 100.f);

    //Play
    m_rePlayButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_rePlayButton.setString("Replay");
    m_rePlayButton.setOrigin(m_rePlayButton.getLocalBounds().width / 2,
        m_rePlayButton.getLocalBounds().height / 2);
    m_rePlayButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_rePlayButton.setCharacterSize(20);

    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 25.f);
    m_exitButton.setCharacterSize(20);

}

void GameOver::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        //check close event
        if (event.type == sf::Event::Closed) {

            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) // store the key that pressed
            {
            case sf::Keyboard::Up: {
                if (!m_rePlayButtonSelected) { //keep looping between 2 option 
                    m_rePlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down: {
                if (!m_isExitButtonSelected) { //keep looping between 2 option 
                    m_rePlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return: {
                //enter selection to choose
                m_rePlayButtonPressed = false;
                m_isExitButtonPressed = false;
                if (m_rePlayButtonSelected) {
                    m_rePlayButtonPressed = true;
                }
                else {
                    m_isExitButtonPressed = true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void GameOver::Update(const sf::Time& deltaTime)
{
    if (m_rePlayButtonSelected) {
        m_rePlayButton.setFillColor(sf::Color::Blue);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else {
        m_rePlayButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Blue);
    }
    if (m_rePlayButtonPressed) {
        //go to play state
       /* m_rePlayButton.setColor(sf::Color::Magenta);*/

        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed) {
        /* m_exitButton.setColor(sf::Color::Magenta);*/
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Red);
    m_context->m_window->draw(m_gameOverTilte);
    m_context->m_window->draw(m_rePlayButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}