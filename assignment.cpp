#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "snake.hpp"
#include "food.hpp"

int main()
{
    // game constants
    const int cellSize = 20;
    const int gridWidth = 20;
    const int gridHeight = 20;
    const int windowWidth = gridWidth * cellSize;
    const int windowHeight = gridHeight * cellSize;

    const float moveDelay = 0.15f; // seconds between moves

    //random seed for food
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    // Create window for game
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "B-2 Bomber");
    window.setFramerateLimit(60);
    
    // Create snake and food
    Snake snake(gridWidth / 2, gridHeight / 2);
    Food food;
    food.spawn(gridWidth, gridHeight, snake);

    //movement timer
    sf::Clock moveClock;
    bool gameOver = false;

    while (window.isOpen()) {
        // Handle window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //handle keyboard for direction and prevent 180 turn
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.getDirY() != 1) {
            snake.setDirection(0, -1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.getDirY() != -1) {
            snake.setDirection(0, 1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.getDirX() != 1) {
            snake.setDirection(-1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.getDirX() != -1) {
            snake.setDirection(1, 0);
        }

        // Update snake position on a timer
        if (!gameOver && moveClock.getElapsedTime().asSeconds() >= moveDelay) {
            moveClock.restart();

            // Decide where the head will go next
            Segment nextHead = snake.getNextHead();

            // Check wall collision
            if (nextHead.x < 0 || nextHead.x >= gridWidth || nextHead.y < 0 || nextHead.y >= gridHeight) {
                gameOver = true;
            }

            // Check self collision
            if (!gameOver && snake.willHitSelf(nextHead)) {
                gameOver = true;
            }

            if (!gameOver) {
                Segment foodPos = food.getPosition();
                bool ateFood = (nextHead.x == foodPos.x && nextHead.y == foodPos.y);


                // Move snake, grow if it just ate
                snake.move(nextHead, ateFood);

                //check food
                if (ateFood) {
                    // grow: don't pop tail
                    food.spawn(gridWidth, gridHeight, snake);
                }
            } else {
                //Simple restart after a crash
                snake.reset(gridWidth / 2, gridHeight / 2);
                food.spawn(gridWidth, gridHeight, snake);
                moveClock.restart();
                gameOver = false;
            }
        }

        // Draw everything
        window.clear(sf::Color(0, 20, 0));// dark green background

        // Draw target (crosshair)
        Segment foodPos = food.getPosition();

        // center of this grid cell in pixels
        float targetCenterX = foodPos.x * cellSize + cellSize / 2.0f;
        float targetCenterY = foodPos.y * cellSize + cellSize / 2.0f;

        // ring
        sf::CircleShape ring(cellSize / 2.5f);
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineColor(sf::Color::Red);
        ring.setOutlineThickness(1.5f);
        ring.setOrigin(ring.getRadius(), ring.getRadius());
        ring.setPosition(targetCenterX, targetCenterY);

        // horizontal line
        sf::RectangleShape hLine(sf::Vector2f(cellSize / 2.0f, 2.f));
        hLine.setFillColor(sf::Color::Red);
        hLine.setOrigin(hLine.getSize().x / 2.0f, hLine.getSize().y / 2.0f);
        hLine.setPosition(targetCenterX, targetCenterY);

        // vertical line
        sf::RectangleShape vLine(sf::Vector2f(2.f, cellSize / 2.0f));
        vLine.setFillColor(sf::Color::Red);
        vLine.setOrigin(vLine.getSize().x / 2.0f, vLine.getSize().y / 2.0f);
        vLine.setPosition(targetCenterX, targetCenterY);

        window.draw(ring);
        window.draw(hLine);
        window.draw(vLine);

        // Draw bomber formation (each segment as a B-2-like triangle)
        const std::deque<Segment>& body = snake.getBody();

        for (std::size_t i = 0; i < body.size(); ++i) {
            // Center of this grid cell in pixels
            float centerX = body[i].x * cellSize + cellSize / 2.0f;
            float centerY = body[i].y * cellSize + cellSize / 2.0f;

        // 3-point "circle" = triangle
        sf::CircleShape bomberShape(cellSize / 2.0f, 3);
        bomberShape.setOrigin(bomberShape.getRadius(), bomberShape.getRadius());
        bomberShape.setPosition(centerX, centerY);

        // Color and size: head brighter, followers smaller/darker
        if (i == 0) {
            // lead B-2
            bomberShape.setFillColor(sf::Color(120, 120, 120));
        } else {
            // trailing bombers
            // fade the shade a bit as i increases
            int shade = 110 - static_cast<int>(
                (static_cast<float>(i) / body.size()) * 40.0f
            );
            if (shade < 70) shade = 70;
            bomberShape.setFillColor(sf::Color(shade, shade, shade));
            bomberShape.setScale(0.75f, 0.75f);
        }

        // Figure out direction for this segment so the triangle points "forward"
        int dirX = 0;
        int dirY = 0;

        if (i == 0) {
            // head uses the snake's current direction
            dirX = snake.getDirX();
            dirY = snake.getDirY();
        } else {
            // body segments point toward the previous segment
            int dx = body[i - 1].x - body[i].x;
            int dy = body[i - 1].y - body[i].y;
            dirX = dx;
            dirY = dy;
        }

        float rotation = 0.f;
        // up = 0, right = 90, down = 180, left = 270.
        if (dirX == 0 && dirY == -1) {
            rotation = 0.f;          // moving up
        } else if (dirX == 1 && dirY == 0) {
            rotation = 90.f;         // moving right
        } else if (dirX == 0 && dirY == 1) {
            rotation = 180.f;        // moving down
        } else if (dirX == -1 && dirY == 0) {
            rotation = 270.f;        // moving left
        }

        bomberShape.setRotation(rotation);
        window.draw(bomberShape);
    }
        
        window.display();
    }

    return 0;
}