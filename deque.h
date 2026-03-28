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

        // ---------- Michael Code to Complete ----------
        deque()
        {
            data = nullptr;
            numCapacity = 0;
            numElements = 0;
            iaFront = 0;
        }

        // ---------- Michael Code to Complete ----------
        deque(int newCapacity);

        // ---------- Michael / Brayden Code to Complete ----------
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

        // ---------- Brayden Code to Complete ----------
        deque<T>& operator = (const deque <T>& rhs);

        //
        // Iterator
        //

        // ---------- Michael Code to Complete ----------
        class iterator;

        // ---------- Michael Code to Complete ----------
        iterator begin()
        {
            return iterator(this, 0);
        }

        // ---------- Michael Code to Complete ----------
        iterator end()
        {
            return iterator(this, (int)numElements);
        }

        //
        // Access
        //

        // ---------- Brayden Code to Complete ----------
        T& front();

        // ---------- James Code to Complete ----------
        T& back();

        // ---------- Brayden Code to Complete ----------
        const T& front() const;

        // ---------- James Code to Complete ----------
        const T& back()  const;

        // ---------- Michael Code to Complete ----------
        const T& operator[](size_t index) const;

        // ---------- Michael Code to Complete ----------
        T& operator[](size_t index);

        //
        // Insert
        //

        // ---------- Brayden Code to Complete ----------
        void push_front(const T& t);

        // ---------- James Code to Complete ----------
        void push_back(const T& t);

        //
        // Remove
        //

        // ---------- Michael Code to Complete ----------
        void clear()
        {
            delete[] data;
            data = nullptr;
            numCapacity = 0;
            numElements = 0;
            iaFront = 0;
        }

        // ---------- Brayden Code to Complete ----------
        void pop_front();

        // ---------- Michael Code to Complete ----------
        void pop_back();

        //
        // Status
        //

        // ---------- Michael Code to Complete ----------
        size_t size() const
        {
            return numElements;
        }

        // ---------- Michael Code to Complete ----------
        bool empty() const
        {
            return numElements == 0;
        }

    private:

        // fetch array index from the deque index
        // ---------- Michael Code to Complete ----------
        int iaFromID(int id) const
        {
            if (numCapacity == 0)
                return 0;
            int front = iaFront % (int)numCapacity;
            if (front < 0)
                front += (int)numCapacity;
            return (front + id) % (int)numCapacity;
        }

        // ---------- Brayden Code to Complete ----------
        void resize(int newCapacity = 0);

        // member variables
        // ---------- Michael Code to Complete ----------
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

        // ---------- Michael Code to Complete ----------
        iterator()
        {
            id = 0;
            pDeque = nullptr;
        }

        // ---------- Michael Code to Complete ----------
        iterator(custom::deque<T>* pDeque, int id)
        {
            this->pDeque = pDeque;
            this->id = id;
        }

        // ---------- Michael Code to Complete ----------
        iterator(const iterator& rhs)
        {
            pDeque = rhs.pDeque;
            id = rhs.id;
        }

        //
        // Assign
        //

        // ---------- Michael Code to Complete ----------
        iterator& operator = (const iterator& rhs)
        {
            pDeque = rhs.pDeque;
            id = rhs.id;
            return *this;
        }

        //
        // Compare
        //

        // ---------- Michael Code to Complete ----------
        bool operator == (const iterator& rhs) const { return pDeque == rhs.pDeque && id == rhs.id; }

        // ---------- Michael Code to Complete ----------
        bool operator != (const iterator& rhs) const { return !(*this == rhs); }

        //
        // Access
        //

        // ---------- James Code to Complete ----------
        const T& operator * () const
        {
            return *(new T);
        }

        // ---------- James Code to Complete ----------
        T& operator * ()
        {
            return *(new T);
        }

        //
        // Arithmetic
        //

        // ---------- James Code to Complete ----------
        int operator - (iterator it) const
        {
            return 99;
        }

        // ---------- James Code to Complete ----------
        iterator& operator += (int offset)
        {
            return *this;
        }

        // ---------- James Code to Complete ----------
        iterator& operator ++ ()
        {
            return *this;
        }

        // ---------- James Code to Complete ----------
        iterator operator ++ (int postfix)
        {
            return *this;
        }

        // ---------- James Code to Complete ----------
        iterator& operator -- ()
        {
            return *this;
        }

        // ---------- James Code to Complete ----------
        iterator operator -- (int postfix)
        {
            return *this;
        }

    private:

        // Member variables
        // ---------- Michael Code to Complete ----------
        int id;             // deque index
        deque<T>* pDeque;
    };


    /****************************************************
     * DEQUE : CONSTRUCTOR - non-default
     ***************************************************/
     // ---------- Michael Code to Complete ----------
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
     // ---------- Brayden Code to Complete ----------
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
     // ---------- Brayden Code to Complete ----------
    template <class T>
    deque <T>& deque <T> :: operator = (const deque <T>& rhs)
    {
        if (this == &rhs)
            return* this;
        
        T* newData = nullptr; // allocate new container first
        if (rhs.numCapacity != 0)
        {
            newData = new T[rhs.numCapacity]; // copy capacity
            for (size_t i = 0; i < rhs.numElements; ++i)
            {
                newData[i] = rhs[i]; // copy elements
            }
        }

        // Delete old, update
        delete[] data;
        data        = newData;
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        iaFront     = 0;
    }


    /**************************************************
     * DEQUE :: FRONT
     * Fetch the item that is at the beginning of the deque
     *************************************************/
     // ---------- Brayden Code to Complete ----------
    template <class T>
    const T& deque <T> ::front() const
    {
        assert(numElements != 0);

        // Return the first element by converting id to ia 
        // to access the element in the array
        return data[iaFromID(0)];
    }

    // ---------- Brayden Code to Complete ----------
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
     // ---------- James Code to Complete ----------
    template <class T>
    const T& deque <T> ::back() const
    {
        return* (new T);
    }

    // ---------- James Code to Complete ----------
    template <class T>
    T& deque <T> ::back()
    {
        return *(new T);
    }

    /**************************************************
     * DEQUE :: SUBSCRIPT
     * Fetch the item in the deque
     ***************************************************/
     // ---------- Michael Code to Complete ----------
    template <class T>
    const T& deque <T> ::operator[](size_t index) const
    {
        return data[iaFromID((int)index)];
    }

    // ---------- Michael Code to Complete ----------
    template <class T>
    T& deque <T> ::operator[](size_t index)
    {
        return data[iaFromID((int)index)];
    }

    /*****************************************************
     * DEQUE : POP_BACK
     *****************************************************/
     // ---------- Michael Code to Complete ----------
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
     // ---------- Brayden Code to Complete ----------
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
     // ---------- James Code to Complete ----------
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
     // ---------- Brayden Code to Complete ----------
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
     // ---------- Brayden Code to Complete ----------
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
        data = newData; // Update data
        numCapacity = newCapacity;
        iaFront = 0;
    }

} // namespace custom
