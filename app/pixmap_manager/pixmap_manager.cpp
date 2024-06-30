#include "app/pixmap_manager/pixmap_manager.h"
#include  <QString>

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
    this->m_textures.load(Texture::Fon, "C:/Users/vtali/Documents/ActionGame/Resource/photo_2024-06-30_23-46-01.jpg");
}
