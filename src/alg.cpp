// Copyright 2022 NNTU-CS
#include <vector>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"

namespace {
void walk(PMTree::Node* now,
        std::vector<char>* way,
        std::vector<std::vector<char>>* ans) {
    if (now->children.empty()) {
        if (!way->empty()) {
            ans->push_back(*way);
        }
        return;
    }
    for (size_t i = 0; i < now->children.size(); i++) {
        way->push_back(now->children[i]->ch);
        walk(now->children[i], way, ans);
        way->pop_back();
    }
}
int fact(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
} // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> perms;
    std::vector<char> path;
    walk(tree.getTop(), &path, &perms);
    return perms;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(perms.size())) {
        return {};
    }
    return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    PMTree::Node* currentNode = tree.getTop();
    int n = static_cast<int>(currentNode->children.size());
    if (num < 1 || num > fact(n)) {
        return {};
    }
    std::vector<char> perms;
    num--;
    while (!currentNode->children.empty()) {
        int block = fact(static_cast<int>(currentNode->children.size()) - 1);
        int index = num / block;
        perms.push_back(currentNode->children[index]->ch);
        currentNode = currentNode->children[index];
        num %= block;
    }
    return perms;
}
