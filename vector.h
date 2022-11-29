#pragma once
#include <iostream>
using namespace std;

template <class T>
class vector { //������ ������ ������
    T* array; //������
    int capacity; //������� �������
    int length; //������ �������

public:
    vector()
    { //����������� �� ���������
        array = new T[1];
        capacity = 1;
        length = 0;
    }
    vector(const vector& vec)
    { //����������� �����������
        array = vec.array;
        capacity = vec.capacity;
        length = vec.length;
    }

    int size() const
    {
        return length;
    }
    int �apacity()
    { //��������� ���� �������
        return capacity;
    }

    void clear()
    {//������� �������
        delete[]array;
        array = new T[1];
        capacity = 1;
        length = 0;
    }
    T getByIndex(int pos)
    { //��������� �������� � ��������� �������
        if (pos < length)
            return array[pos];
    }

    void pushBack(T value)
    {//���������� �������� � ����� �������
        if (length == capacity)
        {//��� ������, ���� � ������� ������ ��� ���� ��� ����� ���������
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
    { //���������� �������� � ��������� ������� � �������
        if (pos != capacity)
            array[pos] = value;
        else
            pushBack(value);
    }
    void popBack()
    { //�������� ���������� �������� �������
        length--;
    }

};

