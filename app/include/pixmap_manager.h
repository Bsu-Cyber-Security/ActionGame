#pragma once

#include <QPixmap>

#include "resource_holder.h"

class PixmapManager {
   public:
    static PixmapManager* Init();
    static PixmapManager* Instance();
    QPixmap& getPixmap(TextureID id);
   private:
    PixmapManager();
    PixmapManager(PixmapManager& other) = delete;
    void operator=(const PixmapManager &) = delete;

    ResourceHolder<QPixmap, int> m_textures;
    inline static PixmapManager* ptr;
};
