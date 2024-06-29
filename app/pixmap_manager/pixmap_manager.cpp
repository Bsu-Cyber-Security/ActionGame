#include "app/pixmap_manager/pixmap_manager.h"

PixmapManager* PixmapManager::ptr = nullptr;

PixmapManager *PixmapManager::Instance(){
    if(!ptr){
        ptr = new PixmapManager();
    }
    else{
        return ptr;
    }
}
