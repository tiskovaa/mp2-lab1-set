// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <string>

static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {};

// конструктор копирования
TSet::TSet(const TSet&s):BitField(s.BitField),MaxPower(s.MaxPower){}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this !=& s) {
        this->MaxPower=s.MaxPower;
        this->BitField=s.BitField;
    }
    return * this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp(BitField | s.BitField);
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < MaxPower && Elem >= 0) {
        TSet tmp(BitField);
        tmp.InsElem(Elem);
        return tmp;
    }
    else throw "Elem is not correct";
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < MaxPower && Elem >= 0) {
        TSet res(BitField);
        res.DelElem(Elem);
        return res;
    }
    else throw "Elem is not correct";
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet app(~BitField);
    return app;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
