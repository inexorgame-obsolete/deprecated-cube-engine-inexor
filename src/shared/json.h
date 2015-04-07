///  JSON is used to store data-information
///  Rewrite of cJSON 1.0r58 in Inexor-optimized object-orientated C-ish C++
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
    JSON *next, *prev;   /// next/prev allow you to walk array/object chains.
    JSON *firstchild,    /// child pointer to the FIRST ITEM of the children chain.
         *parent;        /// Pointer to the parent JSON

    int type;                       // The type of the item, as above.

    char *valuestring;              /// The item's string, if type==JSON_String
    int valueint;                   /// The item's number, if type==JSON_Number
    float valuefloat;               /// The item's number, if type==JSON_Number

    char *name;                     /// The item's name string, if the item in an object this is equivalent to the key. In an array its the string of the value!

    const char *currentfile;        /// The parent directory of the .json-file ( If the JSON is the result of a .json-file beeing loaded)

    JSON *original;                 /// Contains the original info if it got overridden by an import.

    JSON() : next(NULL), prev(NULL), firstchild(NULL), parent(NULL), type(0), valuestring(NULL), valueint(0), valuefloat(0), name(NULL), currentfile(NULL), original(NULL) { }

    /// Copies contents from old, without copying the dependencies to other JSONs.
    JSON(JSON *old)
    {
        JSON();
        type = old->type;
        valueint = old->valueint; valuefloat = old->valuefloat;
        if(old->valuestring) valuestring = newstring(old->valuestring);
        if(old->name) name = newstring(old->name);
        if(old->currentfile) currentfile = newstring(old->currentfile);

        //copy children:
        JSON *loop = old->firstchild, *last = NULL;
        while(loop)
        {
            JSON *newchild = new JSON(loop); //duplicate every child and its subchilds ..
            newchild->parent = this;

            if(!last) { firstchild = newchild; last = newchild; } //set first child
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
        DELETEA(currentfile);
        JSON *c = firstchild;
        while (c)
        {
            JSON *b = c;
            c = c->next;
            DELETEP(b);
        }
    }
    
    /// Returns rendered JSON, as you would find it in a file.
    char *render(bool formatted = true, bool minified = false);

    /// Save's to a specific .json-file.
    void save(const char *filename)
    {
        string s; 
        copystring(s, filename);
        stream *f = openutf8file(path(s), "w");
        if(!f) { conoutf(CON_WARN, "could not save %s", s); return; }
        char *buf = render();
        f->putstring(buf);
        delete f;
        currentfile = newstring(s);
    }

    /// Get number of children.
    /// More useful for arrays probably.
    int numchilds()
    { 
        JSON *c = firstchild;
        int i = 0;
        while(c) { i++; c = c->next; }
        return i;
    }

    /// Return Children of a specific number.
    /// Used for Arrays.
    JSON *getchild(int number)
    {
        JSON *c = firstchild;
        while (c && number > 0) {
            number--;
            c = c->next;
        }
        return c;
    }

    /// Return Children with name <name>.
    /// Used for Objects.
    /// Case insensitive.
    JSON *getchild(const char *name)
    {
        JSON *c = firstchild;
        while (c && strcasecmp(c->name, name)) c = c->next;
        return c;
    }

    /// Get float of Object. 
    /// Used if floatvalue is expected. otherwise returns -1
    float getchildfloat(const char *key)
    {
        JSON *sub = getchild(key);
        return sub ? sub->valuefloat : -1.0f;
    }

    float getchildfloat(int item)        //Get float of Array. Used if floatvalue is expected. otherwise returns -1.0f
    {
        JSON *sub = getchild(item);
        return sub ? sub->valuefloat : -1.0f;
    }

    int getchildint(const char *key)     //Get int of Object. Used if value is expected to be int. otherwise returns -1
    {
        JSON *sub = getchild(key);
        return sub ? sub->valueint : -1;
    }

    int getchildint(int item)            //Get child int of Array. Used if value is expected to be int. otherwise returns -1
    {
        JSON *sub = getchild(item);
        return sub ? sub->valueint : -1;
    }

    const char *getchildstring(const char *key)     //Get string of Object. Used if value is expected to be a string. otherwise returns ""
    {
        JSON *sub = getchild(key);
        return sub ? sub->valuestring : newstring("");
    }

    const char *getstring(int item)            //Get string of Array. Used if value is expected to be string. otherwise returns ""
    {
        JSON *sub = getchild(item);
        return sub ? sub->valuestring : newstring("");
    }

    /// add Item to the last place of an Array (item == another JSON).
    void addchild(JSON *item);

    /// add Item to Object (item == another JSON).
    /// @param name is the new name of the item.
    void addchild(const char *name, JSON *item)
    { 
        if (!item) return;
		delete[] item->name;
        if(name) item->name = newstring(name);
        addchild(item);
    }

    /// Remove Item from Array but do not delete it.
    /// @param which tells which place to remove in the Array.
    JSON *detachchild(int which)
    {
        JSON *c = firstchild;
        while (c && which>0) { c = c->next; which--; }
        if (!c) return 0;
        if (c->prev) c->prev->next = c->next;
        if (c->next) c->next->prev = c->prev;
        if (c == firstchild) firstchild = c->next;
        c->parent = c->prev = c->next = NULL;
        return c;
    }

    /// Detach Item from Object but do not delete it.
    /// @param name gives the name of the item.
    JSON *detachchild(const char *name)
    {
        int i=0;
        JSON *c = firstchild;
        while (c && strcasecmp(c->name, name)){ i++; c = c->next; }
        if (c) return JSON::detachchild(i);
        return NULL;
    }

    void deletechild(int which) { JSON *c = detachchild(which); DELETEP(c); }        //Delete Item from Array
    void deletechild(const char *name) { JSON *c = detachchild(name); DELETEP(c); }  //Delete Item from Object
    
    /// Replace Item in Array with newitem.
    /// @sideeffects Deletes the old item.
    /// @param which represents which position in the Array the old item had.
    /// of recognizing imported/replaced stuff.
    void replacechild(int which, JSON *newitem);

    /// Replace Item in Object.
    void replacechild(const char *name, JSON *newitem)
    {
        int i = 0;
        JSON *c = firstchild;
        while(c && strcasecmp(c->name, name)) { i++; c = c->next; }
        if(!c) return;

        if(name) newitem->name = newstring(name);
        replacechild(i, newitem);
    }
};

extern JSON *loadjson(const char *filename);

extern JSON *JSON_CreateBool(bool b);
extern JSON *JSON_CreateInt(int num);
extern JSON *JSON_CreateFloat(float num);
extern JSON *JSON_CreateString(const char *str);
extern JSON *JSON_CreateArray();  //new ordered list. access: position
extern JSON *JSON_CreateObject(); //new unordered list. access: name

/// Executes b for all JSON elements below the given (t), but not t itself.
/// @param k is the variable name to access these JSON subelements.
/// @example foralljsonchildren(rootjson, j, j->valuestring = NULL)
#define foralljsonchildren(t, k, b) \
{ \
    JSON *curchildlayer = t->firstchild; \
    while(curchildlayer) \
    { \
    JSON *k = curchildlayer; \
        while(k) \
        { \
            b; \
            k = (k)->next; \
        } \
        curchildlayer = curchildlayer->firstchild; \
    } \
}

/// Executes b for all JSON elements below the given (t) and for the given one.
/// @param k is the variable name to access all these JSON subelements.
/// @example foralljson(rootjson, j, { j->name = newstring("allocated string") })
#define foralljson(t, k, b)     JSON *k = t; if(k) { b; } foralljsonchildren(t, k, b)

#endif // JSON_H

