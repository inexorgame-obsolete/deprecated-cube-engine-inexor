///  JSON is used to store data-information
///  Rewrite of cJSON 1.0r58 in Inexor-optimized object-orientated C-ish C++
///  cJSON (Copyright (c) 2009 by Dave Gamble) is licensed under the MIT-license

#include "inexor/engine/engine.h"

// Debugging

VARP(debugjson, 0, 0, 1);
static const char *ep; //error pointer
const char *JSON_GetError()
{
    return ep;
}

/// Internal: Parse the input text to generate a number, and populate the result into item.
static const char *parse_number(JSON *item, const char *num)
{
    float n = 0, sign=1, scale=0; int subscale=0, signsubscale=1;

    if(*num=='-') sign=-1,num++;      // Has sign?
    if(*num=='0') num++;              // is zero
    if(*num>='1' && *num<='9') do n = (n*10.0) + (*num++ -'0'); while (*num>='0' && *num<='9');    // Number?
    if(*num=='.' && num[1]>='0' && num[1]<='9') {                                  // Fractional part?
        num++;
        do { n = (n*10.0) + (*num++ -'0');
            scale--; }
        while (*num>='0' && *num<='9');
    }
    if(*num=='e' || *num=='E')        // Exponent?
    {   num++;if(*num=='+') num++;    else if(*num=='-') signsubscale=-1,num++;    // With sign?
        while (*num>='0' && *num<='9') subscale=(subscale*10)+(*num++ - '0');      // Number?
    }

    n = sign*n*pow(10.0f, (scale+subscale*signsubscale));    // number = +/- number.fraction * 10^+/- exponent

    item->valuefloat = n;
    item->valueint = (int)n;
    item->type = JSON_NUMBER;
    return num;
}

/// Internal: Render the number nicely from the given item into a string.
static char *print_number(JSON *item)
{
	defformatstring(val, "%g", item->valuefloat);
	return newstring(val);
}

static unsigned parse_hex4(const char *str)
{
    unsigned h=0;
    if(*str>='0' && *str<='9') h+=(*str)-'0'; else if(*str>='A' && *str<='F') h+=10+(*str)-'A'; else if(*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
    h=h<<4;str++;
    if(*str>='0' && *str<='9') h+=(*str)-'0'; else if(*str>='A' && *str<='F') h+=10+(*str)-'A'; else if(*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
    h=h<<4;str++;
    if(*str>='0' && *str<='9') h+=(*str)-'0'; else if(*str>='A' && *str<='F') h+=10+(*str)-'A'; else if(*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
    h=h<<4;str++;
    if(*str>='0' && *str<='9') h+=(*str)-'0'; else if(*str>='A' && *str<='F') h+=10+(*str)-'A'; else if(*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
    return h;
}

/// Internal: Parse the input text into an unescaped cstring, and populate item.
static const unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
static const char *parse_string(JSON *item, const char *str)
{
    const char *ptr=str+1;
    char *ptr2, *out;
    int len=0;
    unsigned uc,uc2;
    if(*str!='\"') { ep = str; return 0; }  // not a string!

    while (*ptr!='\"' && *ptr && ++len) if(*ptr++ == '\\') ptr++;    // Skip escaped quotes.

    out = new char [len+1];                 // This is how long we need for the string, roughly.

    ptr = str+1; ptr2 = out;
    while (*ptr!='\"' && *ptr)
    {
        if(*ptr!='\\') *ptr2++ = *ptr++;
        else
        {
            ptr++;
            switch (*ptr)
            {
                case 'b': *ptr2++ = '\b';    break;
                case 'f': *ptr2++ = '\f';    break;
                case 'n': *ptr2++ = '\n';    break;
                case 'r': *ptr2++ = '\r';    break;
                case 't': *ptr2++ = '\t';    break;
                case 'u':     // transcode utf16 to utf8.
                    uc = parse_hex4(ptr+1);ptr+=4;      // get the unicode char.

                    if((uc>=0xDC00 && uc<=0xDFFF) || uc==0)    break;   // check for invalid.

                    if(uc>=0xD800 && uc<=0xDBFF)        // UTF16 surrogate pairs.
                    {
                        if(ptr[1]!='\\' || ptr[2]!='u')    break;       // missing second-half of surrogate.
                        uc2 = parse_hex4(ptr+3);ptr+=6;
                        if(uc2<0xDC00 || uc2>0xDFFF)        break;      // invalid second-half of surrogate.
                        uc = 0x10000 + (((uc&0x3FF)<<10) | (uc2&0x3FF));
                    }

                    len = 4;
                    if(uc<0x80) len=1;
                    else if(uc<0x800) len=2;
                    else if(uc<0x10000) len = 3;
                    ptr2 += len;

                    switch (len) {
                        case 4: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
                        case 3: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
                        case 2: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
                        case 1: *--ptr2 =(uc | firstByteMark[len]);
                    }
                    ptr2 += len;
                    break;
                default:  *ptr2++ = *ptr; break;
            }
            ptr++;
        }
    }
    *ptr2 = 0;
    if(*ptr=='\"') ptr++;
    item->valuestring = out;
    item->type = JSON_STRING;
    return ptr;
}

/// Internal: Render the cstring provided to an escaped version that can be printed.
static char *print_string_ptr(const char *str)
{
    const char *ptr; char *ptr2,*out; int len=0; unsigned char token;

    if(!str) return newstring("");
    ptr = str;
    while ((token=*ptr) && ++len) { if(strchr("\"\\\b\f\n\r\t", token)) len++; else if(token<32) len+=5; ptr++; }

    out = new char[len+3];
    if(!out) return 0;

    ptr2 = out;
    ptr = str;
    *ptr2++ = '\"';
    while (*ptr)
    {
        if((unsigned char)*ptr>31 && *ptr!='\"' && *ptr!='\\') *ptr2++ = *ptr++;
        else
        {
            *ptr2++ = '\\';
            switch (token = *ptr++)
            {
                case '\\':    *ptr2++ = '\\';    break;
                case '\"':    *ptr2++ = '\"';    break;
                case '\b':    *ptr2++ = 'b';    break;
                case '\f':    *ptr2++ = 'f';    break;
                case '\n':    *ptr2++ = 'n';    break;
                case '\r':    *ptr2++ = 'r';    break;
                case '\t':    *ptr2++ = 't';    break;
                default:
                    nformatstring(ptr2, len+3, "u%04x", token);
                    ptr2 += 5;
                    break;    // escape and print
            }
        }
    }
    *ptr2++ = '\"';
    *ptr2++ = 0;
    return out;
}

/// Internal: Invote print_string_ptr (which is useful) on an item.
static char *print_string(JSON *item) { return print_string_ptr(item->valuestring); }

/// Internal: Predeclare these prototypes.
static const char *parse_value(JSON *item, const char *value);
static char *print_value(JSON *item, int depth, bool fmt);
static const char *parse_array(JSON *item, const char *value);
static char *print_array(JSON *item, int depth, bool fmt);
static const char *parse_object(JSON *item, const char *value);
static char *print_object(JSON *item, int depth, bool fmt);

/// Internal: Utility to jump whitespace and cr/lf
static const char *skip(const char *in) {while (in && *in && (unsigned char)*in<=32) in++; return in;}

/// Internal: Parse an object - create a new root, and populate.
JSON *JSON_ParseWithOpts(const char *value, const char **return_parse_end, bool require_null_terminated)
{
    const char *end = 0;
    JSON *c = new JSON();
    ep = 0;

    end = parse_value( c, skip(value));
    if(!end) { delete c; return 0; }    // parse failure. ep is set.

    // if we require null-terminated JSON without appended garbage, skip and then check for a null terminator
    if(require_null_terminated)
    {
        end = skip(end);
        if(*end) { delete c; ep=end; return 0; }
    }
    if(return_parse_end) *return_parse_end = end;
    return c;
}
/// Internal: Default options for JSON_Parse
JSON *JSON_Parse(const char *value) { return JSON_ParseWithOpts(value, 0, false); }

/// Internal: Parser core - when encountering text, process appropriately.
static const char *parse_value(JSON *item, const char *value)
{
    if(!value)                        return 0;    // Fail on null.
    if(!strncmp(value, "null", 4))    { item->type = JSON_NULL;  return value+4; }
    if(!strncmp(value, "false",5))    { item->type = JSON_FALSE; return value+5; }
    if(!strncmp(value, "true", 4))    { item->type = JSON_TRUE;  item->valueint = 1; return value+4; }
    if(*value=='\"')                { return parse_string(item, value); }
    if(*value=='-' || (*value>='0' && *value<='9'))    { return parse_number(item, value); }
    if(*value=='[')                { return parse_array( item, value); }
    if(*value=='{')                { return parse_object(item, value); }

    ep = value; return 0;    // failure.
}

/// Internal: Render a value to text.
static char *print_value(JSON *item, int depth, bool fmt)
{
    char *out = 0;
    if(!item) return 0;
    if(item->original) { //imported item
        item = item->original;
    }
    switch (item->type)
    {
        case JSON_NULL:     out = newstring("null");    break;
        case JSON_FALSE:    out = newstring("false");   break;
        case JSON_TRUE:     out = newstring("true");    break;
        case JSON_NUMBER:   out = print_number(item);   break;
        case JSON_STRING:   out = print_string(item);   break;
        case JSON_ARRAY:    out = print_array( item, depth, fmt);break;
        case JSON_OBJECT:   out = print_object(item, depth, fmt);break;
    }
    return out;
}

/// Internal: Build an array from input text.
static const char *parse_array(JSON *item, const char *value)
{
    JSON *child;
    if(*value != '[')    { ep=value; return 0; }    // not an array!

    item->type = JSON_ARRAY;
    value = skip(value+1);
    if(*value==']') return value+1;    // empty array.

    item->firstchild = child = new JSON();
    child->parent = item;

    value = skip( parse_value(child, skip(value)));    // skip any spacing, get the value.
    if(!value) return 0;

    while(*value==',')
    {
        JSON *new_item = new JSON();
        new_item->parent = item;
        child->next = new_item;
        new_item->prev = child; child = new_item;
        value = skip( parse_value( child, skip(value+1)));
        if(!value) return 0;    // memory fail
    }

    if(*value==']') return value+1;    // end of array
    ep = value; return 0;    // malformed.
}

/// Internal: Render an array to text
static char *print_array(JSON *item, int depth, bool fmt)
{
    char **entries;
    char *out = 0, *ptr, *ret;
    int len = 5;

    JSON *child = item->firstchild;
    int numentries = 0 , i = 0, fail = 0;

    // How many entries in the array?
    while (child) numentries++, child = child->next;

    if(!numentries)// Explicitly handle numentries==0
    {
        out = new char[3];
        nformatstring(out, 3, "[]");
        return out;
    }
    // Allocate an array to hold the values for each
    entries = new char*[numentries*sizeof(char *)];
    if(!entries) return 0;
    memset(entries, 0, numentries*sizeof(char*));

    // Retrieve all the results:
    child = item->firstchild;
    while (child && !fail)
    {
        ret = print_value(child, depth+1, fmt);
        entries[i++] = ret;
        if(ret) len += strlen(ret) + 2 + (fmt?1:0);
        else fail = 1;
        child = child->next;
    }

    // If we didn't fail, try to malloc the output string
    if(!fail) out = new char[len];
    // If that fails, we fail.
    if(!out) fail = 1;

    // Handle failure.
    if(fail)
    {
        for (i=0; i<numentries; i++) delete[] entries[i];
        delete[] entries;
        return 0;
    }

    // Compose the output array.
    *out='[';
    ptr = out+1;
    *ptr = 0;
    for( i=0; i<numentries; i++)
    {
        strcpy(ptr, entries[i]);
        ptr += strlen(entries[i]);
        if(i!=numentries-1) { *ptr++=','; if(fmt) *ptr++=' '; *ptr=0;}
        delete[] entries[i];
    }
    delete[] entries;

    *ptr++=']'; *ptr++=0;
    return out;
}

/// Internal: Build an object from the text.
static const char *parse_object(JSON *item, const char *value)
{
    JSON *child;
    if(*value!='{') { ep = value; return 0; }    // not an object!

    item->type = JSON_OBJECT;
    value = skip(value+1);
    if(*value=='}') return value+1;    // empty array.

    item->firstchild = child = new JSON();
    child->parent = item;

    value = skip(parse_string(child, skip(value)));
    if(!value) return 0;
    child->name = child->valuestring;
    child->valuestring = NULL;

    if(*value!=':') { ep = value; return 0; }    // fail!
    value = skip(parse_value(child, skip(value+1)));    // skip any spacing, get the value.
    if(!value) return 0;

    while (*value==',')
    {
        JSON *new_item = new JSON();
        new_item->parent = item;
        child->next = new_item;
        new_item->prev = child; child = new_item;

        value = skip(parse_string(child, skip(value+1)));
        if(!value) return 0;
        child->name = child->valuestring;
        child->valuestring = NULL;

        if(*value!=':') { ep = value; return 0; }    // fail!
        value = skip(parse_value( child, skip(value+1)));    // skip any spacing, get the value.
        if(!value) return 0;
    }

    if(*value=='}') return value+1;    // end of array
    ep = value; return 0;    // malformed.
}

/// Internal: Render an object to text.
static char *print_object(JSON *item, int depth, bool fmt)
{
    char **entries = 0, **names = 0;
    char *out = 0, *ptr, *ret, *str;
    int len=7, i=0;

    JSON *child = item->firstchild;
    int numentries=0, fail=0;
    // Count the number of entries.
    while (child) numentries++, child = child->next;

    if(!numentries) // Explicitly handle empty object case
    {
        out=new char[fmt?depth+4:3];
        if(!out)    return 0;
        ptr = out;
        *ptr++='{';
        if(fmt) { *ptr++='\n'; for (i=0; i<depth-1; i++) *ptr++='\t';}
        *ptr++='}'; *ptr++=0;
        return out;
    }
    // Allocate space for the names and the objects
    entries = new char *[numentries*sizeof(char*)];
    if(!entries) return 0;
    names = new char *[numentries*sizeof(char*)];

    memset(entries, 0, sizeof(char*)*numentries);
    memset(names, 0, sizeof(char*)*numentries);

    // Collect all the results into our arrays:
    child = item->firstchild;
    depth++;
    if(fmt) len+=depth;
    while (child)
    {
        names[i] = str = print_string_ptr(child->name);
        entries[i++]= ret = print_value(child, depth, fmt);
        if(str && ret) len+= strlen(ret) + strlen(str) + 2 + (fmt ? depth+2 : 0);
        else fail=1;
        child = child->next;
    }

    // Try to allocate the output string
    if(!fail) out = new char[len];

    // Handle failure
    if(fail)
    {
        loopi(numentries) { delete[] names[i]; delete[] entries[i];}
        delete[] names;
        delete[] entries;
        return 0;
    }

    // Compose the output:
    *out = '{'; ptr = out+1;
    if(fmt) *ptr++ = '\n'; *ptr = 0;
    loopi(numentries)
    {
        if(fmt) loopj(depth) *ptr++ = '\t';
        strcpy(ptr, names[i]);
        ptr += strlen(names[i]);
        *ptr++=':'; if(fmt) *ptr++ = '\t';

        strcpy(ptr, entries[i]); ptr += strlen(entries[i]);
        if(i != numentries-1) *ptr++ = ',';
        if(fmt) *ptr++='\n'; *ptr = 0;
        delete[] names[i];
        delete[] entries[i];
    }

    delete[] names;
    delete[] entries;
    if(fmt) loopi(depth-1) *ptr++='\t';
    *ptr++='}';*ptr++=0;
    return out;
}

/// Minify JSON buffer (remove whitespaces and even comments).
void JSON_Minify(char *json)
{
    char *into = json;
    while (*json)
    {
        if (*json==' ') json++;
        else if (*json=='\t') json++;    // Whitespace characters.
        else if (*json=='\r') json++;
        else if (*json=='\n') json++;
        else if (*json=='/' && json[1]=='/')  while (*json && *json!='\n') json++;    // double-slash comments, to end of line.
        else if (*json=='/' && json[1]=='*') { while (*json && !(*json=='*' && json[1]=='/')) json++; json += 2;}    // multiline comments.
        else if (*json=='\"') {          // string literals, which are \" sensitive.
            *into++ = *json++;
            while (*json && *json!='\"')
            {
                if (*json=='\\') *into++ = *json++;
                *into++ = *json++;
            }
            *into++ = *json++;
        }
        else *into++=*json++;            // All other characters.
    }
    *into=0;    // and null-terminate.
}

/// Basic and really simplistic routine to fix malformatted .json files
/// It will replace the old version of your file on success and create a backup of the old one (called <filename>_backup.json)
/// Currently it fixes: double commata, missing " for non-numeric strings
int JSON_Fix(const char *filename)
{
    string s;
    copystring(s, filename);
    const char *found = findfile(path(s), "");
    char *buf = loadfile(found, NULL);
    if(!buf) return -1;
    JSON_Minify(buf);

    size_t len = strlen(buf);

    char *newbuf = new char[len + 1];

    size_t pos = 0; //current position in the newbuf
    for(size_t i = 0; i < len; i++)
    {
        if(buf[i] == ',')
        {
                if(!i) i++;                     //buf starts with a commata
                else if(buf[i + 1] == ',') i++; //two subsequent commata
                else
                {
                    newbuf[pos] = buf[i];
                    pos++;
                }
        }
        else if(isalpha(buf[i]))
        {
            if(!i) //todo worst case: is it an array or object?
                return 0;
            else if(buf[i - 1] != '\"') {
                newbuf[pos] = '\"'; pos++;
            } //string was missing a leading "
            newbuf[pos] = buf[i];
            pos++;
        }
        else
        {
            if(i && isalpha(i - 1)) {
                newbuf[pos] = '\"'; pos++;
            } //string was missing a trailing "
            newbuf[pos] = buf[i];
            pos++;
        }
    }

    JSON *j = JSON_Parse(newbuf);
    if(j)
    {
        conoutf("%s was malformatted but has been fixed automatically. \nThe original file has been overwritten, but backuped", found);
        //cutextension .. getextension
        defformatstring(backupname, "%s_backup", found);
        if(!rename(found, backupname)) j->save(found);
        delete j;
        delete[] buf;
        delete[] newbuf;
        return 1;
    }

    delete[] buf;
    delete[] newbuf;
    return 0;
}

#define IMPORTPHRASE "#import"

/// Replace an occurence of string from in string src with string to.
/// @example replace("hallo welt",
// TODO


void JSON_ResolveReplacements(JSON *g, JSON *replacements)
{
    if(!g || !replacements) return;
    foralljsonchildren(replacements, k,
    {
        foralljson(g, h,
        {
            if(g->name && k->name && strstr(g->name, k->name));
        })
    })
}

/// "anims": { "#import" : { "file": "generics.json", "key": "animations", "replace": { "arg4" : "codefragment" }
/// "anims": { "#import" : { "file": "generics.json", "key": "animations", "replace": { "arg4" : { "#import": } }
/// "$moreanims": { "#import" : "generics.json" },
/// "anims": [ "anim1", "anim2", "anim3", "$moreanims"]
bool JSON_ResolveImport(JSON *g)
{
    JSON *j = g->getchild(IMPORTPHRASE);
    JSON *f = NULL;       // the exporting file: "generics.json"
    JSON *newg = NULL;    // the JSON which will replace the old section

    if(!j) return false;

    JSON *src = j->getchild("file");
    JSON *key = j->getchild("key");
    JSON *replace = j->getchild("replace");

    if(!src) { return false; }
    const char *srcname = src->valuestring;
    f = loadjson(srcname);

    if(!f) { return false; }

    if(key) {
        newg = f->getchild(key->valuestring);
    }
    else newg = f;

    if(!newg){ return false; }

    JSON_ResolveReplacements(newg, replace);

    // Replace g with newg:
    if(g->name) copystring(newg->name, g->name, strlen(g->name)); // "anims"
    newg->parent = g->parent;

    newg->next = g->next;
    newg->prev = g->prev;

    // tell the others
    if(g->next) g->next->prev = newg;
    if(g->parent->firstchild == g) g->parent->firstchild = newg;
    else g->prev->next = newg;

    newg->original = g;
    return true;
}

/// Load all occurences of import-markers from the referring json-files.
void JSON_ResolveImports(JSON *j)
{
    foralljson(j, k,
    {
        if(k->getchild(IMPORTPHRASE)) JSON_ResolveImport(k);
    }
    )
}

/// Load a JSON File and display its contents.
void testjson(const char *name)
{
    JSON *j = loadjson(name);
    if(!j) { conoutf("could not load testjson file"); return; }
    JSON_ResolveImports(j);
    conoutf("content %s", j->render());
}
COMMAND(testjson, "s");

// Create basic types:
JSON *JSON_CreateBool(bool b)               { JSON *item= new JSON(); item->type = b ? JSON_TRUE : JSON_FALSE;  return item; }
JSON *JSON_CreateInt(int num)               { JSON *item= new JSON(); item->type = JSON_NUMBER;     item->valueint = num; item->valuefloat = num; return item; }
JSON *JSON_CreateFloat(float num)           { JSON *item= new JSON(); item->type = JSON_NUMBER;     item->valuefloat = num;     return item; }
JSON *JSON_CreateString(const char *str)    { if(!str) return NULL; JSON *item = new JSON(); item->type = JSON_STRING;     item->valuestring = newstring(str);  return item; }
JSON *JSON_CreateArray()                    { JSON *item= new JSON(); item->type = JSON_ARRAY;      return item; }
JSON *JSON_CreateObject()                   { JSON *item= new JSON(); item->type = JSON_OBJECT;     return item; }

/// Load a .json file.
/// @sideeffects allocates memory for a JSON structure, needs to be deleted.
JSON *loadjson(const char *filename)
{
    if(!filename) return NULL;

    string s;
    copystring(s, filename);
    char *buf = loadfile(path(s), NULL);
    if(!buf)
    {
        conoutf(CON_WARN, "could not find %s", s);
        return NULL;
    }
    JSON *j = JSON_Parse(buf);
    if(!j)
    {
        conoutf(CON_WARN, "JSON File %s malformatted. (Use /debugjson to enable find error position)", s);
        if(debugjson) conoutf(CON_DEBUG, "could not parse: %s", ep ? ep : "");
       // if(JSON_Fix(filename)) j = loadjson(filename);
        return NULL;
    }
    j->currentfile = newstring(s);
    foralljsonchildren(j, k, k->currentfile = j->currentfile;);

    delete[] buf;
    return j;
}

char *JSON::render(bool formatted, bool minified) {
    char *out = print_value(this, 0, formatted);
    if(minified) JSON_Minify(out);
    return out;
}

void JSON::addchild(JSON *item)
{
    if(!item) return;

    if(!currentfile || !item->currentfile || strcmp(item->currentfile, currentfile) )
    {
        delete[] item->currentfile;
        foralljson(item, k, k->currentfile = currentfile;);
    }

    item->parent = this;

    JSON *c = firstchild; //rewire:
    if(!c) { firstchild = item; }
    else
    { //last place in the chain
        while(c && c->next) c = c->next;
        c->next = item;
        item->prev = c;
    }
}

void JSON::replacechild(int which, JSON *newitem)
{
    JSON *c = firstchild;
    while(c && which>0) { c = c->next; which--; }
    if(!c) return;

    if(type != JSON_ARRAY && !newitem->name && c->name) newitem->name = newstring(c->name); //misuse prevention
    if(!currentfile || !newitem->currentfile || strcmp(newitem->currentfile, c->currentfile))
    {
        foralljson(newitem, k, k->currentfile = c->currentfile;);
    }

    newitem->parent = this;
    newitem->next = c->next;
    newitem->prev = c->prev;
    if(newitem->next) newitem->next->prev = newitem;

    if(c == firstchild) firstchild = newitem;
    else newitem->prev->next = newitem;
    DELETEP(c);
}

// TODO:
// refractor replace, addchild, replaceimport
// namespace ? 
// class instead of struct ?
