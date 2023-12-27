#include "assets/asset_manager.hpp"
#include "assets/shaders.hpp"

class Game
{
private:
	AssetManager m_assets;

public:
	Game();

	void run();
};