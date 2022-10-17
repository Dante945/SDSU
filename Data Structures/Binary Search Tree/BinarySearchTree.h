// Author: Dante Viscuso
// San Diego State University
// CS210/CS496: Data Structures
//
// File: BinarySearchTree.h
//
// A concrete implementation of a basic binary search tree. This structure is
// useful only for education and illustration of the BAD things about growth.

#ifndef PROG2_BINARYSEARCHTREE_H
#define PROG2_BINARYSEARCHTREE_H

#include <memory>
#include "Map.h"
#include <set>

namespace sdsu {
    template<typename KEY, typename VALUE>
    class BinarySearchTree : public Map<KEY, VALUE> {

        // The BST links together BSTNode objects. The outside world never
        // needs to use these, but this data structure will use them to build
        // the search tree.
        struct BSTNode {

            // The BST structures itself around the KEY's ranking. The key is
            // so important, it must be unique in the BST.
            KEY key;

            // The value will almost certainly not be a void*, but this allows
            // us to store ANYTHING, for we can cast a void* into something else
            // void* is an address to anything . . . not nothingness. Values
            // in a map may be repeated, and values don't appear in a Set.
            VALUE value;

            std::shared_ptr<BSTNode> childL;
            std::shared_ptr<BSTNode> childR;

            BSTNode() {};

            //Creates new node
            BSTNode(KEY item) : key(item), childL(nullptr), childR(nullptr) {};

            std::pair<std::shared_ptr<KEY *> &, int> keyset(std::shared_ptr<KEY *> &arr) {
                std::pair<std::shared_ptr<KEY *> &, int> toRet(arr);
            };

            // This is something like Java's toString method.
            // This is an IN-ORDER traversal.
            friend std::ostream &operator<<(std::ostream &os, BSTNode const &node) {
                if (node.childL != nullptr) os << *node.childL;
                os << std::setw(8) << node.key << " ";
                if (node.childR != nullptr) os << *node.childR;
                return os;
            }
        };

        std::shared_ptr<BSTNode> root;

        int treeSize = 0;

        KEY minValue(std::shared_ptr<BSTNode> &node) {
            std::shared_ptr<BSTNode> currNode = node;

            while (currNode != NULL && currNode->childL != NULL) {
                currNode = currNode->childL;
            }
            return currNode->key;
        }




        bool insert(const KEY &key, std::shared_ptr<BSTNode> &start) {
            std::shared_ptr<BSTNode> currNode = start;

            if (key > currNode->key) {
                if (currNode->childR != NULL) {
                    return insert(key, currNode->childR);
                } else {
                    currNode->childR = std::make_shared<BSTNode>(key);
                    treeSize++;
                    return true;
                }
            } else {
                if (currNode->childL != NULL)
                    return insert(key, currNode->childL);
                else {
                    currNode->childL = std::make_shared<BSTNode>(key);
                    treeSize++;
                    return true;
                }
            }
        }
        VALUE insert(const KEY &key, std::shared_ptr<BSTNode> &start, const VALUE &val) {
            std::shared_ptr<BSTNode> currNode = start;

            if (key > currNode->key) {
                if (currNode->childR != NULL) {
                    return insert(key, currNode->childR, val);
                } else {
                    currNode->childR = std::make_shared<BSTNode>(key);
                    treeSize++;
                    currNode->childR->value = val;
                    return NULL;
                }
            } else {
                if (currNode->childL != NULL)
                    return insert(key, currNode->childL, val);
                else {
                    currNode->childL = std::make_shared<BSTNode>(key);
                    treeSize++;
                    currNode->childL->value = val;
                    return NULL;
                }
            }
        }

        bool remove(const KEY &key, std::shared_ptr<BSTNode> &start, std::shared_ptr<BSTNode> &parent) {
            std::shared_ptr<BSTNode> currNode = start;
            std::shared_ptr<BSTNode> parentNode = parent;

            //Find node to delete
            if (key < currNode->key) {
                return remove(key, currNode->childL, currNode);
            } else if (key > currNode->key) {
                return remove(key, currNode->childR, currNode);
            }

            //No children
            else {
                if (currNode->childR == NULL && currNode->childL == NULL) {
                    if (key < parentNode->key) {
                        parentNode->childL = NULL;
                        treeSize--;
                        return true;
                    } else {
                        parentNode->childR = NULL;
                        treeSize--;
                        return true;
                    }
                }
                //Only right child
                if (currNode->childL == NULL && currNode->childR != NULL) {
                    if(key < parentNode->key) {
                        parentNode->childL = currNode->childR;
                    }
                    else {
                        parentNode->childR = currNode->childR;
                    }
                    treeSize--;
                    return true;
                }
                //Only left child
                if (currNode->childR == NULL && currNode->childL != NULL) {
                    if(key > parentNode->key) {
                        parentNode->childR = currNode->childL;
                    }
                    else {
                        parentNode->childL = currNode->childL;
                    }
                    treeSize--;
                    return true;
                }
                //Two children
                int tempKey = minValue(currNode->childR);
                remove(tempKey);
                currNode->key = tempKey;
                return true;
            }
        }

    public:
        BinarySearchTree() {}

        BinarySearchTree(const BinarySearchTree<KEY, VALUE> &other) {}

        ~BinarySearchTree() override {}

        bool runUnique(int i) {
            std::set<int> test;
            return testUniqueValues(root, test, 0);
        }

        std::set<int> valuesUn;
        int sizeOf;
        void traverse(std::shared_ptr<BSTNode> &Root)
        {
            if (Root == NULL)
                return;
            traverse(Root->left);
            valuesUn.insert(Root->value);
            sizeOf++;
            traverse(Root->right);
        }

        bool testValues(std::set<int> valueSet, int size){
            if(size == valueSet.size())
                return true;
            else
                return false;
        }

        bool testUniqueValues (std::shared_ptr<BSTNode> &Root, std::set<int> uniqueValues, int size) {
                if (Root->childL != NULL) {
                    testUniqueValues(Root->childL, uniqueValues, size);
                }
                if (Root->childR != NULL) {
                    testUniqueValues(Root->childR, uniqueValues, size);
                }
                uniqueValues.insert(Root->value);
                size++;
                if (uniqueValues.size() != size)
                    return false;
                else
                    return true;
        }

        bool contains(const KEY &key) const override {
            if (this->isEmpty())
                return false;
            if (root->key == key)
                return true;
            std::shared_ptr<BSTNode> currNode = root;

            while (currNode != NULL) {
                if (key < currNode->key) {
                    currNode = currNode->childL;
                } else if (key > currNode->key) {
                    currNode = currNode->childR;
                } else
                    return true;
            }
            return false;
        }

        void clear() override {
            root = nullptr;
            treeSize = 0;
        }

        virtual VALUE &get(const KEY &key) override {
            if (root->key == key) {
                return root->value;
            }
            std::shared_ptr<BSTNode> currNode = root;

            while (currNode != NULL) {
                if (key < currNode->key) {
                    currNode = currNode->childL;
                } else if (key > currNode->key) {
                    currNode = currNode->childR;
                } else {
                    return currNode->value;
                }
            }
        }

        bool insert(const KEY &key) override {
            if (this->isEmpty()) {
                root = std::make_shared<BSTNode>(key);
                treeSize++;
                return true;
            }
            if (contains(key))
                return false;
            return insert(key, root);
        }

        VALUE insert(const KEY &key, const VALUE &val) override {
            if (this->isEmpty()) {
                root = std::make_shared<BSTNode>(key);
                treeSize++;
                root->value = val;
                return NULL;
            }
            if (contains(key)) {
                if (root->key = key) {
                    if (root->value == NULL) {
                        root->value = val;
                        return NULL;
                    }
                    else{
                        VALUE temp = root->value;
                        root->value = val;
                        return temp;
                    }
                }
                else {
                    std::shared_ptr<BSTNode> currNode = root;
                    while (currNode != NULL) {
                        if (key < currNode->key) {
                            currNode = currNode->childL;
                        } else if (key > currNode->key) {
                            currNode = currNode->childR;
                        } else {
                            if (currNode->value == NULL) {
                                currNode->value = val;
                                return NULL;
                            }
                            if (currNode->value != NULL) {
                                VALUE temp = currNode->value;
                                currNode->value = val;
                                return temp;
                            }
                        }
                    }
                }
            }
            return insert(key, root, val);
        }

        std::pair<std::shared_ptr<KEY *>, int> keys() override {
            KEY *raw = new KEY[size()];
            std::shared_ptr<KEY *> arr = std::make_shared<KEY *>(raw);
            std::pair<std::shared_ptr<KEY *>, int> toRet(arr, size());
            return toRet;
        };

        virtual std::pair<std::shared_ptr<VALUE *>, int> values() override {
            VALUE *raw = new VALUE[size()];
            std::shared_ptr<VALUE *> arr = std::make_shared<VALUE *>(raw);
            std::pair<std::shared_ptr<VALUE *>, int> vals(arr, size());
            return vals;
        };
        bool remove(const KEY &key) override {
            std::shared_ptr<BSTNode> currNode = root;
            if (this->isEmpty())
                return false;
            if (contains(key) == false)
                return false;
            if (currNode->key == key) {
                if (currNode->childL == NULL && currNode->childR != NULL) {
                    root = currNode->childR;
                    treeSize--;
                    return true;
                } else if (currNode->childL != NULL && currNode->childR == NULL) {
                    root = currNode->childL;
                    treeSize--;
                    return true;
                } else if (currNode->childR, currNode->childL != NULL) {
                    return remove(key, currNode, currNode);
                } else {
                    root = nullptr;
                    treeSize = 0;
                    return true;
                }
            }
            return remove(key, currNode, currNode);
        }

        int size() const override {
            return treeSize;
        }

        bool isEmpty() const override {
            return size() == 0;
        }

        VALUE &operator[](std::size_t idx) {
            return get(idx);
        }

        friend std::ostream &operator<<(std::ostream &os, sdsu::BinarySearchTree<KEY, VALUE> const &bst) {
            if (bst.root != nullptr) return os << "[" << (*bst.root) << "]";
            return os;
        }
    };
}
#endif //PROG2_BINARYSEARCHTREE_H
