/*
factory: A minimal library for a generic factory.
    Copyright (C) 2009  Daniel Gutson and Marcelo Caro, FuDePAN

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

template <class BaseClass, class Key>
class FactoryRegistry
{
private:
    Factory<Key, BaseClass> fc;
    static FactoryRegistry<BaseClass, Key>* instance;
    unsigned int users;

    template <class DerivedClass>
    void _register_factory(const Key& k)
    {
        users++;
        fc.register_factory<DerivedClass>(k);
    }
    BaseClass* _new_class(Key& k)
    {
        BaseClass* t;
        t = fc.new_class(k);
        return t;
    }
    bool _deregister_factory()
    {
        users--;
        return (users == 0);
    }
public:
    FactoryRegistry()
    {
        users = 0;
    }
    template<class DerivedClass>
    static void register_factory(const Key& k)
    {
        if (instance == NULL)
            instance = new FactoryRegistry<BaseClass, Key>;
        instance->_register_factory<DerivedClass>(k);
    }
    static BaseClass* new_class(Key& k)
    {
        BaseClass* t;
        t = instance->_new_class(k);
        return t;
    }
    static void deregister_factory()
    {
        if (instance->_deregister_factory())
            delete instance;
    }

};

template<class BaseClass, class DerivedClass, class Key>
class Registerer
{
public:
    Registerer(const Key& k)
    {
        mili::FactoryRegistry<BaseClass, Key>::template register_factory<DerivedClass>(k);
    }
    ~Registerer()
    {
        mili::FactoryRegistry<BaseClass, Key>::template deregister_factory();
    }
};

#define REGISTER_FACTORIZABLE_CLASS(BaseClassName, DerivedClassName, keytype, key) \
static mili::Registerer<BaseClassName,DerivedClassName,keytype> r##DerivedClassName(key)
