#pragma once

#include "asset_manager.hpp"

class Locator
{
private:
	inline static AssetManager *m_assets = nullptr;

public:
	static inline void provide(AssetManager *assets) { m_assets = assets; }
	static inline AssetManager &assets() { return *m_assets; }
};
