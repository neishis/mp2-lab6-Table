#pragma once
#include <string.h>
#include <string>
#include <string>
#include <sstream> 
#include <iostream>

    template<typename TKey, typename TVal>
    struct Record
    {
        TKey key;
        TVal val;

        friend std::ostream& operator<<(std::ostream& out, const Record<TKey, TVal>& r) {
            out << "[" << r.key << "]: " << r.val;
            return out;
        }

        bool operator== (const Record& rec) const { return (key == rec.key && val == rec.val); }
        bool operator!= (const Record& rec) const { return !(*this == rec); }
    };
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

        virtual bool IsFull() const = 0;

        virtual bool Find(TKey key) = 0;
        virtual void Insert(Record <TKey, TVal> rec) = 0;
        virtual void Delete(TKey key) = 0;

        virtual void Reset() = 0;
        virtual void GoNext() = 0;
        virtual bool IsEnd() = 0;

        virtual Record <TKey, TVal> getCurr() = 0;

        friend std::ostream& operator<<(std::ostream& os, Table<TKey, TVal>& t)
        {
            for (t.Reset(); !t.IsEnd(); t.GoNext())
            {
                os << t.getCurr() << std :: endl;
            }
            return os;
        }

    };
