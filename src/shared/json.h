///  JSON is used to store data-information
///  Rewrite of cJSON 1.0r58 in Inexor-optimized object-orientated C-ish C++
///  Author: Malte "a_teammate" Haase
///  Date:   31.12.2014
///  cJSON (Copyright (c) 2009 by Dave Gamble) is licensed under the MIT-license


#ifndef __JSON__H
#define __JSON__H

#include <float.h>

enum {
    JSON_FALSE = 0,
    JSON_TRUE,
    JSON_NULL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,                     //ordered list [ ]
    JSON_OBJECT                     //unordered list { }
}; /// JSON Types

/// A Class to hold the parsed data of a json-file
struct JSON
{
    JSON *next, *prev;   // next/prev allow you to walk array/object chains.
    JSON *child;         // An array or object item will have a child pointer pointing to the first item of a childchain.

    int type;                       // The type of the item, as above.

    char *valuestring;              // The item's string, if type==JSON_String
    int valueint;                   // The item's number, if type==JSON_Number
    float valuefloat;               // The item's number, if type==JSON_Number

    char *name;                     /// The item's name string, if the item in an object this is equivalent to the key. In an array its the string of the value!

    const char *currentdir;         /// The parent directory of the .json-file ( If the JSON is the result of a .json-file beeing loaded)

    JSON() : next(NULL), prev(NULL), child(NULL), type(0), valueint(0), valuefloat(0), currentdir(NULL)  { name = newstring(""); valuestring = newstring(""); currentdir = newstring(""); }

    JSON(JSON *old)       /// Copy constructor
    {
        type = old->type;
        valueint = old->valueint; valuefloat = old->valuefloat;
        if(old->valuestring && old->valuestring[0]) valuestring = newstring(old->valuestring);
        if(old->name) name = newstring(old->name);
        if(old->currentdir) currentdir = newstring(old->currentdir);

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
        DELETEA(currentdir);
        JSON *c = child;
        while (c)
        {
            JSON *b = c;
            c = c->next;
            DELETEP(b);
        }
    }
    
     //Returns rendered JSON, as you would find it in a file
    char *render(bool formatted = true, bool minified = false);

     //Save's to a specific JSON-File
    void save(const char *filename)
    {
        string s; 
        copystring(s, filename);
        stream *f = openutf8file(path(s), "w");
        if(!f) { conoutf(CON_WARN, "could not save %s", s); return; }
        char *buf = render();
        f->putstring(buf);
        delete f;
        currentdir = newstring(s);
    }

    int numchilds()					  //Get number of children (if array or object, though not useful for objects)
    { 
        JSON *c = child;
        int i = 0;
        while(c) { i++; c = c->next; }
        return i;
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

    float getfloat(const char *key)  //Get float of Object. Used if floatvalue is expected. otherwise returns -1.0f
    {
        JSON *sub = getitem(key);
        return sub ? sub->valuefloat : -1.0f;
    }

    float getfloat(int item)        //Get float of Array. Used if floatvalue is expected. otherwise returns -1.0f
    {
        JSON *sub = getitem(item);
        return sub ? sub->valuefloat : -1.0f;
    }

    int getint(const char *key)     //Get int of Object. Used if value is expected to be int. otherwise returns -1
    {
        JSON *sub = getitem(key);
        return sub ? sub->valueint : -1;
    }

    int getint(int item)            //Get int of Array. Used if value is expected to be int. otherwise returns -1
    {
        JSON *sub = getitem(item);
        return sub ? sub->valueint : -1;
    }

    const char *getstring(const char *key)     //Get string of Object. Used if value is expected to be a string. otherwise returns ""
    {
        JSON *sub = getitem(key);
        return sub ? sub->valuestring : newstring("");
    }

    const char *getstring(int item)            //Get string of Array. Used if value is expected to be string. otherwise returns ""
    {
        JSON *sub = getitem(item);
        return sub ? sub->valuestring : newstring("");
    }

    void additem(JSON *item)                      //add item to Array
    {
		if (!item) return;
        //if(type != JSON_ARRAY) return; //invalid JSON
        JSON *c = child;

        if (!c) { child = item; }
        else
        { //last place in the chain
            while (c && c->next) c = c->next;
            c->next = item;
            item->prev = c;
        }
    }

    void additem(const char *name, JSON *item)  //add item to Object
    {
        if (!item) return;
		delete[] item->name;
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

#endif

