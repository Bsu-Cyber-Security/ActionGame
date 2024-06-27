#pragma once

#include <Qmap>
#include <memory>
#include <QString>

template <class Identifier, class Resource>
class ResourceHolder {
    public:
        void oad(Identifier id, const QString &filename);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

        ResourceHolder& instance();

    private:
        ResourceHolder() = default;
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        Qmap<Identifier, std::unique_ptr<Resource>>	m_resources;
};
