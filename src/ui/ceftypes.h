#ifndef _CEF_TYPES_H
#define _CEF_TYPES_H

#include <list>

struct InexorCefValue {
    public:
        InexorCefValue(int v)          : type(0), _int(v), _uint(0), _double(0.0), _str("") {};
        InexorCefValue(unsigned int v) : type(1), _int(0), _uint(v), _double(0.0), _str("") {};
        InexorCefValue(double v)       : type(2), _int(0), _uint(0), _double(v),   _str("") {};
        InexorCefValue(std::string v)  : type(3), _int(0), _uint(0), _double(0.0), _str(v)  {};
        int GetIntValue() { return _int; };
        unsigned int GetUIntValue() { return _uint; };
        double GetDoubleValue() { return _double; };
        std::string GetStringValue() { return _str; };
        CefRefPtr<CefV8Value> GetValue() {
            switch (type) {
                case 0:
                    return CefV8Value::CreateInt(_int);
                case 1:
                    return CefV8Value::CreateUInt(_uint);
                case 2:
                    return CefV8Value::CreateDouble(_double);
                case 3:
                    return CefV8Value::CreateString(_str);
                default:
                    return CefV8Value::CreateUndefined();
            }
        };

    private:
        int type;
        int _int;
        unsigned int _uint;
        double _double;
        std::string _str;

        IMPLEMENT_REFCOUNTING(InexorCefValue);

};

typedef std::list<CefRefPtr<InexorCefValue> > InexorCefValueList;

#endif  // _CEF_TYPES_H
