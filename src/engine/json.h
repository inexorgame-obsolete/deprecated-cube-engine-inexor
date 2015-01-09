//  Rewrite of cJSON 1.0r58 in Inexor-optimized object-orientated C-ish C++
//  cJSON (Copyright (c) 2009 by Dave Gamble) is licensed under the MIT-license

#include <float.h>

enum {
    JSON_FALSE = 0,
    JSON_TRUE,
    JSON_NULL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,                     //ordered list [ ]
    JSON_OBJECT                     //unordered list { }
}; // JSON types

struct JSON
{
    JSON *next, *prev;   // next/prev allow you to walk array/object chains.
    JSON *child;         // An array or object item will have a child pointer pointing to the first item of a childchain.

    int type;                       // The type of the item, as above.

    char *valuestring;              // The item's string, if type==JSON_String
    int valueint;                   // The item's number, if type==JSON_Number
    float valuefloat;               // The item's number, if type==JSON_Number

    char *name;                     // The item's name string, if this item is the child of, or is in the list of subitems of an object.

    JSON() : next(NULL), prev(NULL), child(NULL), type(0), valuestring(NULL), valueint(0), valuefloat(0), name(NULL)  { }

    JSON(JSON *old)       //Copy constructor
    {
        type = old->type;
        valueint = old->valueint; valuefloat = old->valuefloat;
        if(old->valuestring) valuestring = newstring(old->valuestring);
        if(old->name) name = newstring(old->name);

        //copy children:
        JSON *loop = old->child, *last = NULL;
        while(loop)
        {
            JSON *newchild = new JSON(loop); //duplicate every child and its subchilds ..

            if(!last) { child = newchild; last = newchild; } //set first child
            else {         //If child already set, then crosswire ->prev and ->next and move on
                last->next = newchild;
                newchild->prev = last;
                last = newchild;
            }
            loop = loop->next;
        }
    }

    ~JSON()
    {
        DELETEA(name);
        DELETEA(valuestring);
        JSON *c = child;
        while (c)
        {
            JSON *b = c;
            c = c->next;
            DELETEP(b);
        }
    }
    
     //Returns rendered JSON, as you would find it in a file
     //NOTE: This is implemented in json.cpp, because it
     //      needs access to a static variable.
    char *render(bool formatted = true, bool minified = false);

     //Save's to a specific JSON-File
    void save(const char *filename)
    {
        string s; 
        copystring(s, filename);
        stream *f = openutf8file(path(s), "w");
        if(!f) { conoutf(CON_WARN, "could not save %s", s); return; }
        char *buf = render();
        f->printf(buf);
        delete f;
    }

    JSON *getitem(int item)           //Get Item of Array
    {
        JSON *c = child;
        while (c && item > 0) {
            item--;
            c = c->next;
        }
        return c;
    }

    JSON *getitem(const char *name)   //Get Item of Object
    {
        JSON *c = child;
        while (c && strcasecmp(c->name, name)) c = c->next;
        return c;
    }

    void additem(JSON *item)                      //add item to Array
    {
        //if(type != JSON_ARRAY) return; //invalid JSON
        JSON *c = child;
        if (!item) return;

        if (!c) { child = item; }
        else
        { //last place in the chain
            while (c && c->next) c = c->next;
            c->next = item;
            item->prev = c;
        }
    }

    void additem(const char *string, JSON *item)  //add item to Object
    {
        if (!item) return;
        DELETEA(item->name);
        item->name = newstring(name);
        additem(item);
    }

    JSON *detachitem(int which)         //Detach Item from Array
    {
        JSON *c = child;
        while (c && which>0) { c = c->next; which--; }
        if (!c) return 0;
        if (c->prev) c->prev->next = c->next;
        if (c->next) c->next->prev = c->prev;
        if (c == child) child = c->next;
        c->prev = c->next = NULL;
        return c;
    }
    JSON *detachitem(const char *name)  //Detach Item from Object
    {
        int i=0;
        JSON *c = child;
        while (c && strcasecmp(c->name, name)){ i++; c = c->next; }
        if (c) return JSON::detachitem(i);
        return 0;
    }

    void deleteitem(int which) { JSON *c = detachitem(which); DELETEP(c); }        //Delete Item from Array
    void deleteitem(const char *name) { JSON *c = detachitem(name); DELETEP(c); }  //Delete Item from Object

    void replaceitem(int which, JSON *newitem)          //Replace Item in Array
    {
        JSON *c = child;
        while (c && which>0) { c = c->next; which--; }
        if (!c) return;

        if(type != JSON_ARRAY && !newitem->name) newitem->name = newstring(c->name); //misuse prevention

        newitem->next = c->next;
        newitem->prev = c->prev;
        if (newitem->next) newitem->next->prev = newitem;

        if (c == child) child = newitem;
        else newitem->prev->next = newitem;
        DELETEP(c);
    }

    void replaceitem(const char *name, JSON *newitem)   //Replace Item in Object
    {
        int i = 0;
        JSON *c = child;
        while(c && strcasecmp(c->name, name)) { i++; c = c->next; }
        if(!c) return;

        newitem->name = newstring(name);
        replaceitem(i, newitem);
    }
};

extern JSON *loadjson(const char *filename);

extern JSON *JSON_CreateBool(bool b);
extern JSON *JSON_CreateInt(int num);
extern JSON *JSON_CreateFloat(float num);
extern JSON *JSON_CreateString(const char *str);
extern JSON *JSON_CreateArray();  //new ordered list. access: position
extern JSON *JSON_CreateObject(); //new unordered list. access: name

extern JSON *JSON_CreateIntArray(const int *numbers, int count);
extern JSON *JSON_CreateFloatArray(const float *numbers, int count);
extern JSON *JSON_CreateStringArray(const char **strings, int count);

