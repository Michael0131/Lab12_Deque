/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a deque
 *        deque::iterator       : An iterator through a deque
 * Author
 *    Michael, James, Brayden
 ************************************************************************/

#pragma once

 // Debug stuff
#include <cassert>

class TestDeque;    // forward declaration for TestDeque unit test class

namespace custom
{

    /******************************************************
     * DEQUE
     *         iaFront
     * ia =   0   1   2   3   4
     *      +---+---+---+---+---+
     *      |   | A | B | C |   |
     *      +---+---+---+---+---+
     * id =       0   1   2
     * iaFront = 1
     * numElements = 3
     * numCapacity = 5
     *****************************************************/
    template <class T>
    class deque
    {
        friend class ::TestDeque; // give unit tests access to the privates
    public:

        //
        // Construct
        //

        deque()
        {
            data = nullptr;
            numCapacity = 0;
            numElements = 0;
            iaFront = 0;
        }

        deque(int newCapacity);

        deque(const deque <T>& rhs);

        ~deque()
        {
            delete[] data;
            data = nullptr;
            numCapacity = 0;
            numElements = 0;
            iaFront = 0;
        }

        //
        // Assign
        //

        deque<T>& operator = (const deque <T>& rhs);

        //
        // Iterator
        //

        class iterator;

        iterator begin()
        {
            return iterator(this, 0);
        }

        iterator end()
        {
            return iterator(this, (int)numElements);
        }

        //
        // Access
        //

        T& front();

        T& back();

        const T& front() const;

        const T& back()  const;

        const T& operator[](size_t index) const;

        T& operator[](size_t index);

        //
        // Insert
        //

        void push_front(const T& t);

        void push_back(const T& t);

        //
        // Remove
        //

        void clear()
        {
            delete[] data;
            data = nullptr;
            numCapacity = 0;
            numElements = 0;
            iaFront = 0;
        }

        void pop_front();

        void pop_back();

        //
        // Status
        //

        size_t size() const
        {
            return numElements;
        }

        bool empty() const
        {
            return numElements == 0;
        }

    private:

        // fetch array index from the deque index
        int iaFromID(int id) const
        {
            if (numCapacity == 0)
                return 0;
            int front = iaFront % (int)numCapacity;
            if (front < 0)
                front += (int)numCapacity;
            return (front + id) % (int)numCapacity;
        }

        void resize(int newCapacity = 0);

        // member variables
        T* data;           // dynamically allocated data for the deque
        size_t numCapacity; // the size of the data array
        size_t numElements; // number of elements in the deque
        int iaFront;        // the index of the first item in the array
    };



    /**********************************************************
     * DEQUE ITERATOR
     * Forward and reverse iterator through a deque, just call
     *********************************************************/
    template <typename T>
    class deque <T> ::iterator
    {
        friend class ::TestDeque; // give unit tests access to the privates
    public:
        //
        // Construct
        //

        iterator()
        {
            id = 0;
            pDeque = nullptr;
        }

        iterator(custom::deque<T>* pDeque, int id)
        {
            this->pDeque = pDeque;
            this->id = id;
        }

        iterator(const iterator& rhs)
        {
            pDeque = rhs.pDeque;
            id = rhs.id;
        }

        //
        // Assign
        //

        iterator& operator = (const iterator& rhs)
        {
            pDeque = rhs.pDeque;
            id = rhs.id;
            return *this;
        }

        //
        // Compare
        //

        bool operator == (const iterator& rhs) const { return pDeque == rhs.pDeque && id == rhs.id; }

        bool operator != (const iterator& rhs) const { return !(*this == rhs); }

        //
        // Access
        //

        const T& operator * () const
        {
            return (*pDeque)[id];
        }

        T& operator * ()
        {
            return (*pDeque)[id];
        }

        //
        // Arithmetic
        //

        int operator - (iterator it) const
        {
            
            return this->id - it.id;
        }

        iterator& operator += (int offset)
        {
            id = id + offset;
            return *this;
        }

        iterator& operator ++ ()
        {
            ++id;
            return *this;
        }

        iterator operator ++ (int postfix)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator& operator -- ()
        {
            --id;
            return *this;
        }

        iterator operator -- (int postfix)
        {
            iterator tmp(*this);
            --id;
            return tmp;
        }

    private:

        // Member variables
        int id;             // deque index
        deque<T>* pDeque;
    };


    /****************************************************
     * DEQUE : CONSTRUCTOR - non-default
     ***************************************************/
    template <class T>
    deque <T> ::deque(int newCapacity)
    {
        numCapacity = (newCapacity > 0 ? (size_t)newCapacity : 0);
        numElements = 0;
        iaFront = 0;
        data = (numCapacity ? new T[numCapacity] : nullptr);
    }

    /****************************************************
     * DEQUE : CONSTRUCTOR - copy
     ***************************************************/
    template <class T>
    deque <T> ::deque(const deque <T>& rhs)
    {
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        iaFront     = 0;

        if (numCapacity == 0)
        {
            data = nullptr;
            return;
        }

        data = new T[numCapacity];
        for (size_t i = 0; i < numElements; ++i)
            data[i] = rhs[i];
    }


    /****************************************************
     * DEQUE : ASSIGNMENT OPERATOR
     ***************************************************/
    template <class T>
    deque <T>& deque <T> :: operator = (const deque <T>& rhs)
    {
        if (this == &rhs)
            return *this;
        
        // grow only if needed (never shrink)
        if (numCapacity < rhs.numCapacity)
        {
            delete[] data; // delete old storage; updating capacity
            data = nullptr;
            numCapacity = rhs.numCapacity;
            // allocate storage if capacity > 0; otherwise represent empty buffer as nullptr
            data = (numCapacity ? new T[numCapacity] : nullptr);
        }

        // copy elements in logical deque order (unwrap rhs)
        for (size_t i = 0; i < rhs.numElements; ++i)
            data[i] = rhs[i];

        numElements = rhs.numElements;
        iaFront = 0;

        return *this;
    }


    /**************************************************
     * DEQUE :: FRONT
     * Fetch the item that is at the beginning of the deque
     *************************************************/
    template <class T>
    const T& deque <T> ::front() const
    {
        assert(numElements != 0);

        // Return the first element by converting id to ia 
        // to access the element in the array
        return data[iaFromID(0)];
    }

    template <class T>
    T& deque <T> ::front()
    {
        assert(numElements != 0);
        return data[iaFromID(0)];
    }

    /**************************************************
     * DEQUE :: BACK
     * Fetch the item that is at the end of the deque
     *************************************************/
    template <class T>
    const T& deque <T> ::back() const
    {
        assert(numElements != 0);
        return data[iaFromID(numElements - 1)];
    }

    template <class T>
    T& deque <T> ::back()
    {
        assert(numElements != 0);
        return data[iaFromID(numElements - 1)];
    }

    /**************************************************
     * DEQUE :: SUBSCRIPT
     * Fetch the item in the deque
     ***************************************************/
    template <class T>
    const T& deque <T> ::operator[](size_t index) const
    {
        return data[iaFromID((int)index)];
    }

    template <class T>
    T& deque <T> ::operator[](size_t index)
    {
        return data[iaFromID((int)index)];
    }

    /*****************************************************
     * DEQUE : POP_BACK
     *****************************************************/
    template <class T>
    void deque <T> ::pop_back()
    {
        if (numElements == 0)
            return;

        --numElements;
        if (numElements == 0)
            iaFront = 0;
    }

    /*****************************************************
     * DEQUE : POP_FRONT
     *****************************************************/
    template <class T>
    void deque <T> ::pop_front()
    {
        assert(numElements > 0);

        iaFront = (iaFront + 1) % numCapacity;
        --numElements;

        if (numElements == 0)
            iaFront = 0;
    }

    /******************************************************
     * DEQUE : PUSH_BACK
     ******************************************************/
    template <class T>
    void deque <T> ::push_back(const T& t)
    {
        if (numElements == numCapacity)
           resize(numCapacity == 0 ? 1 : numCapacity * 2);
        data[iaFromID(numElements++)] = t;
    }

    /******************************************************
     * DEQUE : PUSH_FRONT
     ******************************************************/
    template <class T>
    void deque <T> ::push_front(const T& t)
    {
        // Empty deque
        if (numCapacity == 0)
            resize(1);
        // Full (must grow)
        else if (numElements == numCapacity)
            resize(numCapacity * 2);

        // Room left
        // Move iaFront one step left
        iaFront = (iaFront + numCapacity - 1) % numCapacity;
        // Add t to new front position
        data[iaFront] = t;
        ++numElements;
    }

    /****************************************************
     * DEQUE :: RESIZE
     * Resize the deque so the numCapacity matches the newCapacity
     ***************************************************/
    template <class T>
    void deque <T> ::resize(int newCapacity)
    {
        assert(newCapacity >= (int)numElements);

        // Allocate a new container
        T* newData = new T[newCapacity];
        // Unwrap
        for (size_t i = 0; i < numElements; ++i)
        {
            newData[i] = (*this)[i];
        }

        delete[] data; // Delete old data
        data = nullptr;
        data = newData; // Update data
        numCapacity = newCapacity;
        iaFront = 0;
    }

} // namespace custom
