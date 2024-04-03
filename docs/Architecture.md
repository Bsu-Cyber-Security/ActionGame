# Архитектура


## Main modules:
- (5) Engine (обрабатывать события, т.е. логика игры)
- (3) Generator (генерация новых игровых карт)
- (5) Graphics (отрисовка событий)
- Asset Manager (загрузка изображений, данных пользователя)

## Classes
### Engine:
Methods:
- Initialization()
- RenderAction()
- Polling()
- Stop()

Memebers:
- state
- duration
- end_time
- player
- map

### Control:
methods:
- Polling()
- RenderEvent()

### Ghraphic:
*friend class Enginen*

methods:
- DrawCurrentState()
- CloseWindow() (Возможно обертка над стандартным методом)

members:
- Engine* - указатель на объект игры

Menu - отдельный класс или часть графики.


---
---

### FieldCell:
- type {enum}
- action
- texture

### Map:
- vector of FieldCELL

### Player:
- position
- state

