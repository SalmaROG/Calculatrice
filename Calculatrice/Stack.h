#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class Stack {
private:
    T* data;
    int sommet;
    int capacity;

public:
    Stack(int taille);
    bool IsEmpty()const;
    bool IsFull()const;
    void push(T elem);
    void pop();
    void resize();
    int size() const;
    T& operator[](int index);
    void Afficher() const;
    T Sommet() const;
    ~Stack();
};

template<class T>
inline Stack<T>::Stack(int taille) :capacity(taille), sommet(-1)
{
    if (taille <= 0)
    {
        throw invalid_argument("La taille doit etre positive");
    }
    this->data = new T[this->capacity];
    for (int i = 0; i < this->capacity; i++)
    {
        this->data[i] = T();
    }

}

template<class T>
inline bool Stack<T>::IsEmpty() const
{
    return (this->sommet == -1);


}

template<class T>
inline bool Stack<T>::IsFull() const
{
    return (this->sommet == (this->capacity - 1));

}

template<class T>
inline void Stack<T>::push(T elem)
{

    if (!this->IsFull())
    {
        this->data[++this->sommet] = elem;
    }


}

template<class T>
inline void Stack<T>::pop()
{

    if (!this->IsEmpty())

        this->sommet--;


}



template<class T>
inline void Stack<T>::resize()
{
    int k = 0;
    T* temp = new T[this->capacity];
    this->capacity *= 2;
    T* table = new T[this->capacity];
    for (int i = this->sommet; i >= 0; i--)
    {
        temp[k++] = this->data[i];
    }
    k = 0;
    for (int i = this->sommet; i >= 0; i--)
    {
        table[k++] = temp[i];
    }

    for (int i = this->sommet + 1; i < this->capacity; i++)
    {
        table[i] = T();
    }
    delete[] this->data;
    this->data = table;

}

template<class T>
inline int Stack<T>::size() const
{
    return this->sommet + 1;
}

template<class T>
inline T& Stack<T>::operator[](int index)
{
    if (index < 0 || index >= this->capacity)
        throw out_of_range("Index hors limite\n");
    return this->data[index];
}

template<class T>
inline void Stack<T>::Afficher() const
{
    for (int i = this->sommet; i >= 0; i--)
    {
        cout << this->data[i] << " ";
    }
    cout << endl;
}

template<class T>
inline T Stack<T>::Sommet() const
{
    return this->data[this->sommet];
}

template<class T>
inline Stack<T>::~Stack()
{
    delete[] this->data;
    this->data = nullptr;
}






