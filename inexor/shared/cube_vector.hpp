/// Legacy vector implementation.
///
/// In new code std::vectors (or a similar optimized and tested library) is strongly advised to use over this one.

#pragma once

#include "inexor/shared/cube_sort.hpp"

/// convert to float (?)
/// clever way to avoid static_casts (?)
template<class T>
static inline float heapscore(const T &n) { return n; }

/// Vector template
/// @brief a manual implementation of vector templates (self managing dynamic arrays which store one type).
template <class T, int MINSIZE = 8> struct vector
{

    /// data pointer
    T *buf;

    /// ALLOCATED memory size
    int alen;
    /// USED memory size
    int ulen;

    /// Default constructor
    /// @brief sets all members to 0
    vector() : buf(NULL), alen(0), ulen(0)
    {
    }

    /// Copy constructor
    /// @brief this constructor initialises the vector by copying another vector.
    /// @param v the vector from which data will be copied (call by reference).
    vector(const vector &v) : buf(NULL), alen(0), ulen(0)
    {
        *this = v;
    }

    /// Destructor
    /// @brief Deletes all allocated memory and sets vector size to 0.
    /// @sideeffects Calling this method manually means that all data contained in this vector will be lost.
    ~vector()
    {
        shrink(0);
        if(buf) free(buf);
    }

    /// Operator =
    /// @brief Resets own memory and copies all data from the other vector.
    /// @param v The vector from which data will be copied.
    /// @return Returns a pointer to itself.
    vector<T> &operator=(const vector<T> &v)
    {
        shrink(0);
        if(v.length() > alen) growbuf(v.length());
        loopv(v) add(v[i]);
        return *this;
    }

    /// Add new index to vector
    /// @brief Pushs a new element at the end of the vector. Allocates memory automaticly if neccesary.
    /// @param x Element which will be added at the end
    /// @sideeffects May allocates a lot of memory without your notice
    /// @see growbuf
    /// @return The last element of the vector (which is parameter x)
    T &add(const T &x)
    {
        if(ulen==alen) growbuf(ulen+1);
        new (&buf[ulen]) T(x);
        return buf[ulen++];
    }

    /// Add new EMPTY index to vector.
    /// @brief Pushs a new EMPTY element at the end of the vector. Allocates memory automaticly if neccesary.
    /// @param x Element which will be added at the end.
    /// @see growbuf
    /// @sideeffects May allocates a lot of memory without your notice.
    /// @return The last element of the vector (which is parameter x).
    T &add()
    {
        if(ulen==alen) growbuf(ulen+1);
        new (&buf[ulen]) T;
        return buf[ulen++];
    }

    /// Duplicate vector's last index.
    /// @brief Duplicates last index of the vector and appends it to the end. Allocates memory automaticly if neccesary.
    /// @see growbuf
    /// @sideeffects May allocates a lot of memory without your notice.
    /// @return The last element of the vector.
    T &dup()
    {
        if(ulen==alen) growbuf(ulen+1);
        new (&buf[ulen]) T(buf[ulen-1]);
        return buf[ulen++];
    }

    /// copy vector from vector reference
    void move(vector<T> &v)
    {
        if(!ulen)
        {
            swap(buf, v.buf);
            swap(ulen, v.ulen);
            swap(alen, v.alen);
        }
        else
        {
            growbuf(ulen+v.ulen);
            if(v.ulen) memcpy(&buf[ulen], (void  *)v.buf, v.ulen*sizeof(T));
            ulen += v.ulen;
            v.ulen = 0;
        }
    }

    /// safety check: tests if index i exists in this vector
    bool inrange(size_t i) const { return i<size_t(ulen); }
    /// safety check: tests if index i exists in this vector
    /// integer version: i must be greater (or equal to) 0
    bool inrange(int i) const { return i>=0 && i<ulen; }

    /// get the last index and decrement the vector's size
    T &pop() { return buf[--ulen]; }
    /// get the last index
    T &last() { return buf[ulen-1]; }

    /// decrement vector's size and call the DESTRUCTOR of the template in the last index
    void drop()
    {
        ulen--;
        buf[ulen].~T(); /// call template's destructor
    }

    /// is this vector empty?
    bool empty() const { return ulen==0; }

    /// return size of reserved memory
    int capacity() const { return alen; }
    /// return size of used memory
    int length() const { return ulen; }

    /// [] array access operators
    T &operator[](int i) { ASSERT(i>=0 && i<ulen); return buf[i]; }
    const T &operator[](int i) const { ASSERT(i >= 0 && i<ulen); return buf[i]; }

    /// resets all members to 0
    /// @warning This member does NOT clean up its memory!
    void disown()
    {
        buf = NULL;
        alen = ulen = 0;
    }

    /// shrink vector memory size AND DELETE UNUSED MEMORY
    void shrink(int i) { ASSERT(i<=ulen); if(isclass<T>::no) ulen = i; else while(ulen>i) drop(); }
    /// shrink vector memory size
    void setsize(int i) { ASSERT(i<=ulen); ulen = i; }

    void deletecontents() { while(!empty()) delete   pop(); }
    void deletearrays() { while(!empty()) delete[] pop(); }

    /// get the whole vector
    T *getbuf() { return buf; }
    /// get the whole vector as const value
    const T *getbuf() const { return buf; }
    bool inbuf(const T *e) const { return e >= buf && e < &buf[ulen]; }

    /// sort the vector using quicksort template and sort criteria F
    template<class F>
    void sort(F fun, int i = 0, int n = -1)
    {
        quicksort(&buf[i], n < 0 ? ulen-i : n, fun);
    }

    void sort() { sort(sortless()); }
    void sortname() { sort(sortnameless()); }

    /// mix the vector's indices randomly
    void shuffle()
    {
        for(int i = 0; i < ulen; i++)
        {
            int indx = rnd(ulen);
            T temp = buf[i];
            buf[i] = buf[indx];
            buf[indx] = temp;
        }
    }

    /// reallocate memory for vector (its size)
    void growbuf(int sz)
    {
        int olen = alen;
        if(!alen) alen = max(MINSIZE, sz);
        else while(alen < sz) alen += alen/2;
        if(alen <= olen) return;
        buf = (T *)realloc(buf, alen*sizeof(T));
        if(!buf) abort();
    }

    /// reserved memory and returns vector of the reserved memory
    databuf<T> reserve(int sz)
    {
        if(alen-ulen < sz) growbuf(ulen+sz);
        return databuf<T>(&buf[ulen], sz);
    }

    /// increase value of used bytes manually (?)
    void advance(int sz)
    {
        ulen += sz;
    }

    /// increase value of used bytes by size of a vector
    void addbuf(const databuf<T> &p)
    {
        advance(p.length());
    }

    /// 
    T *pad(int n)
    {
        T *buf = reserve(n).buf;
        advance(n);
        return buf;
    }

    /// write bytes to vector
    void put(const T &v)
    {
        add(v);
    }
    void put(const T *v, int n)
    {
        databuf<T> buf = reserve(n);
        buf.put(v, n);
        addbuf(buf);
    }

    /// remove indices from vector
    /// remove ordered?
    void remove(int i, int n)
    {
        for(int p = i+n; p<ulen; p++) buf[p-n] = buf[p];
        ulen -= n;
    }

    /// remove element from given position.
    /// @sideeffect 
    /// @return the removed element.
    T remove(int i)
    {
        T e = buf[i];
        for(int p = i+1; p<ulen; p++) buf[p-1] = buf[p];
        ulen--;
        return e;
    }
    T removeunordered(int i)
    {
        T e = buf[i];
        ulen--;
        if(ulen>0) buf[i] = buf[ulen];
        return e;
    }

    /// find (first) index in vector.
    template<class U>
    int find(const U &o)
    {
        loopi(ulen) if(buf[i]==o) return i;
        return -1;
    }

    /// only add new element if it is unique.
    void addunique(const T &o)
    {
        if(find(o) < 0) add(o);
    }

    /// remove an element if equal to to given one.
    void removeobj(const T &o)
    {
        loopi(ulen) if(buf[i] == o)
        {
            int dst = i;
            for(int j = i+1; j < ulen; j++) if(!(buf[j] == o)) buf[dst++] = buf[j];
            setsize(dst);
            break;
        }
    }

    /// replace an index with the last vector index using a template parameter key
    void replacewithlast(const T &o)
    {
        if(!ulen) return;
        loopi(ulen-1) if(buf[i]==o)
        {
            buf[i] = buf[ulen-1];
            break;
        }
        ulen--;
    }

    /// insertion functions
    T &insert(int i, const T &e)
    {
        add(T());
        for(int p = ulen-1; p>i; p--) buf[p] = buf[p-1];
        buf[i] = e;
        return buf[i];
    }
    T *insert(int i, const T *e, int n)
    {
        if(alen-ulen < n) growbuf(ulen+n);
        loopj(n) add(T());
        for(int p = ulen-1; p>=i+n; p--) buf[p] = buf[p-n];
        loopj(n) buf[i+j] = e[j];
        return &buf[i];
    }

    /// reverse all indices (first becomes last and so on...)
    void reverse()
    {
        loopi(ulen/2) swap(buf[i], buf[ulen-1-i]);
    }

    /// ?
    static int heapparent(int i) { return (i - 1) >> 1; }
    static int heapchild(int i) { return (i << 1) + 1; }

    /// ?
    void buildheap()
    {
        for(int i = ulen/2; i >= 0; i--) downheap(i);
    }

    /// ?
    int upheap(int i)
    {
        float score = heapscore(buf[i]);
        while(i > 0)
        {
            int pi = heapparent(i);
            if(score >= heapscore(buf[pi])) break;
            swap(buf[i], buf[pi]);
            i = pi;
        }
        return i;
    }

    /// ?
    T &addheap(const T &x)
    {
        add(x);
        return buf[upheap(ulen-1)];
    }

    /// ?
    int downheap(int i)
    {
        float score = heapscore(buf[i]);
        for(;;)
        {
            int ci = heapchild(i);
            if(ci >= ulen) break;
            float cscore = heapscore(buf[ci]);
            if(score > cscore)
            {
                if(ci+1 < ulen && heapscore(buf[ci+1]) < cscore) { swap(buf[ci+1], buf[i]); i = ci+1; }
                else { swap(buf[ci], buf[i]); i = ci; }
            }
            else if(ci+1 < ulen && heapscore(buf[ci+1]) < score) { swap(buf[ci+1], buf[i]); i = ci+1; }
            else break;
        }
        return i;
    }

    /// ?
    T removeheap()
    {
        T e = removeunordered(0);
        if(ulen) downheap(0);
        return e;
    }

    /// similar to find but uses hashtable keys
    template<class K>
    int htfind(const K &key)
    {
        loopi(ulen) if(htcmp(key, buf[i])) return i;
        return -1;
    }
};


