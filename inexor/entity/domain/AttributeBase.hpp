/*
 * AttributeBase.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEBASE_H_
#define SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEBASE_H_

#include "../EntitySystemBase.hpp"
#include "AttributeRefPtr.hpp"

class vec;
class vec4;

namespace inexor {
namespace entity {

class AttributeBase
{
    public:
        AttributeBase();
        virtual ~AttributeBase();

        virtual AttributeRefPtr GetAttribute(std::string key);
        void SetAttribute(std::string key, AttributeRefPtr attributeRefPtr);
        bool HasAttribute(std::string key);

        virtual AttributeRefPtr operator[](std::string key) const;
        virtual AttributeRefPtr & operator[](std::string key);

        void AddAttribute(std::string key, AttributeRefPtr attribute);
        void AddAttribute(std::string key, bool value);
        void AddAttribute(std::string key, int value);
        void AddAttribute(std::string key, float value);
        void AddAttribute(std::string key, double value);
        void AddAttribute(std::string key, vec value);
        void AddAttribute(std::string key, double x, double y, double z);
        void AddAttribute(std::string key, vec4 value);
        void AddAttribute(std::string key, double x, double y, double z, double w);
        void AddAttribute(std::string key, std::string value);
        void AddAttribute(std::string key, FunctionRefPtr action);

    protected:

        /**
         * The attributes of this type.
         * TODO: std::unordered_map (C++11)
         */
        std::unordered_map<std::string, AttributeRefPtr> attributes;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(AttributeBase);
};

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEBASE_H_ */
