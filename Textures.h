#include <SFML/Graphics.hpp>
#include <memory>

class Textures {
public:
    static std::unique_ptr<sf::RenderTexture> empty;
    static std::unique_ptr<sf::RenderTexture> agent;
    static std::unique_ptr<sf::RenderTexture> food;

private:
    static int getTextureWidth();

    static int getTextureHeight();
};
