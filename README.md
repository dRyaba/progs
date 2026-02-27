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
