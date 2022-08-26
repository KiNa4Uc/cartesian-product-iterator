# cartesian-product-iterator
an iter-tool for c++.  C++ 11 REQUIRED!

# Example
```c++
int main() {

    vector<int> v1 {1, 2, 3, 4};
    vector<int> v2 {5, 6};
    vector<int> v3 {7, 8, 9};
    vector<int> v4 {0, 1};

    cartesian_product<int, vector<int>::iterator> product {{v1.begin(), v1.end()}, {v2.begin(), v2.end()}, {v3.begin(), v3.end()}, {v4.begin(), v4.end()}};
    auto iter = product.begin();
    int count = 0;
    while (!iter.is_end()) {
        std::vector<int> t = *iter;
        copy(t.begin(), t.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        iter++;
        count++;
    }

    cout << count << endl;


    return 0;
}
```

Output
```
1 5 7 0
2 5 7 0
3 5 7 0
4 5 7 0
1 6 7 0
2 6 7 0
3 6 7 0
4 6 7 0
.......(omit)
48
```

# Detailed Info
## operator++
The overloaded ++ operator does not return an iterator! And I haven't implemented -- operator...

## add array
void cartesian_product<T, I>::insert_pair(I begin, I end)

begin: the begin iterator of array

end: the end iterator of array

so, you can re-write the example code like following
```c++
cartesian_product<int, vector<int>::iterator> product;
product.insert_pair(v1.begin(), v1.end());
product.insert_pair(v2.begin(), v2.end());
product.insert_pair(v3.begin(), v3.end());
product.insert_pair(v4.begin(), v4.end());
```
