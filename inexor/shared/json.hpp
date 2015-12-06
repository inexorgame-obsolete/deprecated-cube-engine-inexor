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
    /// @return true after saving successfully.
    bool save(const char *filename, bool formatted = true)
    {
        string s;
        copystring(s, filename);
        stream *f = openutf8file(path(s), "w");
        if(!f) return false;
        char *buf = render(formatted);
        f->putstring(buf);
        delete f;
        delete[] currentfile;
        currentfile = newstring(s);
        return true;
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
        if(!name) return NULL;
        JSON *c = firstchild;
        while (c && (!c->name || strcasecmp(c->name, name))) c = c->next;
        return c;
    }

    /// Get floatvalue of a specific child in an Object.
    /// @return floatvalue of child or -1.0 if not found.
    float getchildfloat(const char *key)
    {
        JSON *sub = getchild(key);
        return sub ? sub->valuefloat : -1.0f;
    }

    /// Get floatvalue of a specific child in an Array.
    /// @return floatvalue of child or -1.0 if not found.
    float getchildfloat(int item)
    {
        JSON *sub = getchild(item);
        return sub ? sub->valuefloat : -1.0f;
    }

    /// Get intvalue of a specific child in an Object.
    /// @return intvalue of child or -1 if not found.
    int getchildint(const char *key)
    {
        JSON *sub = getchild(key);
        return sub ? sub->valueint : -1;
    }

    /// Get intvalue of a specific child in an Array.
    /// @return intvalue of child or -1 if not found.
    int getchildint(int item)
    {
        JSON *sub = getchild(item);
        return sub ? sub->valueint : -1;
    }

    /// Get (allways allocated!) string of a specific child in an Object.
    /// @return intvalue of child or a new allocated string "" if not found.
    /// @sideeffects allocates memory if no such key is found, needs deletion.
    const char *getchildstring(const char *key)
    {
        JSON *sub = getchild(key);
        return sub ? sub->valuestring : newstring("");
    }

    /// Get (allways allocated!) string of a specific child in an Object.
    /// @return intvalue of child or a new allocated string "" if not found.
    /// @sideeffects allocates memory if no such key is found, needs deletion.
    const char *getchildstring(int item)
    {
        JSON *sub = getchild(item);
        return sub ? sub->valuestring : newstring("");
    }

    /// add a child to this JSON Array (at the last place, not setting a new name).
    void addchild(JSON *item);

    /// add a child to this JSON Object (at the last place).
    /// @param name is the new key/name the added item will be accessed.
    void addchild(const char *name, JSON *item)
    {
        if (!item) return;
        if(name) {
            delete[] item->name;
            item->name = newstring(name);
        }
        addchild(item);
    }

    /// Remove Child from Array but do not delete it.
    /// @param which specifies which place the Child is.
    /// @return the detached Child.
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

    /// Detach Child from Object but do not delete it.
    /// @param name specifies the key/name of the Child.
    /// @return the detached Child.
    JSON *detachchild(const char *name)
    {
        if(!name) return NULL;
        int i=0;
        JSON *c = firstchild;
        while (c && (!c->name || strcasecmp(c->name, name))){ i++; c = c->next; }
        if (c) return JSON::detachchild(i);
        return NULL;
    }

    /// Delete Child according to its position (from Array).
    void deletechild(int which) { JSON *c = detachchild(which); DELETEP(c); }

    /// Delete Child according to its name (from Object).
    void deletechild(const char *name) { JSON *c = detachchild(name); DELETEP(c); }

    /// Replace Child in an Array with newitem.
    /// @sideeffects Deletes the old item.
    /// @param which represents which position in the Array the old item has.
    void replacechild(int which, JSON *newitem);

    /// Replace Child in an Object with newitem.
    /// @sideeffects Deletes the old item.
    /// @param name represents the key/name of the old item.
    void replacechild(const char *name, JSON *newitem)
    {
        if(!name) return;
        int i = 0;
        JSON *c = firstchild;
        while(c && (!c->name || strcasecmp(c->name, name))) { i++; c = c->next; }
        if(!c) return;

        if(name) {
            delete[] newitem->name;
            newitem->name = newstring(name);
        }
        replacechild(i, newitem);
    }
};

/// Load a .json file.
/// Prints out the error position if it failed to parse if debugjson is enabled.
/// @sideeffects allocates memory for a JSON structure, needs to be deleted.
extern JSON *loadjson(const char *filename);


/// Create a JSON with a boolean value.
extern JSON *JSON_CreateBool(bool b);

/// Create a JSON with given integer number as value.
extern JSON *JSON_CreateInt(int num);

/// Create a JSON with given floating point number as value.
extern JSON *JSON_CreateFloat(float num);

/// Create a JSON containing just a valuestring.
extern JSON *JSON_CreateString(const char *str);

/// Create a new ordered list.
/// Access childs through its position number.
extern JSON *JSON_CreateArray();

/// Create a new unordered list.
/// Access Childs through their keys (name-strings).
extern JSON *JSON_CreateObject();



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

