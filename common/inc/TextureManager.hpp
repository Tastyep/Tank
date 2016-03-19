#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "RessourceManager.hpp"
#include "Singleton.hpp"
#include <SFML/Graphics.hpp>

template <typename T = sf::Texture>
class TextureManager : public RessourceManager<T>,
                       public Singleton<TextureManager<T>> {
public:
  virtual ~TextureManager() = default;
  std::shared_ptr<T> load(const std::string &path, const std::string &name) {
    std::shared_ptr<T> texture(new T);

    if (!texture->loadFromFile(path))
      throw(std::runtime_error("Can't load texture " + path));
    this->addObject(name, texture);
    return texture;
  }

  void free(const std::string &name) { this->removeObject(name); }
};

#endif /* _TEXTUREMANAGER_H_ */
