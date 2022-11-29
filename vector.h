#pragma once
#include <iostream>
using namespace std;

template <class T>
class vector { //шаблон класса Вектор
    T* array; //массив
    int capacity; //ёмкость массива
    int length; //размер массива

public:
    vector()
    { //конструктор по умолчанию
        array = new T[1];
        capacity = 1;
        length = 0;
    }
    vector(const vector& vec)
    { //конструктор копирования
        array = vec.array;
        capacity = vec.capacity;
        length = vec.length;
    }

    int size() const
    {
        return length;
    }
    int сapacity()
    { //получение всей ёмкости
        return capacity;
    }

    void clear()
    {//очистка вектора
        delete[]array;
        array = new T[1];
        capacity = 1;
        length = 0;
    }
    T getByIndex(int pos)
    { //получение элемента с указанной позиции
        if (pos < length)
            return array[pos];
    }

    void pushBack(T value)
    {//добавление элемента в конец вектора
        if (length == capacity)
        {//для случая, если в векторе больше нет мест для новых элементов
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            capacity *= 2;
            array = temp;
        }
        array[length] = value;
        length++;
    }
    void pushIn(T value, int pos)
    { //добавление элемента в указанную позицию в векторе
        if (pos != capacity)
            array[pos] = value;
        else
            pushBack(value);
    }
    void popBack()
    { //удаление последнего элемента вектора
        length--;
    }

};

