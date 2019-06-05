#include "tree.h"

Tree::Tree()
{
    root = nullptr;
    size_c = 25;
    setBackgroundBrush(QBrush(Qt::white,Qt::SolidPattern));
}

void Tree::add(int va)
{
    node* N = new node();
    N->val = va;
    N->src = false;
    root = insert(root,N);
    draw();
}

void Tree::search(int va)
{
    node* i = root;
    while ((i != nullptr) && (i->val != va)){
        if (va > i->val){
            i = i->right;
        }
        if (va < i->val){
            i = i->left;
        }
    }
    if (i == nullptr){
        draw();
        return;
    }
    i->src = true;
    draw();
}

void Tree::draw()
{
    clear();
    if (root == nullptr){
        return;
    }
    if (root->src){
        addEllipse(0,0,size_c,size_c,Qt::SolidLine,Qt::green);
        root->src = false;
    }
    else{
        addEllipse(0,0,size_c,size_c,Qt::SolidLine,Qt::black);
    }
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(0,0);
    io->setPlainText(QString::number(root->val));
    addItem(io);
    draw_left(root->left,0,0);
    draw_right(root->right,0,0);
}

void Tree::del(int val){
    node* tmp = deleteBST(root, val);
    fixDeleteRBTree(tmp);
    draw();
}

node* Tree::deleteBST(node *&root, int val) {
    if (root == nullptr)
        return root;

    if (val < root->val)
        return deleteBST(root->left, val);

    if (val > root->val)
        return deleteBST(root->right, val);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    node *temp = minValueNode(root->right);
    root->val = temp->val;
    return deleteBST(root->right, temp->val);
}

node* Tree::minValueNode(node *&Node) {

    node* ptr = Node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

void Tree::fixDeleteRBTree(node *Node)
{
    if (Node == nullptr)
        return;

    if (Node == root) {
        root = nullptr;
        return;
    }

    if (getColor(Node) == RED || getColor(Node->left) == RED || getColor(Node->right) == RED) {
        node *child = Node->left != nullptr ? Node->left : Node->right;

        if (Node == Node->batya->left) {
            Node->batya->left = child;
            if (child != nullptr)
                child->batya = Node->batya;
            setColor(child, BLACK);
            delete (Node);
        } else {
            Node->batya->right = child;
            if (child != nullptr)
                child->batya = Node->batya;
            setColor(child, BLACK);
            delete (Node);
        }
    } else {
        node *sibling = nullptr;
        node *batya = nullptr;
        node *ptr = Node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            batya = ptr->batya;
            if (ptr == batya->left) {
                sibling = batya->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(batya, RED);
                    leftRotate(batya);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(batya) == RED)
                            setColor(batya, BLACK);
                        else
                            setColor(batya, DOUBLE_BLACK);
                        ptr = batya;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rightRotate(sibling);
                            sibling = batya->right;
                        }
                        setColor(sibling, batya->color);
                        setColor(batya, BLACK);
                        setColor(sibling->right, BLACK);
                        leftRotate(batya);
                        break;
                    }
                }
            } else {
                sibling = batya->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(batya, RED);
                    rightRotate(batya);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(batya) == RED)
                            setColor(batya, BLACK);
                        else
                            setColor(batya, DOUBLE_BLACK);
                        ptr = batya;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            leftRotate(sibling);
                            sibling = batya->left;
                        }
                        setColor(sibling, batya->color);
                        setColor(batya, BLACK);
                        setColor(sibling->left, BLACK);
                        rightRotate(batya);
                        break;
                    }
                }
            }
        }
        if (Node == Node->batya->left)
            Node->batya->left = nullptr;
        else
            Node->batya->right = nullptr;
        delete(Node);
        setColor(root, BLACK);
    }
}

int Tree::getColor(node *&Node)
{
    if (Node == nullptr)
        return BLACK;

    return Node->color;
}

void Tree::setColor(node *&Node, int color) {
    if (Node == nullptr)
        return;

    Node->color = color;
}

node *Tree::insert(node *root, node *n)
{
    insertRecurse(root,n);
    insertFix(n);
    root = n;
    while (batya(root) != nullptr){
        root = batya(root);
    }
    return root;
}

void Tree::insertRecurse(node *root, node *n)
{
    if ((root != nullptr) && (n->val < root->val)) {
        if (root->left != nullptr) {
            insertRecurse(root->left, n);
            return;
        }
        else
            root->left = n;
    } else if (root != nullptr) {
        if (root->right != nullptr){
            insertRecurse(root->right, n);
            return;
        }
        else
            root->right = n;
    }

    n->batya = root;
    n->left = nullptr;
    n->right = nullptr;
    setColor(n,RED);
}

void Tree::insertFix(node *n)
{
    if (batya(n) == nullptr) {
        insertCase1(n);
    } else if (batya(n)->color == BLACK) {
        insertCase2(n);
    } else if ((uncle(n) != nullptr) && (uncle(n)->color == RED)) {
        insertCase3(n);
    } else {
        insertCase4(n);
    }
}

void Tree::insertCase1(node *n)
{
    if (batya(n) == nullptr)
        n->color = BLACK;
}

void Tree::insertCase2(node *n)
{
    return;
}

void Tree::insertCase3(node *n)
{
    batya(n)->color = BLACK;
    uncle(n)->color = BLACK;
    grandbatya(n)->color = RED;
    insertFix(grandbatya(n));
}

void Tree::insertCase4(node *n)
{
    node* p = batya(n);
    node* g = grandbatya(n);

    if ((n == p->right) && (p == g->left)) {
        leftRotate(p);
        n = n->left;
    } else if ((n == p->left) && (p == g->right)) {
        rightRotate(p);
        n = n->right;
    }

    insertCase4_2(n);
}

void Tree::insertCase4_2(node *n)
{
    node* p = batya(n);
    node* g = grandbatya(n);
    if (n == p->left){
        rightRotate(g);
    }
    else{
        leftRotate(g);
    }
    p->color = BLACK;
    g->color = RED;
}

void Tree::leftRotate(node *a)
{
    node* anew = a->right;
    node* p = batya(a);
    assert(anew != nullptr);
    a->right = anew->left;
    anew->left = a;
    a->batya = anew;
    if (a->right != nullptr){
        a->right->batya = a;
    }
    if (p != nullptr){
        if (a == p->left){
            p->left = anew;
        }
        else{
            if (a == p->right){
                p->right = anew;
            }
        }
    }
    anew->batya = p;
    if (anew->batya == nullptr){
        root = anew;
    }
}

void Tree::rightRotate(node *a)
{
    node* anew = a->left;
    node* p = batya(a);
    assert(anew != nullptr);
    a->left = anew->right;
    anew->right = a;
    a->batya = anew;
    if (a->left != nullptr){
        a->left->batya = a;
    }
    if (p != nullptr){
        if (a == p->left){
            p->left = anew;
        }
        else{
            if (a == p->right){
                p->right = anew;
            }
        }
    }
    anew->batya = p;
    if (anew->batya == nullptr){
        root = anew;
    }
}

node *Tree::batya(node *a)
{
    return a->batya;
}

node *Tree::grandbatya(node *a)
{
    node* t = batya(a);
    if (t == nullptr){
        return nullptr;
    }
    return batya(t);
}

node *Tree::bro(node *a)
{
    node* t = batya(a);
    if (t == nullptr){
        return nullptr;
    }
    if (a == t->left){
        return t->right;
    }
    else{
        return t->left;
    }
}

node *Tree::uncle(node *a)
{
    node* t = batya(a);
    node* t1 = grandbatya(a);
    if (t1 == nullptr){
        return nullptr;
    }
    return bro(t);
}

void Tree::draw_left(node *a, int xp, int yp)
{
    if (a == nullptr){
        return;
    }
    int count = 0;
    if (a->right != nullptr){
        count = 1 + children_count(a->right);
    }
    int x = xp - size_c - count * size_c;
    int y = yp + size_c;
    addLine(xp+size_c*0.5,yp+size_c*0.5,x+size_c*0.5,y+size_c*0.5,Qt::SolidLine);
    if (a->src){
        addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::green);
        a->src = false;
    }
    else{
        if (a->color == RED){
            addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::red);
        }
        else{
            addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::black);
        }
    }
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(x,y);
    io->setPlainText(QString::number(a->val));
    addItem(io);
    draw_left(a->left,x,y);
    draw_right(a->right,x,y);
}

void Tree::draw_right(node *a, int xp, int yp)
{
    if (a == nullptr){
        return;
    }
    int count = 0;
    if (a->left != nullptr){
        count = 1 + children_count(a->left);
    }
    int x = xp + size_c + count * size_c;
    int y = yp + size_c;
    addLine(xp+size_c*0.5,yp+size_c*0.5,x+size_c*0.5,y+size_c*0.5,Qt::SolidLine);
    if (a->src){
        addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::green);
        a->src = false;
    }
    else{
        if (a->color == RED){
            addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::red);
        }
        else{
            addEllipse(x,y,size_c,size_c,Qt::SolidLine,Qt::black);
        }
    }
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(x,y);
    io->setPlainText(QString::number(a->val));
    addItem(io);
    draw_left(a->left,x,y);
    draw_right(a->right,x,y);
}

int Tree::children_count(node *a)
{
    if (a == nullptr){
        return 0;
    }
    return 1 + children_count(a->left) + children_count(a->right);
}
