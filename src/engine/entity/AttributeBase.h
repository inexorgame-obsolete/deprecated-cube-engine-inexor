/*
 * AttributeBase.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ATTRIBUTEBASE_H_
#define SRC_ENGINE_ENTITY_ATTRIBUTEBASE_H_

#include "EntitySystemBase.h"
#include "EntityAttribute.h"

class AttributeBase
{
    public:
        AttributeBase();
        virtual ~AttributeBase();

        AttributeRefPtr operator[](std::string key) const;
        AttributeRefPtr & operator[](std::string key);

        void AddAttribute(std::string key, AttributeRefPtr attribute) {
            attribute.get()->name = key;
            attributes[key] = attribute;
        }

        void AddAttribute(std::string key, bool value) {
            attributes[key] = value;
            attributes[key]->type = value;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, int value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_INT;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, float value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_FLOAT;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, double value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_DOUBLE;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, std::string value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_STRING;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, FunctionRefPtr action) {
            attributes[key] = action;
            attributes[key]->type = ENTATTR_FUNCTION;
            attributes[key]->name = key;
        }

        AttributeRefPtr GetAttribute(std::string key) {
            return attributes[key];
        }

    protected:

        /**
         * The attributes of this type.
         */
        std::map<std::string, AttributeRefPtr> attributes;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(AttributeBase);
};

#endif /* SRC_ENGINE_ENTITY_ATTRIBUTEBASE_H_ */
