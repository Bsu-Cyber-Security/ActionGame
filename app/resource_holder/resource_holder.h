#pragma once

#include <map>
#include <memory>
#include <QString>

template <class Identifier, class Resource>
class ResourceHolder {
    public:
        void load(Identifier id, const QString &filename);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        std::map<Identifier, std::unique_ptr<Resource>>	m_resources;
};
