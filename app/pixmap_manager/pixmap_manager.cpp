#include "app/pixmap_manager/pixmap_manager.h"

PixmapManager* PixmapManager::ptr = nullptr;

PixmapManager *PixmapManager::Init(){
    if(!ptr){
        ptr = new PixmapManager();
    }
    else{
        return ptr;
    }
}

QPixmap& PixmapManager::getQPixmap(PixmapManager::Texture id){
    return this->m_textures.get(id);
}

PixmapManager::PixmapManager(){
}
