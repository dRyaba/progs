#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nmbr_of_marks 10
#define epsilon 1e-6

typedef struct Student_ {
    int id;
    double marks[nmbr_of_marks];
    double avg;
} Student;

typedef struct Node_ {
    double key;
    int nmbr_of_students;
    Student *same;
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
        root->same = (Student *) realloc(root->same, sizeof(Student) * (root->nmbr_of_students+1));
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

Node *removeNode(Node *root, double key) {
    if (root == NULL)
        return NULL;
    if (equality_compare(key, root->key)) {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        } else if (!root->left && root->right) {
            Node *right = root->right;
            free(root);
            return right;
        } else if (root->left && !root->right) {
            Node *left = root->left;
            free(root);
            return left;
        } else {
            Node *FLeftNode = root->right;
            while (FLeftNode->left)
                FLeftNode = FLeftNode->left;
            double temp;
            temp = root->key;
            root->key = FLeftNode->key;
            FLeftNode->key = temp;
            root->right = removeNode(root->right, key);
        }
    } else {
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
    if (*tree == NULL)
        return 0;
    for (int i = 0; i < (*tree)->nmbr_of_students; i++) {
        if ((*tree)->same[i].id == id) {
            (*tree)->same[i].avg -= ((*tree)->same[i].marks[mark_place] /
                                     nmbr_of_marks);
            (*tree)->same[i].marks[mark_place] = new_mark;
            (*tree)->same[i].avg += (*tree)->same[i].marks[mark_place] / nmbr_of_marks;
            *base_root = insert(*base_root, (*tree)->same[i]);
            (*tree)->nmbr_of_students--;
            if ((*tree)->nmbr_of_students == 0) {
                *tree = removeNode(*tree, (*tree)->key);
            } else {
                Student help = (*tree)->same[i];
                (*tree)->same[i] = (*tree)->same[(*tree)->nmbr_of_students];
                (*tree)->same[(*tree)->nmbr_of_students] = help;
                (*tree)->same = (Student *) realloc((*tree)->same, sizeof(Student) * (*tree)->nmbr_of_students);
                if (!(*tree)->same)
                    return 0;
            }
            return 1;
        }
    }
    return replacement(&((*tree)->left), base_root, id, mark_place, new_mark) + replacement(&((*tree)->right),base_root, id, mark_place, new_mark);
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
    fscanf(input, "%s", inf);
    fscanf(input, "%s", inf);
    while (strcmp(inf, "CHANGES:") != 0) {
        double avg = 0;
        cur_student.id = atoi(inf);
        for (int i = 0; i < nmbr_of_marks; i++) {
            fscanf(input, "%lf", &cur_student.marks[i]);
            avg += cur_student.marks[i] / nmbr_of_marks;
        }
        cur_student.avg = avg;
        tree = insert(tree, cur_student);
        fscanf(input, "%s", inf);
    }

    fscanf(input, "%s", inf);
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
    double key_remove;
    while (bad_std_search(tree, k, &key_remove))
        tree = removeNode(tree, key_remove);
    fprintf(output, "%d %d", studentcount(tree), good_studentcount(tree, p));
    memory_free(tree);
    fclose(output);
    return 0;
}
