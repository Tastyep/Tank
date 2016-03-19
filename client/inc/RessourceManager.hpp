#ifndef _RESSOURCEMANAGER_H_
#define _RESSOURCEMANAGER_H_

#include <map>
#include <memory>
#include <string>

template <typename T> class RessourceManager {
public:
  typedef std::map<std::string, std::shared_ptr<T>> ResourceMap;

public:
  RessourceManager() = default;
  virtual ~RessourceManager() = default;

  virtual std::shared_ptr<T> load(const std::string &path,
                                  const std::string &name) = 0;
  virtual void free(const std::string &) = 0;

  std::shared_ptr<T> get(const std::string &name);

protected:
  void addObject(const std::string &name, const std::shared_ptr<T> &resource);
  void removeObject(const std::string &name);

private:
  ResourceMap resources;
};

template <typename T>
std::shared_ptr<T> RessourceManager<T>::get(const std::string &name) {
  auto it = this->resources.find(name);

  if (it != this->resources.end())
    return (*it).second;
  return nullptr;
}

template <typename T>
void RessourceManager<T>::addObject(const std::string &name,
                                    const std::shared_ptr<T> &resource) {
  this->resources.insert(std::make_pair(name, resource));
}

template <typename T>
void RessourceManager<T>::removeObject(const std::string &name) {
  auto it = this->resources.find(name);

  if (it != this->resources.end())
    this->resources.erase(it);
}

#endif /* _RESSOURCEMANAGER_H_ */
