#include "GameManager.hpp"

 GameManager::GameManager(RenderingWindow& renderwindow,
                TextureManager& textureManager,
                Audio& audio,
                Input& input,
                Render& render,
                Config& config,
                Snake& snake,
                Menu& menu)
        : renderwindow(renderwindow),
          textureManager(textureManager),
          audio(audio),
          input(input),
          render(render),
          config(config),
          snake(snake),
          menu(menu),
          state(GameState::MENU),
          moveCounter(0.0f),
          score(0),
          gameOver(false),
          quit(false) {}

void GameManager::Update(float deltaTime) {
    moveCounter -= deltaTime;
    if (moveCounter <= 0) {
        snake.Update();
        moveCounter = config.SNAKE_BASE_SPEED - (score * config.SPEED_BUMP);
        moveCounter = std::max(moveCounter, config.SNAKE_MAX_SPEED);
    }
}
void GameManager::Run()
{

}
void GameManager::nRender()
{

}