/*
factory_registry: A simple way to registry derived classes without .h file
    Copyright (C) 2012  Leandro Ramos, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FACTORY_REGISTRY_H
#   error Internal header file, DO NOT include this.
#endif
#include<string>

template <class BaseClass, class Key = std::string>
class FactoryRegistry
{
private:
    Factory<Key, BaseClass> fc;
    static FactoryRegistry<BaseClass, Key>* instance;
    unsigned int users;

    FactoryRegistry(): users(0) {}

    template <class DerivedClass>
    void _register_factory(const Key& k)
    {
        users++;
        fc.register_factory<DerivedClass>(k);
    }
    BaseClass* _new_class(Key& k)
    {
        return fc.new_class(k);;
    }
    bool _deregister_factory()
    {
        users--;
        return (users == 0);
    }
public:
    template<class DerivedClass>
    static void register_factory(const Key& k)
    {
        if (instance == NULL)
            instance = new FactoryRegistry<BaseClass, Key>;
        instance->_register_factory<DerivedClass>(k);
    }
    static BaseClass* new_class(Key& k)
    {
        return instance->_new_class(k);
    }
    static void deregister_factory()
    {
        if (instance->_deregister_factory())
            delete instance;
        instance = NULL;
    }

};
template<class Base, class Key> FactoryRegistry<Base,Key> * FactoryRegistry<Base,Key>::instance = 0;

template<class BaseClass, class DerivedClass>
class Registerer
{
public:
    template <class Key>
    Registerer(const Key& k)
    {
        mili::FactoryRegistry<BaseClass, Key>::template register_factory<DerivedClass>(k);
    }
    template<class Key>
    ~Registerer()
    {
        mili::FactoryRegistry<BaseClass, Key>::template deregister_factory();
    }
};

#define REGISTER_FACTORIZABLE_CLASS(BaseClassName, DerivedClassName, key) \
static mili::Registerer<BaseClassName,DerivedClassName> r##DerivedClassName(std::string(key))
