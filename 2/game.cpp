#include <SFML/Graphics.hpp>

const int TILE_SIZE = 40;
const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 10;

// Mảng đại diện cho mê cung: 1 là tường, 0 là đường đi
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main() {
    // Tạo cửa sổ trò chơi
    sf::RenderWindow window(sf::VideoMode(MAZE_WIDTH * TILE_SIZE, MAZE_HEIGHT * TILE_SIZE), "Maze Runner");

    // Tạo nhân vật người chơi
    sf::RectangleShape player(sf::Vector2f(TILE_SIZE - 4, TILE_SIZE - 4));
    player.setFillColor(sf::Color::Green);
    player.setPosition(1 * TILE_SIZE + 2, 1 * TILE_SIZE + 2); // Đặt nhân vật tại vị trí (1,1) trong mê cung

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Xử lý sự kiện di chuyển nhân vật
            if (event.type == sf::Event::KeyPressed) {
                sf::Vector2f pos = player.getPosition();
                int x = pos.x / TILE_SIZE;
                int y = pos.y / TILE_SIZE;

                if (event.key.code == sf::Keyboard::Up && maze[y - 1][x] == 0)
                    player.move(0, -TILE_SIZE);
                if (event.key.code == sf::Keyboard::Down && maze[y + 1][x] == 0)
                    player.move(0, TILE_SIZE);
                if (event.key.code == sf::Keyboard::Left && maze[y][x - 1] == 0)
                    player.move(-TILE_SIZE, 0);
                if (event.key.code == sf::Keyboard::Right && maze[y][x + 1] == 0)
                    player.move(TILE_SIZE, 0);
            }
        }

        window.clear();

        // Vẽ mê cung
        for (int i = 0; i < MAZE_HEIGHT; ++i) {
            for (int j = 0; j < MAZE_WIDTH; ++j) {
                if (maze[i][j] == 1) {
                    sf::RectangleShape wall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    wall.setFillColor(sf::Color::Blue);
                    wall.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(wall);
                }
            }
        }

        // Vẽ nhân vật
        window.draw(player);

        window.display();
    }

    return 0;
}