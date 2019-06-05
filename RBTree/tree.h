#ifndef TREE_H
#define TREE_H
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QString>

enum Color {RED, BLACK, DOUBLE_BLACK};

struct node{
    int color;
    int val;
    bool src;
    node* batya;
    node* left;
    node* right;
};

class Tree : public QGraphicsScene{

    Q_OBJECT

public:
    Tree();
    void add(int va);
    void search(int va);
    void del(int val);
    void draw();
private:
    node* root;
    int size_c;
    node* deleteBST(node *&root, int val);
    node* minValueNode(node *&Node);
    void fixDeleteRBTree(node* Node);
    int getColor(node *&Node);
    void setColor(node *&Node, int color);
    node* insert(node* root, node* n);
    void insertRecurse(node* root, node* n);
    void insertFix(node* n);
    void insertCase1(node* n);
    void insertCase2(node* n);
    void insertCase3(node* n);
    void insertCase4(node* n);
    void insertCase4_2(node* n);
    void leftRotate(node* a);
    void rightRotate(node* a);
    node* batya(node* a);
    node* grandbatya(node* a);
    node* bro(node* a);
    node* uncle(node* a);
    void draw_left(node* a, int xp, int yp);
    void draw_right(node* a, int xp, int yp);
    int children_count(node* a);
};

#endif // TREE_H
