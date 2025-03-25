#pragma once
#include <string.h>
#include <string>
#include <string>
#include <sstream> 
#include <iostream>
    //структура табличной записи
    template<typename TKey, typename TVal>
    struct Record
    {
        TKey key;
        TVal val;
    };

    // массивы дл€ хранени€ может быть неупор€доченным и упор€доченным по ключу 
    // два вида хэш-таблиц - таблиц, в которой позици€ может быть вычислена по ключу
    // два вида деревьев (сбалансированные и несбалансированные)

    // поиск вставка удаление - должны присутствовать во всех этих таблицах

    // поиск по ключу и удаление
    // вставка получает все данные 

    // ключ должен быть уникальным

    // ветки наследовани€ будут разные дл€ базового класса

    template<typename TKey, typename TVal>
    class Table 
    {
    protected:
        int DataCount; // кол-во данных (записей)
        int Eff; // эффективность в числе выполненных операций
    public:
        Table() : DataCount(0), Eff(0) {};
        virtual ~Table() {};

        int getDataCount() {
            return DataCount;
        };
        int getEff() {
            return Eff;
        };

        void ClearEff() {
            Eff = 0;
        };

        bool IsEmpty() const {
            if (DataCount == 0)
                return true;
            return false;
        }

        virtual bool IsFull() const = 0; // значит данный метод не имеет здесь реализации а класс становитс€ абстрактным 

        virtual bool Find(TKey key) = 0;
        virtual void Insert(Record <TKey, TVal> rec) = 0;
        virtual void Delete(TKey key) = 0;

        virtual void Reset() = 0;
        virtual void GONext() = 0;
        virtual bool IsEnd() = 0;

        virtual Record <TKey, TVal> getCurr() = 0;
        virtual TKey getCurrKey() = 0;
        virtual TVal getCurrVal() = 0;

        friend std::ostream& operator<<(std::ostream& os, const Table& t)
        {
            for (t.Reset(); !t.IsEnd(); t.GoNext())
            {
                os << t.GetCurr() << std :: endl;
            }
            return os;
        }

    };
