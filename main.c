#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nmbr_of_marks 10
#define epsilon 1e-6

typedef struct Student_ {
    int id;
    double marks[nmbr_of_marks];// double чтобы сразу прибавлять к avg делением на 10
    double avg;
} Student;

typedef struct Node_ {
    double key;// avg
    int nmbr_of_students;// число студентов в данной вершине
    Student *same; // массив студентов с одинаковым avg
    struct Node_ *left;
    struct Node_ *right;
} Node;

Node *getNewNode(Student student) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (!newNode)
        return NULL;
    newNode->key = student.avg;
    newNode->nmbr_of_students = 1;
    newNode->same = (Student *) malloc(sizeof(Student));
    if (!newNode->same)
        return NULL;
    *(newNode->same) = student;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int equality_compare(double a1, double a2){
    if (fabs(a1 - a2) < epsilon)
        return 1;
    return 0;
}

Node *insert(Node *root, Student student) {
    if (root == NULL)
        return getNewNode(student);
    if (equality_compare(student.avg, root->key)) {
        root->same = (Student *) realloc(root->same, sizeof(student) * (root->nmbr_of_students+1));
        if (!root->same)
            return NULL;
        *(root->same + root->nmbr_of_students) = student;
        root->nmbr_of_students++;
    } else if (student.avg > root->key)
        root->right = insert(root->right, student);
    else
        root->left = insert(root->left, student);
    return root;
}

Node *removeNode(Node *root, double key) {// удаляет конкретную Ноду с avg = key
    if (root == NULL)
        return NULL;
    if (equality_compare(key, root->key)) { // если ключ совпал с текущим, то должен очистить текущую ноду
        if (!root->left && !root->right) { // если лист
            free(root);
            return NULL;
        } else if (!root->left && root->right) {// если есть только правый ребенок
            Node *right = root->right;
            free(root);
            return right;
        } else if (root->left && !root->right) {// если есть только левый ребенок
            Node *left = root->left;
            free(root);
            return left;
        } else { // если есть оба ребенка
            Node *FLeftNode = root->right;// ищет самого левого ребенка в правом ребенке
            while (FLeftNode->left)
                FLeftNode = FLeftNode->left;
            double temp;// меняет найденого ребенка с текущей нодой
            temp = root->key;
            root->key = FLeftNode->key;
            FLeftNode->key = temp;
            root->right = removeNode(root->right, key);
        }
    } else{ // если ключ не равен текущему ключа то идёт искать в детей
        root->left = removeNode(root->left, key);
        root->right = removeNode(root->right, key);
    }
    return root;
}

void memory_free(Node *root) {
    if (root == NULL)
        return;
    memory_free(root->left);
    memory_free(root->right);
    free(root->same);
    free(root);
}

int replacement(Node **tree, Node **base_root, int id, int mark_place, int new_mark) {
    // получаем корень дерева, id, место оценки, новую оценку
    //берём двойной указатель, чтобы изменять дерево в main
    if (*tree == NULL)
        return 0;
    for (int i = 0; i < (*tree)->nmbr_of_students; i++) { //проходим всю вершину в поисках нужного id
        if ((*tree)->same[i].id == id) {
            (*tree)->same[i].avg -= ((*tree)->same[i].marks[mark_place] /
                                     nmbr_of_marks); //из среднего значения убираем [mark_place] оценку
            (*tree)->same[i].marks[mark_place] = new_mark; //перезаписываем оценку
            (*tree)->same[i].avg += (*tree)->same[i].marks[mark_place] / nmbr_of_marks; // добавляем new_mark/10 к avg
            *base_root = insert(*base_root, (*tree)->same[i]);
            (*tree)->nmbr_of_students--; //теперь нужно его удалить из текущей ноды и заново поместить в дерево
            if ((*tree)->nmbr_of_students == 0) { //если студентов в вершине не осталось,
                // то удаляем конкретную вершину с её avg
                *tree = removeNode(*tree, (*tree)->key);
            } else { // если в вершине остались студенты,
                // то нужно их передвинуть, чтобы не было пустого места
                Student help = (*tree)->same[i];
                (*tree)->same[i] = (*tree)->same[(*tree)->nmbr_of_students];
                (*tree)->same[(*tree)->nmbr_of_students] = help; //поменяли местами
                // нужного студента с ненужным и реаллоком уничтожим ненужного
                // количество памяти теперь нам необходимое это количество оставшихся студентов * размер ноды студента
                (*tree)->same = (Student *) realloc((*tree)->same, sizeof(Student) * (*tree)->nmbr_of_students);
                if (!(*tree)->same)
                    return 0;
            }
            return 1;
        }
    }
    return replacement(&((*tree)->left), base_root, id, mark_place, new_mark) + replacement(&((*tree)->right),base_root, id, mark_place, new_mark);
    //заходит в детей если не вышел в вершине
}

int studentcount(Node *root) {
    if (root == NULL)
        return 0;
    return root->nmbr_of_students + studentcount(root->left) + studentcount(root->right);
}

int good_studentcount(Node *root, double avg) {
    if (root == NULL)
        return 0;
    int count = 0;
    if ((root->key > avg) || equality_compare(root->key,avg))
        count += root->nmbr_of_students;
    return count + good_studentcount(root->left, avg) + good_studentcount(root->right, avg);
}

int bad_std_search(Node *root, double p, double *key_remove) {
    if (root == NULL)
        return 0;
    if (root->key < p) {
        *key_remove = root->key;
        return 1;
    }
    return bad_std_search(root->left, p, key_remove);
}

int main() {
    char inf[256];
    Student cur_student;
    Node *tree = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r"), output = fopen("output.txt", "w");
    if ((input == NULL) || (output == NULL))
        return 1;
    fscanf(input, "%s", inf); // считываем ненужный STUDENTS:
    fscanf(input, "%s", inf); // считываем id первого студента
    while (strcmp(inf, "CHANGES:") != 0) { // считываем информацию обо всех студентах
        double avg = 0;
        cur_student.id = atoi(inf);  //function from stdlib.h. Записываем айди к студенту
        for (int i = 0; i < nmbr_of_marks; i++) {   //считываем 10 его оценок, попутно считая его среднюю
            fscanf(input, "%lf", &cur_student.marks[i]); //заполняем оценки студента
            avg += cur_student.marks[i] / nmbr_of_marks; //считаем среднюю студента, чтобы поместить его в дерево
        }
        cur_student.avg = avg; //записыаем avg к студенту
        tree = insert(tree, cur_student);//заносим студента в дерево
        fscanf(input, "%s", inf); //считываем id следующего студента
    }

    fscanf(input, "%s", inf); // считываем id
    int id, mark_place, new_mark;
    while (strcmp(inf, "BORDERS:") != 0) {
        id = atoi(inf);
        fscanf(input, "%d%d", &mark_place, &new_mark);
        replacement(&tree, &tree, id, mark_place, new_mark);
        fscanf(input, "%s", inf);
    }
    double k, p;
    fscanf(input, "%lf%lf", &k, &p);
    fclose(input);
    double key_remove; //будем менять key_remove через указатели
    while (bad_std_search(tree, k, &key_remove))
        tree = removeNode(tree, key_remove);
    fprintf(output, "%d %d", studentcount(tree), good_studentcount(tree, p));
    memory_free(tree);
    fclose(output);
    return 0;
}
