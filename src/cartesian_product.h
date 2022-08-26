#ifndef CLASSIFY_FUYING_CARTESIAN_PRODUCT_H
#define CLASSIFY_FUYING_CARTESIAN_PRODUCT_H

#include <initializer_list>
#include <vector>

template <typename T, typename I> class cartesian_product;

template <typename T, typename I> class cartesian_iter {
public:
    cartesian_iter(const cartesian_product<T, I> &product);
    cartesian_iter(cartesian_iter<T, I> &&other);
    cartesian_iter(const cartesian_iter<T, I> &other);

    std::vector<T> operator*();
    void operator++();
    void operator++(int);

    cartesian_iter<T, I> &operator=(const cartesian_iter &iter);
    bool is_end() { return end; }

private:
    const cartesian_product<T, I> *product;
    std::vector<I> ele_iters;
    bool end = false;

friend class cartesian_product<T, I>;
};

template <typename T, typename I> class cartesian_product {
public:
    cartesian_product();
    cartesian_product(std::initializer_list<std::initializer_list<I>>);
    void insert_pair(I begin, I end);

    cartesian_iter<T, I> begin();

private:
    std::vector<std::pair<I, I>> elements;

friend class cartesian_iter<T, I>;
};

#endif //CLASSIFY_FUYING_CARTESIAN_PRODUCT_H
