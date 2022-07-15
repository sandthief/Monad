#ifndef TEXTURE_MANAGER__H
#define TEXTURE_MANAGER__H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class  Texture {
	public:
		std::string name;
		sf::Texture _texture;

		Texture(std::string,sf::Texture);
};

class TextureManager {
	public:
		static sf::Texture get(std::string name);
};

#endif
