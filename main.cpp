#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>

size_t a = 26;

struct Number {
    std::vector<size_t> num;
    bool magic = false;
    size_t last = 0;
    std::vector<size_t> nonFound;

    Number();

    Number(Number const &n);

    size_t NotFound();

    void isMagic();
};


Number::Number() {
    num = {};
    magic = false;
    last = 0;
    nonFound = {};
}

Number::Number(Number const &n) {
    this->num = n.num;
    this->magic = n.magic;
    this->last = n.last;
}

void Number::isMagic() {
    if (!magic) {
        for (size_t i = 0; i < 10; ++i) {
            if (std::find(this->num.begin(), this->num.end(), i) == num.end()) {
                this->magic = false;
                break;
            } else if (i == 9) {
                this->magic = true;
            }
        }
    }
}

size_t Number::NotFound() {
    this->nonFound.clear();
    std::vector<bool> difference = {};
    for (size_t i = 0; i < 10; ++i) {
        if (std::find(this->num.begin(), this->num.end(), i) == num.end()) {
            nonFound.push_back(i);
            difference.push_back(i > this->last);
        }
    }
    if (this->nonFound.size() == 1) {
        return abs(this->last - this->nonFound[0]);
    } else if (std::find(difference.begin(), difference.end(), true) == difference.end()) {
        return last - nonFound[0];
    } else if (std::find(difference.begin(), difference.end(), false) == difference.end()) {
        return nonFound[nonFound.size() - 1] - last;
    }
    return last - nonFound[0] + nonFound[nonFound.size() - 1] - (last - nonFound[0]);

}

size_t magic(Number &Num) {
    if (Num.num.size() > a) {
        return 0;
    }
    Num.isMagic();
    Number nextNum(Num);
    Number nextNum2(Num);
    if (Num.magic) {
        if (Num.last == 0) {
            nextNum.num.push_back(1);
            nextNum.last = 1;
            return 1 + magic(nextNum);
        } else if (Num.last == 9) {
            nextNum.num.push_back(8);
            nextNum.last = 8;
            return 1 + magic(nextNum);
        }
        nextNum.num.push_back(Num.last - 1);
        nextNum2.num.push_back(Num.last + 1);
        nextNum.last = Num.last - 1;
        nextNum2.last = Num.last + 1;
        return 1 + magic(nextNum) + magic(nextNum2);
    }
    if (Num.NotFound() > a - Num.num.size()) {
        return 0;
    } else if (Num.last == 0) {
        nextNum.num.push_back(1);
        nextNum.last = 1;
        return magic(nextNum);
    } else if (Num.last == 9) {
        nextNum.num.push_back(8);
        nextNum.last = 8;
        return magic(nextNum);
    }
    nextNum.num.push_back(Num.last - 1);
    nextNum2.num.push_back(Num.last + 1);
    nextNum.last = Num.last - 1;
    nextNum2.last = Num.last + 1;
    return magic(nextNum) + magic(nextNum2);

}


int main() {
    size_t cnt = 0;
    Number number;
    number.num.push_back(1);
    for (size_t i = 0; i < 5; ++i) {
        number.num[0] = i;
        number.last = i;
        if (i % 5 == 0) {
            cnt += magic(number);
        } else { cnt += magic(number) * 2; }
        std::cout << i << '\n';
    }
    std::cout << cnt;
    return 0;
}
