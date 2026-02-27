# Progs

Набор учебных задач на C.

## Задачи

| Папка | Описание |
|-------|----------|
| `task-01-matrix` | Матрицы: путь, максимальные значения |
| `task-02-expression` | Парсер выражений с переменными |
| `task-03-matrix-det` | Вычисление определителя матрицы |
| `task-04-students` | Студенты и BST (деревья по среднему баллу) |
| `task-05-dijkstra` | Алгоритм Дейкстры |

## Сборка

```bash
cmake -B build
cmake --build build
```

## Запуск

После сборки исполняемые файлы находятся в `build/`:

- `build/task_01_matrix/task_01_matrix` — матрицы (ввод с stdin)
- `build/task_02_expression/task_02_expression` — парсер выражений (ввод с stdin)
- `build/task_03_matrix_det/task_03_matrix_det` — определитель (читает `input.txt`, пишет `output.txt`)
- `build/task_04_students/task_04_students` — студенты (читает `input.txt`, пишет `output.txt`)
- `build/task_05_dijkstra/task_05_dijkstra` — Дейкстра (читает `input.txt`, пишет `output.txt`)

На Windows добавьте `.exe` к именам файлов.

---

## Progs2 (задачи из PDF)

Тексты заданий для репозитория progs2:

### 1.1.2 — Класс String
Инкапсуляция, конструкторы, перегрузка операторов. Класс для работы со строками: конструкторы (по умолчанию, от char, от const char*), операторы +, +=, (), *, [], -. Демо: замена str2 на str3 в str1 (input.txt → output.txt).

### 2.1.1 — Иерархия выражений
Наследование и полиморфизм. Абстрактный Expression, производные Number, Variable, Add, Sub, Mul, Div. Парсинг, печать, дифференцирование, eval. Демо: дифференцирование по "x" (input.txt → output.txt).

### 3.2.1 — Шаблонный Vector
Шаблоны. Vector<T>: add, remove, [], LSH, RSH, print. Команды из файла (ADD, REMOVE, PRINT, UPDATE, LSH, RSH). Типы: I (int), D (double), S (string).

### 4.2.1 — Калькулятор
STL. Вычисление выражений с настраиваемыми приоритетом и ассоциативностью. std::map, std::stack, std::queue. Алгоритм сортировочной станции. Обработка деления на ноль.

### 5.1.1 — Web Crawler
Многопоточность. Перебор страниц, поиск ссылок, настраиваемое число потоков. Протокол file://. Выход: число страниц и время.
