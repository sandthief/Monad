#include <Common.hpp>
#include <TextureManager.hpp>

using namespace std;

std::vector<Texture> textures;

Texture::Texture(string nameIn,sf::Texture texture) {
	_texture = texture;
	name = nameIn;

}

sf::Texture TextureManager::get(string nameIn) {
	for(int t = 0; t < textures.size(); t++) {
		if(textures[t].name == nameIn) {
			return textures[t]._texture;
		}
	}

	sf::Texture currentTexture;
	currentTexture.setRepeated(true);
	
	if (!currentTexture.loadFromFile(nameIn)) {
	    std::cout << "Could not load " << nameIn;
	    return get("resources/models/default.bmp");
	}
	else {
		textures.push_back(Texture(nameIn,currentTexture));
		return currentTexture;
	}

}
