#include <iostream>

class Polynomial_sparse; // 前向宣告

// 代表多項式中的每一個非零項
class Term {
    friend class Polynomial_sparse;
private:
    float coef; // 係數 (Coefficient)
    int exp;    // 指數 (Exponent)
    Term* next; // 指向下一項的指標

public:
    Term(float c = 0.0, int e = 0) : coef(c), exp(e), next(nullptr) {}
};

// 代表整個多項式
class Polynomial_sparse {
    friend Polynomial_sparse newPolyAdd(const Polynomial_sparse& a, const Polynomial_sparse& b);
private:
    Term* first; // 指向多項式第一項的指標
    int size; // size of terms
public:
    Polynomial_sparse() : first(nullptr), size(0) {} // 也可以改成 Term* first = nullptr; int size = 0;
    ~Polynomial_sparse();

    // 常用核心功能
    void AddTerm(float coef, int exp);  // 新增非零項（保持指數由大到小排序）
    void PolyAdd(const Polynomial_sparse& b);  // 多項式相加
    void Display() const;               // 顯示多項式
};
