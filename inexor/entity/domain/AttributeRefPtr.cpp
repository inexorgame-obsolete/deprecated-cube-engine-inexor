/*
 * AttributeRefPtr.cpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#include "AttributeRefPtr.hpp"
#include "FunctionRefPtr.hpp"
#include "inexor/engine/engine.hpp"

namespace inexor {
namespace entity {

    AttributeRefPtr::AttributeRefPtr() : parent(std::make_shared<EntityAttribute>()) {}

    AttributeRefPtr::AttributeRefPtr(EntityAttribute* p) : parent(p)
    {
        EntityAttribute* attr = this->get();
        attr->type = p->type;
        attr->name = p->name;
        attr->intVal = p->intVal;
        attr->floatVal = p->floatVal;
        attr->doubleVal = p->doubleVal;
        attr->vec3Val = p->vec3Val;
        attr->vec4Val = p->vec4Val;
        attr->stringVal = p->stringVal;
        attr->functionVal = p->functionVal;
        attr->initialized = true;
    }

    AttributeRefPtr::AttributeRefPtr(const std::shared_ptr<EntityAttribute>& r) : parent(r)
    {
        EntityAttribute* attr = this->get();
        attr->type = r->type;
        attr->name = r->name;
        attr->intVal = r->intVal;
        attr->floatVal = r->floatVal;
        attr->vec3Val = r->vec3Val;
        attr->vec4Val = r->vec4Val;
        attr->doubleVal = r->doubleVal;
        attr->stringVal = r->stringVal;
        attr->functionVal = r->functionVal;
        attr->initialized = true;
    }

    AttributeRefPtr::AttributeRefPtr(bool value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(int value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(float value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(double value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(vec value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(double x, double y, double z) : parent(std::make_shared<EntityAttribute>(x, y, z)) {}

    AttributeRefPtr::AttributeRefPtr(vec4 value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(double x, double y, double z, double w) : parent(std::make_shared<EntityAttribute>(x, y, z, w)) {}

    AttributeRefPtr::AttributeRefPtr(std::string value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(FunctionRefPtr value) : parent(std::make_shared<EntityAttribute>(value)) {}

    AttributeRefPtr::AttributeRefPtr(FunctionRefPtr *value) : parent(std::make_shared<EntityAttribute>(*value)) {}

    EntityAttribute& AttributeRefPtr::operator=(const EntityAttribute &attribute)
    {
        EntityAttribute* attr = this->get();
        attr->type = attribute.type;
        attr->intVal = attribute.intVal;
        attr->doubleVal = attribute.doubleVal;
        attr->vec3Val = attribute.vec3Val;
        attr->vec4Val = attribute.vec4Val;
        attr->floatVal = attribute.floatVal;
        attr->stringVal = attribute.stringVal;
        attr->functionVal = attribute.functionVal;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const AttributeRefPtr &r)
    {
        EntityAttribute* attr = this->get();
        attr->type = r->type;
        attr->intVal = r->intVal;
        attr->floatVal = r->floatVal;
        attr->doubleVal = r->doubleVal;
        attr->vec3Val = r->vec3Val;
        attr->vec4Val = r->vec4Val;
        attr->stringVal = r->stringVal;
        attr->functionVal = r->functionVal;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const bool &b)
    {
        EntityAttribute* attr = this->get();
        bool b1 = b;
        attr->type = b1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const int &i)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_INT;
        int i1 = i;
        attr->intVal = i1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const float &f)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_FLOAT;
        float f1 = f;
        attr->floatVal = f1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const double &d)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_DOUBLE;
        double d1 = d;
        attr->doubleVal = d1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const vec &v3)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_VEC3;
        vec v = v3;
        attr->vec3Val = v;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const vec4 &v4)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_VEC4;
        vec4 v = v4;
        attr->vec4Val = v;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const std::string &s)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_STRING;
        std::string s1 = s;
        attr->stringVal = s1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(const FunctionRefPtr &f)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_FUNCTION;
        FunctionRefPtr f1 = f;
        attr->functionVal = f1;
        return *attr;
    }

    EntityAttribute& AttributeRefPtr::operator=(FunctionRefPtr &f)
    {
        EntityAttribute* attr = this->get();
        attr->type = ENTATTR_FUNCTION;
        attr->functionVal = f;
        return *attr;
    }

    AttributeRefPtr& AttributeRefPtr::operator+(const AttributeRefPtr &r)
    {
        EntityAttribute* attr = this->get();
        if (attr) switch(attr->type)
        {
            case ENTATTR_INT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->intVal += r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->intVal += (int) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->intVal += (int) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_FLOAT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->floatVal += (float) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->floatVal += r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->floatVal += (float) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_DOUBLE:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->doubleVal += (double) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->doubleVal += (double) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->doubleVal += r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_STRING:
            {
                switch(r->type)
                {
                    case ENTATTR_STRING:
                        attr->stringVal += r->stringVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return *this;
    }

    int AttributeRefPtr::operator+(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_INT)
            return attr->intVal + i;
        return 0;
    }

    float AttributeRefPtr::operator+(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->floatVal + f;
        return 0.0f;
    }

    double AttributeRefPtr::operator+(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->doubleVal + d;
        return 0.0;
    }

    std::string AttributeRefPtr::operator+(std::string s)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_STRING)
            return attr->stringVal + s;
        return std::string("");
    }

    AttributeRefPtr& AttributeRefPtr::operator-(const AttributeRefPtr &r)
    {
        EntityAttribute* attr = this->get();
        if (attr) switch(attr->type)
        {
            case ENTATTR_INT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->intVal -= r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->intVal -= (int) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->intVal -= (int) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_FLOAT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->floatVal -= (float) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->floatVal -= r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->floatVal -= (float) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_DOUBLE:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->doubleVal -= (double) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->doubleVal -= (double) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->doubleVal -= r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return *this;
    }

    int AttributeRefPtr::operator-(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_INT)
            return attr->intVal - i;
        return 0;
    }

    float AttributeRefPtr::operator-(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->floatVal - f;
        return 0.0f;
    }

    double AttributeRefPtr::operator-(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->doubleVal - d;
        return 0.0;
    }

    AttributeRefPtr& AttributeRefPtr::operator*(const AttributeRefPtr &r)
    {
        EntityAttribute* attr = this->get();
        if (attr) switch(attr->type)
        {
            case ENTATTR_INT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->intVal *= r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->intVal *= (int) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->intVal *= (int) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_FLOAT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->floatVal *= (float) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->floatVal *= r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->floatVal *= (float) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_DOUBLE:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        attr->doubleVal *= (double) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        attr->doubleVal *= (double) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        attr->doubleVal *= r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return *this;
    }

    int AttributeRefPtr::operator*(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_INT)
            return attr->intVal * i;
        return 0;
    }

    float AttributeRefPtr::operator*(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->floatVal * f;
        return 0.0f;
    }

    double AttributeRefPtr::operator*(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT)
            return attr->doubleVal * d;
        return 0.0;
    }

    AttributeRefPtr& AttributeRefPtr::operator/(const AttributeRefPtr &r)
    {
        EntityAttribute* attr = this->get();
        if (attr) switch(attr->type)
        {
            case ENTATTR_INT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        if (r->intVal != 0)
                            attr->intVal /= r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        if (r->floatVal != 0.0f)
                            attr->intVal /= (int) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        if (r->doubleVal != 0.0)
                            attr->intVal /= (int) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_FLOAT:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        if (r->intVal != 0)
                            attr->floatVal /= (float) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        if (r->floatVal != 0.0f)
                            attr->floatVal /= r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        if (r->doubleVal != 0.0)
                            attr->floatVal /= (float) r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            case ENTATTR_DOUBLE:
            {
                switch(r->type)
                {
                    case ENTATTR_INT:
                        if (r->intVal != 0)
                            attr->doubleVal /= (double) r->intVal;
                        break;
                    case ENTATTR_FLOAT:
                        if (r->floatVal != 0.0f)
                            attr->doubleVal /= (double) r->floatVal;
                        break;
                    case ENTATTR_DOUBLE:
                        if (r->doubleVal != 0.0)
                            attr->doubleVal /= r->doubleVal;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return *this;
    }

    int AttributeRefPtr::operator/(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_INT && i != 0)
            return attr->intVal / i;
        return 0;
    }

    float AttributeRefPtr::operator/(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT && f != 0.0f)
            return attr->floatVal / f;
        return 0.0f;
    }

    double AttributeRefPtr::operator/(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_FLOAT && d != 0.0)
            return attr->doubleVal / d;
        return 0.0;
    }

    AttributeRefPtr& AttributeRefPtr::operator+=(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal += i;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal += i;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal += i;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator+=(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal += (int) f;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal += f;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal += (double) f;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator+=(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal += (int) d;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal += (float) d;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal += d;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator+=(std::string s)
    {
        EntityAttribute* attr = this->get();
        if (attr && attr->type == ENTATTR_STRING)
            attr->stringVal += s;
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator-=(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal -= i;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal -= i;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal -= i;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator-=(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal -= (int) f;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal -= f;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal -= (double) f;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator-=(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal -= (int) d;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal -= (float) d;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal -= d;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator*=(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal *= i;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal *= i;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal *= i;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator*=(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal *= (int) f;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal *= f;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal *= (double) f;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator*=(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal *= (int) d;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal *= (float) d;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal *= d;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator/=(int i)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal /= i;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal /= i;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal /= i;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator/=(float f)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal /= (int) f;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal /= f;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal /= (double) f;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr& AttributeRefPtr::operator/=(double d)
    {
        EntityAttribute* attr = this->get();
        if (attr)
        {
            switch(attr->type)
            {
                case ENTATTR_INT:
                    attr->intVal /= (int) d;
                    break;
                case ENTATTR_FLOAT:
                    attr->floatVal /= (float) d;
                    break;
                case ENTATTR_DOUBLE:
                    attr->doubleVal /= d;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step)
    {
        return get()->functionVal->Execute(time_step);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type)
    {
        return get()->functionVal->Execute(time_step, type);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst)
    {
        return get()->functionVal->Execute(time_step, type, inst);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst)
    {
        return get()->functionVal->Execute(time_step, inst);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type)
    {
        return get()->functionVal->Execute(time_step, inst, rel_type);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        return get()->functionVal->Execute(time_step, inst, rel_inst);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2)
    {
        return get()->functionVal->Execute(time_step, inst_1, inst_2);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3)
    {
        return get()->functionVal->Execute(time_step, inst_1, inst_2, inst_3);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type)
    {
        return get()->functionVal->Execute(time_step, inst_1, inst_2, rel_type);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        return get()->functionVal->Execute(time_step, inst_1, inst_2, rel_inst);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type)
    {
        return get()->functionVal->Execute(time_step, type);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst)
    {
        return get()->functionVal->Execute(time_step, type, inst);
    }

    AttributeRefPtr AttributeRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst)
    {
        return get()->functionVal->Execute(time_step, inst);
    }

}
}
