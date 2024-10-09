// templated utility functions for binary trees

#pragma once

namespace dsac::tree {

template <typename Position, typename Container>
void inorder(Position p, Container& visited) {
    if (!p.is_null()) {
        inorder(p.left(), visited);
        visited.push_back(p);
        inorder(p.right(), visited);
    }
}

}  // namespace dsac::tree
