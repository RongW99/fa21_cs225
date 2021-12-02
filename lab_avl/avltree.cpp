/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp;
    tmp->height = 1 + std::max(heightOrNeg1(tmp->left), heightOrNeg1(tmp->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp;
    tmp->height = 1 + std::max(heightOrNeg1(tmp->left), heightOrNeg1(tmp->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(!subtree) return;
    
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (b == 0 || b == 1 || b == -1) 
        return;
    else if(b == 2){
        int rightb =  heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(rightb > 0)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    }
    else if(b  == -2){
        int leftb =  heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(leftb < 0)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }
    //subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(!subtree){
        Node *tmp = new Node(key, value);
        subtree = tmp;
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    else if(key > subtree->key){
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
    else if (key == subtree->key){
        subtree->value = value;
        //return;
    }
    //rebalance(subtree);
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    else if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node*cur = subtree->left;
            while(cur->right)
                cur = cur->right;
            swap(subtree, cur);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if(!subtree->left){
                Node*tmp = subtree->right;
                delete subtree;
                subtree = tmp;
            }
            else{
                Node*tmp = subtree->left;
                delete subtree;
                subtree = tmp;
            }
        }
         
    }
    // your code here
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
