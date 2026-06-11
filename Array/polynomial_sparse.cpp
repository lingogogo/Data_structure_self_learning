# include "polynomial_sparse.h"

// 解構子實作（已在前面提供，放在這裡統一管理）
Polynomial_sparse::~Polynomial_sparse() {
    Term* current = first;
    while (current != nullptr) {
        Term* nextTerm = current->next;
        delete current;
        current = nextTerm;
    }
}

// 1. 新增非零項（必須保持指數由大到小排序）
void Polynomial_sparse::AddTerm(float coef, int exp) {
    if (coef == 0.0) return; // 稀疏多項式不儲存係數為 0 的項

    Term* newTerm = new Term(coef, exp);

    // 情況 A：串列為空，或是新項的指數大於目前的第一項
    if (first == nullptr || exp > first->exp) {
        newTerm->next = first;
        first = newTerm;
        size++;
        return;
    }

    // 情況 B：走訪串列，尋找正確的插入位置
    Term* prev = nullptr;
    Term* curr = first;
    while (curr != nullptr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    // 情況 C：若找到相同指數的項，進行係數相加
    if (curr != nullptr && curr->exp == exp) {
        curr->coef += coef;
        delete newTerm; // 沒用到新節點，釋放記憶體
        if (curr->coef == 0.0) {
            // 如果相加後係數變成 0，必須將該節點從串列中移除並 delete
            if (prev == nullptr) first = curr->next;
            else prev->next = curr->next;
            delete curr;
            size--;
        }
    } 
    // 情況 D：插入到 prev 之後、curr 之前
    else {
        newTerm->next = curr;
        if (prev == nullptr) first = newTerm; // 理論上前面情況A已排除此可能，但寫著安全
        else prev->next = newTerm;
        size++;
    }
}

// 2. 顯示多項式
void Polynomial_sparse::Display() const {
    if (first == nullptr) {
        std::cout << "0" << std::endl;
        return;
    }
    Term* curr = first;
    while (curr != nullptr) {
        std::cout << curr->coef << "x^" << curr->exp;
        curr = curr->next;
        if (curr != nullptr && curr->coef > 0) std::cout << " + ";
        // 註：此處為簡版顯示邏輯，未處理正負號與常數項微調
    }
    std::cout << std::endl;
}

 Polynomial_sparse::PolyAdd(const Polynomial_sparse& b)
{
    
}
