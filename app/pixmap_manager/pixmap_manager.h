#pragma once

#include <QPixmap>

#include "app/resource_holder/resource_holder.h"

class PixmapManager {
   public:
    static PixmapManager* Init();
    static PixmapManager* Instance();
    QPixmap& getPixmap(int texture_id);
   private:
    PixmapManager();
    PixmapManager(PixmapManager& other) = delete;
    void operator=(const PixmapManager &) = delete;

    ResourceHolder<int, QPixmap> m_textures;
    inline static PixmapManager* ptr;
};
