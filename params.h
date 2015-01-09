#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <utility>
#include <list>
#include <map>
#include <string>

using namespace std;

class Params;

class param
{
public:
    param() : child(NULL) {}
    string name;
    string value;
    pair<string,string> prop;
    Params *child;
};

class Params
{
    public:
        Params() {}
        ~Params() {}

        void addParam(string name, string value, pair<string,string> prop, Params *child)
        {
            param p;
            p.child = child;
            p.name = name;
            p.value = value;
            p.prop = prop;
            _params.insert(_params.end(),p);
        }

        void addParam(string name, string value, pair<string,string> prop)
        {
            addParam(name, value, prop, NULL);
        }

        void addParam(string name, string value)
        {
            addParam(name, value, pair<string,string>(), NULL);
        }

        void addParam(string name, pair<string,string> prop)
        {
            addParam(name, string(), prop, NULL);
        }

        void addParam(string name, Params *p)
        {
            addParam(name, string(), pair<string,string>(), p);
        }

    //private:
        list<struct param> _params;
};

#endif ///< __PARAMS_H__
