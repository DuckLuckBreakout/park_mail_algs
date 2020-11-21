/*
 * 4_2. Быстрое сложение.
 * Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
 * Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9
 * ((1+3)+2) -> 1+3 + 4+2 = 10
 * ((2+3)+1) -> 2+3 + 5+1 = 11
 * Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы
 * заданного набора чисел.
 *
 * Формат входных данных. Вначале вводится n - количество чисел.
 * Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9,
 * сумма всех чисел не превосходит 2*10^9).
 *
 * Формат выходных данных. Натуральное число - минимальное время.
 *
 *  +-----------+--------+
 *  | in        | out    |
 *  +-----------+--------+
 *  |5          | 45     |
 *  |5 2 3 4 6  |        |
 *  +-----------+--------+
 *  |5          | 56     |
 *  |3 7 6 1 9  |        |
 *  +-----------+--------+
 */


#include <iostream>
#include <cassert>

template<typename Type>
class cmpDefault {
public:
    bool operator() (const Type& left, const Type& right);
};

template<typename Type>
bool cmpDefault<Type>::operator()(const Type &left, const Type &right) {
    return left < right;
}

template<typename Type>
class CArray {
public:
    CArray();
    CArray(const CArray<Type> &array);
    ~CArray();

    int size() const;

    Type &getAt(int index);
    const Type &getAt(int index) const;

    Type &operator[](int index);
    const Type &operator[](int index) const;
    CArray<Type> &operator=(const CArray<Type> &array);

    void add(Type element);
    void deleteLast();

private:
    void grow();

private:
    Type *buffer;
    int bufferSize;
    int realSize;
};

template<typename Type>
CArray<Type>::CArray() : buffer(nullptr), bufferSize(0), realSize(0) {}

template<typename Type>
CArray<Type>::CArray(const CArray<Type> &array) {
    Type *newBuffer = new Type[array.bufferSize];
    assert(newBuffer);
    for (int i = 0; i < array.realSize; ++i)
        newBuffer[i] = array[i];

    buffer = newBuffer;
    bufferSize = array.bufferSize;
    realSize = array.realSize;
}

template<typename Type>
CArray<Type>::~CArray() {
    delete[] buffer;
}

template<typename Type>
int CArray<Type>::size() const {
    return realSize;
}

template<typename Type>
Type &CArray<Type>::getAt(int index) {
    assert(index < realSize && buffer != nullptr);
    return buffer[index];
}

template<typename Type>
const Type &CArray<Type>::getAt(int index) const {
    assert(index < realSize && buffer != nullptr);
    return buffer[index];
}

template<typename Type>
CArray<Type>&  CArray<Type>::operator=(const CArray<Type> &array) {
    Type *newBuffer = new Type[array.bufferSize];
    assert(newBuffer);
    for (int i = 0; i < array.realSize; ++i)
        newBuffer[i] = array[i];

    buffer = newBuffer;
    bufferSize = array.bufferSize;
    realSize = array.realSize;
    return *this;
}

template<typename Type>
Type &CArray<Type>::operator[](int index) {
    return getAt(index);
}

template<typename Type>
Type const & CArray<Type>::operator[](int index) const {
    return getAt(index);
}

template<typename Type>
void CArray<Type>::add(Type element) {
    if (realSize == bufferSize)
        grow();
    assert(realSize < bufferSize && buffer != nullptr);
    buffer[realSize++] = element;
}

template<typename Type>
void CArray<Type>::deleteLast() {
    realSize--;
}


template<typename Type>
void CArray<Type>::grow() {
    Type newBufferSize = bufferSize + ((bufferSize + 1) >> 3) + ((bufferSize + 1) < 9 ? 3 : 6);
    Type *newBuffer = new Type[newBufferSize];
    assert(newBuffer);
    for (int i = 0; i < realSize; ++i)
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template<typename Type, typename Comp=cmpDefault<Type>>
class Heap {
public:
    Heap();
    explicit Heap(const CArray<Type> &arr);
    Heap(const Heap<Type, Comp> &heap);
    ~Heap() = default;

    void insert(Type elem);
    Type &extractPeak();
    Type const &peekPeak() const;

    Heap<Type, Comp>& operator=(const Heap<Type, Comp> &heap);

    int size() const;

private:
    void buildHeap();
    void siftDown(int i);
    void siftUp(int i);

private:
    CArray<Type> array;
    cmpDefault<Type> cmp;
};

template<typename Type, typename Comp>
Heap<Type, Comp>::Heap() : array(), cmp() {}

template<typename Type, typename Comp>
Heap<Type, Comp>::Heap(const CArray<Type> &arr) : array(arr), cmp() {
    buildHeap();
}

template<typename Type, typename Comp>
Heap<Type, Comp>::Heap(const Heap<Type, Comp> &heap) : array(heap.array) {}


template<typename Type, typename Comp>
int Heap<Type, Comp>::size() const {
    return array.size();
}

template<typename Type, typename Comp>
void Heap<Type, Comp>::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int largest = i;
    if ((left < array.size())  && (cmp(array[left], array[i])))
        largest = left;
    if ((right < array.size()) && (cmp(array[right], array[largest])))
        largest = right;

    if (largest != i) {
        std::swap(array[i], array[largest]);
        siftDown(largest);
    }
}

template<typename Type, typename Comp>
void Heap<Type, Comp>::buildHeap() {
    for (int i = array.size() / 2 - 1; i >=0; --i)
        siftDown(i);
}

template<typename Type, typename Comp>
void Heap<Type, Comp>::siftUp(int index) {
    while(index > 0) {
        int parent = (index - 1) / 2;
        if(cmp(array[parent], array[index]))
            return;
        std::swap(array[index], array[parent] );
        index = parent;
    }
}

template<typename Type, typename Comp>
void Heap<Type, Comp>::insert(Type element) {
    array.add(element);
    siftUp(array.size() - 1 );
}

template<typename Type, typename Comp>
Type &Heap<Type, Comp>::extractPeak() {
    assert(array.size());
    Type result = array[0];
    array[0] = array[array.size() - 1];
    array.deleteLast();
    if(array.size())
        siftDown( 0 );
    return result;
}

template<typename Type, typename Comp>
Heap<Type, Comp> &Heap<Type, Comp>::operator=(const Heap<Type, Comp> &heap) {
    array = heap.array;
    return *this;
}

template<typename Type, typename Comp>
Type const &Heap<Type, Comp>::peekPeak() const {
    assert(size());
    return array[0];
}


template <typename Type>
int findMinTime(Heap<Type> &heap) {
    int result = 0;
    while (heap.size() != 1) {
        int first_min = heap.extractPeak();
        int second_min = heap.extractPeak();
        int sum = first_min + second_min;
        result += sum;
        heap.insert(sum);
    }
    return result;
}

void inputArray(CArray<int> &Array, int size) {
    int bufValue;
    for (int i = 0; i < size; i++) {
        std::cin >> bufValue;
        Array.add(bufValue);
    }
}



int main() {

    CArray<int> Arr = CArray<int>();

    int n;
    std::cin >> n;

    inputArray(Arr, n);

    Heap<int> heap = Heap<int>(Arr);

    std::cout << findMinTime(heap);
    return 0;
}

