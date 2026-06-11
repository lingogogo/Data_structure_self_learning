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

void Polynomial_sparse::PolyAdd(const Polynomial_sparse& b) {
    // 取得 b 的第一個節點指標
    Term* b_curr = b.first;
    // 走訪多項式 b 的所有項
    while (b_curr != nullptr) {
        // 利用既有的 AddTerm 函式，將 b 的每一項加到目前的物件 (this) 中
        // AddTerm 內部已經處理好：指數排序、同指數相加、係數為 0 刪除節點等所有防呆邏輯
        this->AddTerm(b_curr->coef, b_curr->exp);
        // 移動到 b 的下一項
        b_curr = b_curr->next;
    }
}

// friend function
Polynomial_sparse newPolyAdd(const Polynomial_sparse& a, const Polynomial_sparse& b) {
    Polynomial_sparse result; // 建立一個全新的多項式物件

    // 1. 複製並加入 a 的所有項
    Term* curr_a = a.first;
    while (curr_a != nullptr) {
        result.AddTerm(curr_a->coef, curr_a->exp);
        curr_a = curr_a->next;
    }

    // 2. 複製並加入 b 的所有項
    Term* curr_b = b.first;
    while (curr_b != nullptr) {
        result.AddTerm(curr_b->coef, curr_b->exp);
        curr_b = curr_b->next;
    }

    return result; // 回傳這個全新相加後的多項式
}
