//  Rewrite of cJSON 1.0r58 in Inexor-optimized object-orientated C-ish C++
//  cJSON (Copyright (c) 2009 by Dave Gamble) is licensed under the MIT-license

#include "engine.h"

 // Parse the input text to generate a number, and populate the result into item.
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

 // Render the number nicely from the given item into a string.
static char *print_number(JSON *item)
{
    char *str;
    float d = item->valuefloat;
    if(fabs(((float)item->valueint)-d) <= FLT_EPSILON && d<=INT_MAX && d>=INT_MIN)
    {
        str= new char[21];    // 2^64+1 can be represented in 21 chars.
        formatstring(str) ("%d", item->valueint);
    }
    else
    {
        str= new char[64];    // This is a nice tradeoff.
        if(str)
        {
            if(fabs(floor(d)-d)<=FLT_EPSILON && fabs(d)<1.0e60) formatstring(str)("%.0f",d);
            else if(fabs(d)<1.0e-6 || fabs(d)>1.0e9)            formatstring(str)("%e",d);
            else                                                formatstring(str)("%f",d);
        }
    }
    return str;
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

 // Parse the input text into an unescaped cstring, and populate item.
static const char *ep; //error pointer
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
    if(!out) return 0;

    ptr=str+1;ptr2=out;
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

 // Render the cstring provided to an escaped version that can be printed.
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
                    formatstring(ptr2) ("u%04x", token);
                    ptr2 += 5;
                    break;    // escape and print
            }
        }
    }
    *ptr2++ = '\"';
    *ptr2++ = 0;
    return out;
}

 // Invote print_string_ptr (which is useful) on an item.
static char *print_string(JSON *item) { return print_string_ptr(item->valuestring); }

 // Predeclare these prototypes.
static const char *parse_value(JSON *item, const char *value);
static char *print_value(JSON *item, int depth, bool fmt);
static const char *parse_array(JSON *item, const char *value);
static char *print_array(JSON *item, int depth, bool fmt);
static const char *parse_object(JSON *item, const char *value);
static char *print_object(JSON *item, int depth, bool fmt);

 // Utility to jump whitespace and cr/lf
static const char *skip(const char *in) {while (in && *in && (unsigned char)*in<=32) in++; return in;}

 // Parse an object - create a new root, and populate.
JSON *JSON_ParseWithOpts(const char *value, const char **return_parse_end, bool require_null_terminated)
{
    const char *end = 0;
    JSON *c= new JSON();
    ep = 0;

    end = parse_value( c, skip(value));
    if(!end) { DELETEP(c); return 0; }    // parse failure. ep is set.

    // if we require null-terminated JSON without appended garbage, skip and then check for a null terminator
    if(require_null_terminated)
    {
        end = skip(end);
        if(*end) { DELETEP(c); ep=end; return 0; }
    }
    if(return_parse_end) *return_parse_end = end;
    return c;
}
 // Default options for JSON_Parse
JSON *JSON_Parse(const char *value) { return JSON_ParseWithOpts(value, 0, false); }

 // Parser core - when encountering text, process appropriately.
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

 // Render a value to text.
char *print_value(JSON *item, int depth, bool fmt)
{
    char *out = 0;
    if(!item) return 0;
    switch ((item->type)&255)
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

 // Build an array from input text.
static const char *parse_array(JSON *item, const char *value)
{
    JSON *child;
    if(*value != '[')    { ep=value; return 0; }    // not an array!

    item->type = JSON_ARRAY;
    value = skip(value+1);
    if(*value==']') return value+1;    // empty array.

    item->child = child = new JSON();

    value = skip( parse_value(child, skip(value)));    // skip any spacing, get the value.
    if(!value) return 0;

    while (*value==',')
    {
        JSON *new_item = new JSON();
        child->next = new_item;
        new_item->prev = child; child = new_item;
        value = skip( parse_value( child, skip(value+1)));
        if(!value) return 0;    // memory fail
    }

    if(*value==']') return value+1;    // end of array
    ep = value; return 0;    // malformed.
}

 // Render an array to text
static char *print_array(JSON *item, int depth, bool fmt)
{
    char **entries;
    char *out = 0, *ptr, *ret;
    int len = 5;

    JSON *child = item->child;
    int numentries = 0 , i = 0, fail = 0;

    // How many entries in the array?
    while (child) numentries++, child = child->next;

    if(!numentries)// Explicitly handle numentries==0
    {
        out = new char[3];
        formatstring(out)("[]");
        return out;
    }
    // Allocate an array to hold the values for each
    entries = new char*[numentries*sizeof(char *)];
    if(!entries) return 0;
    memset(entries, 0, numentries*sizeof(char*));

    // Retrieve all the results:
    child = item->child;
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
        for (i=0; i<numentries; i++) DELETEA(entries[i]);
        DELETEA(entries);
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
        DELETEA(entries[i]);
    }
    DELETEA(entries);

    *ptr++=']'; *ptr++=0;
    return out;
}

 // Build an object from the text.
static const char *parse_object(JSON *item, const char *value)
{
    JSON *child;
    if(*value!='{') { ep = value; return 0; }    // not an object!

    item->type = JSON_OBJECT;
    value = skip(value+1);
    if(*value=='}') return value+1;    // empty array.

    item->child = child = new JSON();
    if(!item->child) return 0;

    value = skip(parse_string(child, skip(value)));
    if(!value) return 0;
    child->name = child->valuestring;
    child->valuestring = 0;

    if(*value!=':') { ep = value; return 0; }    // fail!
    value = skip(parse_value(child, skip(value+1)));    // skip any spacing, get the value.
    if(!value) return 0;

    while (*value==',')
    {
        JSON *new_item = new JSON();
        child->next = new_item;
        new_item->prev = child; child = new_item;

        value = skip(parse_string(child, skip(value+1)));
        if(!value) return 0;
        child->name = child->valuestring;
        child->valuestring = 0;

        if(*value!=':') { ep = value; return 0; }    // fail!
        value = skip(parse_value( child, skip(value+1)));    // skip any spacing, get the value.
        if(!value) return 0;
    }

    if(*value=='}') return value+1;    // end of array
    ep = value; return 0;    // malformed.
}

 // Render an object to text.
static char *print_object(JSON *item, int depth, bool fmt)
{
    char **entries = 0, **names = 0;
    char *out = 0, *ptr, *ret, *str;
    int len=7, i=0;

    JSON *child=item->child;
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
    if(!names) { DELETEA(entries); return 0; }

    memset(entries, 0, sizeof(char*)*numentries);
    memset(names, 0, sizeof(char*)*numentries);

    // Collect all the results into our arrays:
    child = item->child;
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
        loopi(numentries) { if(names[i]) DELETEA(names[i]); if(entries[i]) DELETEA(entries[i]);}
        DELETEA(names);
        DELETEA(entries);
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
        DELETEA(names[i]);
        DELETEA(entries[i]);
    }

    DELETEA(names);
    DELETEA(entries);
    if(fmt) loopi(depth-1) *ptr++='\t';
    *ptr++='}';*ptr++=0;
    return out;
}

//Minify JSON buffer
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

// Create basic types:
JSON *JSON_CreateBool(bool b)               { JSON *item= new JSON(); item->type = b ? JSON_TRUE : JSON_FALSE;  return item; }
JSON *JSON_CreateInt(int num)               { JSON *item= new JSON(); item->type = JSON_NUMBER;     item->valueint = num;       return item; }
JSON *JSON_CreateFloat(float num)           { JSON *item= new JSON(); item->type = JSON_NUMBER;     item->valuefloat = num;     return item; }
JSON *JSON_CreateString(const char *str)    { JSON *item= new JSON(); item->type = JSON_STRING;     item->valuestring = newstring(str);  return item; }
JSON *JSON_CreateArray()                    { JSON *item= new JSON(); item->type = JSON_ARRAY;      return item; }
JSON *JSON_CreateObject()                   { JSON *item= new JSON(); item->type = JSON_OBJECT;     return item; }

static void suffix_object(JSON *prev, JSON *item) { prev->next = item; item->prev = prev; }  // Utility for array list handling.

// Create Arrays:
JSON *JSON_CreateIntArray(const int *numbers, int count)
{
    JSON *last = NULL, *out = JSON_CreateArray();
    loopi(count)
    {
        JSON *cur = JSON_CreateInt(numbers[i]);
        if(!i) out->child = cur;
        else suffix_object(last, cur);
        last = cur;
    }
    return out;
}

JSON *JSON_CreateFloatArray(const float *numbers, int count)
{
    JSON *last = NULL, *out = JSON_CreateArray();
    loopi(count)
    {
        JSON *cur = JSON_CreateFloat(numbers[i]);
        if(!i) out->child = cur;
        else suffix_object(last, cur);
        last = cur;
    }
    return out;
}

JSON *JSON_CreateStringArray(const char **strings, int count)
{
    JSON *last = NULL, *out = JSON_CreateArray();
    loopi(count)
    {
        JSON *cur = JSON_CreateString(strings[i]);
        if(!i) out->child = cur;
        else suffix_object(last, cur);
        last = cur;
    }
    return out;
}

 //Loads .JSON file
JSON *loadjson(const char *filename)
{
    string s;
    copystring(s, filename);
    char *buf = loadfile(path(s), NULL);
    return JSON_Parse(buf);
}

//not used yet:
//int    cJSON_GetArraySize(cJSON *array)                            {cJSON *c=array->child;int i=0;while(c)i++,c=c->next;return i;}
//void    cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)                        {cJSON_AddItemToArray(array,create_reference(item));}
//void    cJSON_AddItemReferenceToObject(cJSON *object,const char *string,cJSON *item)    {cJSON_AddItemToObject(object,string,create_reference(item));}

//JSON *JSON_CreateTrue()                        { JSON *item= new JSON(); item->type = JSON_TRUE;   return item; }
//JSON *JSON_CreateFalse()                    { JSON *item= new JSON(); item->type = JSON_FALSE;  return item; }
//cJSON *cJSON_CreateNumber(double num)            {cJSON *item=cJSON_New_Item();if(item){item->type=cJSON_Number;item->valuedouble=num;item->valueint=(int)num;}return item;} //its int or float now