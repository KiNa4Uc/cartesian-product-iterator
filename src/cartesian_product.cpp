#include "cartesian_product.h"
#include <stdexcept>

using namespace std;

template<typename T, typename I>
cartesian_iter<T, I>::cartesian_iter(const cartesian_product<T, I> &product): product(&product) {
    ele_iters.reserve(product.elements.size());

    for (const auto &pair : this->product->elements) {
        ele_iters.push_back(pair.first);
    }
}

template<typename T, typename I>
vector<T> cartesian_iter<T, I>::operator*() {
    vector<T> t;
    for (auto const &iter : ele_iters) {
        t.push_back(*iter);
    }
    return t;
}

template<typename T, typename I>
void cartesian_iter<T, I>::operator++() {
    auto i = product->elements.size();
    i = 0;
    for (auto &iter : ele_iters) {
        iter++;
        if (iter != product->elements[i].second) {
            i++;
            return;
        }
        else {
            iter = product->elements[i].first;
            i++;
            continue;
        }
    }

    end = true; // 终止
}

template<typename T, typename I>
cartesian_iter<T, I>::cartesian_iter(cartesian_iter<T, I> &&other): ele_iters(std::move(other.ele_iters)), product(other.product) {
    end = other.end;
}

template<typename T, typename I>
cartesian_iter<T, I>::cartesian_iter(const cartesian_iter<T, I> &other): product(other.product) {
    end = other.end;
    ele_iters = other.ele_iters;
}

template<typename T, typename I>
cartesian_iter<T, I> &cartesian_iter<T, I>::operator=(const cartesian_iter &iter) {
    if (this != &iter) { // 避免自身赋值
        end = iter.end;
        ele_iters = iter.ele_iters;
        product = iter.product;
    }
    return *this;
}

template<typename T, typename I>
void cartesian_iter<T, I>::operator++(int a) {
    operator++();
}


template<typename T, typename I>
cartesian_product<T, I>::cartesian_product() {

}

template<typename T, typename I>
cartesian_iter<T, I> cartesian_product<T, I>::begin() {
    cartesian_iter<T, I> iter(*this);
    return iter;
}

template<typename T, typename I>
cartesian_product<T, I>::cartesian_product(initializer_list<std::initializer_list<I>> pair_list) {
    elements.reserve(pair_list.size());
    for (const auto &pairs : pair_list) {
        if (pairs.size() != 2) {
            throw invalid_argument("invalid pairs");
        }
        elements.push_back(make_pair(*pairs.begin(), *(pairs.begin() + 1)));
    }
}

template<typename T, typename I>
void cartesian_product<T, I>::insert_pair(I begin, I end) {
    elements.push_back(std::make_pair(begin, end));
}
