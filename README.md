# Arkanoid 
Классическая аркада, реализованная на **C++** и **SDL2**  

## Управление

| Кнопка                | Действие                  |
|------------------------|---------------------------|
| 🖱️ Движение мышью      | Перемещение платформы     |
| 🖱️ ЛКМ / Клик мыши     | Запустить мяч             |
| ❌ Закрыть окно        | Выход из игры             |

---

## Типы блоков

| Тип блока        | Цвет        | Характеристика                      |
|------------------|-------------|-------------------------------------|
| 🟨 Обычный        | Жёлтый      | Разрушается с одного удара          |
| 🟩 Бонусный       | Зелёный     | Дропает случайный бонус             |
| 🟧 Прочный (x2)   | Оранжевый   | Требует 2 удара                     |
| 🟥 Прочный (x3)   | Красный     | Требует 3 удара                     |
| ⬜ Неразрушимый   | Серый       | Не уничтожается                     |

---

## Бонусы

При разрушении **BONUS**-блока может выпасть один из следующих бонусов:

| Бонус              | Цвет        | Эффект                                                  |
|---------------------|-------------|----------------------------------------------------------|
| 🔴 Extra Ball        | Красный     | Добавляет второй шар в игру        |
| 🟦 Expand Paddle     | Голубой     | Увеличивает ширину платформы                             |
| 🟠 Speed Up          | Оранжевый   | Увеличивает скорость всех мячей                          |
| 🟢 Sticky            | Зелёный     | Мячи прилипают к платформе при касании (до 3 раз)       |
| 🟣 Safety Bottom     | Фиолетовый  | Позволяет один раз спасти мяч, упавший ниже экрана       |

---

## Очки

| Действие                        | Очки     |
|----------------------------------|----------|
| Разрушение обычного блока       | +10      |
| Повреждение прочного блока      | +5       |
| Потеря последнего мяча          | -10      |

Очки отображаются в верхней левой части приложения в его названии (потому что к sdl не подключились шрифты)
