#include <iostream>

class Polynomial; // 前向宣告

// 代表多項式中的每一個非零項
class Term {
    friend class Polynomial;
private:
    float coef; // 係數 (Coefficient)
    int exp;    // 指數 (Exponent)
    Term* link; // 指向下一項的指標

public:
    Term(float c = 0.0, int e = 0) : coef(c), exp(e), link(nullptr) {}
};

// 代表整個多項式
class Polynomial {
private:
    Term* first; // 指向多項式第一項的指標

public:
    Polynomial() : first(nullptr) {}
    ~Polynomial();

    // 常用核心功能
    void AddTerm(float coef, int exp);  // 新增非零項（保持指數由大到小排序）
    void PolyAdd(const Polynomial& b);  // 多項式相加
    void Display() const;               // 顯示多項式
};
