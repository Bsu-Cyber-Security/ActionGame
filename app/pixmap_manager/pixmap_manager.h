#pragma once

#include <QPixmap>

#include "app/resource_holder/resource_holder.h"

class PixmapManager {
   public:
    enum class Texture{Wall};
    static PixmapManager* Init();
    QPixmap& getQPixmap(Texture texture);
   private:
    PixmapManager();
    PixmapManager(PixmapManager& other) = delete;
    void operator=(const PixmapManager &) = delete;

    ResourceHolder<Texture, QPixmap> m_textures;
    static PixmapManager* ptr;
};
