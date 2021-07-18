# :rocket: HW 6. Разработать программу для пакетной обработки команд.
Команды считываются построчно из стандартного ввода и обрабатываются блоками по N команд.
Одна команда - одна строка, конкретное значение роли не играет. Если данные закончились - блок
завершается принудительно. Параметр N передается как единственный параметр командной
строки в виде целого числа.

./bulk 3
| Ввод | Вывод | Комментарий |
|:----------------|:---------:|:----------------:|
| cmd1 | | |
| cmd2 | | |
| cmd3 | | |
|      | bulk: cmd1, cmd2, cmd3 | Блок завершён – выводим блок. |
| cmd4 | | |
| cmd5 | | |
| EOF | bulk: cmd4, cmd5 | Конец ввода – принудительно завершаем блок.|

Размер блока можно изменить динамически, если перед началом блока и сразу после дать
команды `{` и `}` соответственно. Предыдущий пакет при этом принудительно завершается. Такие
блоки могут быть включены друг в друга при этом вложенные команды `{` и `}` игнорируются (но не
сами блоки). Если данные закончились внутри динамического блока, весь динамический блок
игнорируется.
Логика работы для динамического размера блоков (в примере N == 3):

./bulk 3
| Ввод | Вывод | Комментарий |
|:----------------|:---------:|:----------------:|
| cmd1 | | |
| cmd2 | | |
| { | | |
|      | bulk: cmd1, cmd2 | Начало динамического блока – выводим предыдущий статический досрочно.|
| cmd3 | | |
| cmd4 | | |
| } | bulk: cmd3, cmd4 | Конец динамического блока – выводим.|
| { | | |
| cmd5 | | |
| cmd6 | | |
| { | | Игнорируем вложенные команды. |
| cmd7 | | |
| cmd8 | | |
| } | | Игнорируем вложенные команды. |
| cmd9 | | |
| } | bulk: cmd5, cmd6, cmd7, cmd8, cmd9 | Конец динамического блока – выводим. |
