#pragma once                                                                                                                                          #pragma once
#include <Qmap>
#include <QDebug>
#include <memory>
#include <QString>

template <class Identifier, class Resource>
class ResourceHolder {
   public:
    ResourceHolder(ResourceHolder& other) = delete;
    void operator=(const ResourceHolder&)=delete;

    void load(Identifier id, const QString &filename);
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
   private:
    ResourceHolder() = default;
    bool insertResource(Identifier id, std::unique_ptr<Resource> resource);

   private:
    QMap<Identifier, std::unique_ptr<Resource>>  m_resources;
};

template<class Identifier, class Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const QString &filename)
{
    std::unique_ptr<Resource> resource = new Resource();
    if(!resource->load(filename)){
        qDebug()<<"Failed to loaad "<<filename;
    }
    else{
        bool successful = insertResource(id, std::move(resource));
        if(!successful){
            qDebug()<<"Failed to insert resource";
        }
    }
}

template<class Identifier, class Resource>
Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) {
    auto found = m_resources.find(id);
    if (found != m_resources.end()) {
        return *found->second;
    } else {
        throw std::runtime_error("Resource not found.");
    }
    return *found->second;
}

template<class Identifier, class Resource>
const Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) const{
    auto found = m_resources.find(id);
    if (found != m_resources.end()) {
        return *found->second;
    } else {
        throw std::runtime_error("Resource not found.");
    }
}

template<class Identifier, class Resource>
bool ResourceHolder<Identifier, Resource>::insertResource(Identifier id, std::unique_ptr<Resource> resource) {
    auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
    if (!inserted.second) {
        return false;
    }
    return true;
}
