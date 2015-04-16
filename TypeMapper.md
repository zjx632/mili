# Introduction #

Sometimes you need to map types into other types, for example to avoid code bloats due to templates.

This library provides very simple declarations to ease the creation and definition of type mappers.

# Details #

To create a type mapper, call
```
   declare_type_mapper(mapper_name);
```

To add mappings, call:
```
   add_mapping(mapper_name, from_type, to_type);
```

To add a generic pointer mapping (so every pointer gets mapped to the same type), call:
```
   add_mapping_for_pointers(mapper_name, to_type);
```

To use the mapper (specially when a `typename` is required), call
```
   map_type(mapper_name, from_type)
```

## `BasicType` type mapper ##

A type mapper named `Basictype` is provided. This mapper removes the `const` and reference (if any) from a type, thus returning the 'clean' basic type.


# Example #
```
declare_type_mapper(TypeMapper);
add_mapping(TypeMapper, char, int);
add_mapping(TypeMapper, unsigned int, int);
add_mapping(TypeMapper, short int, int);
add_mapping_for_pointers(TypeMapper, int);

template <class T>
class MyVector : public std::vector<map_type(TypeMapper, T)>
{};

int main()
{
    MyVector<short int> v1;
    MyVector<float> v2;

    v1.push_back(1);
    v2.push_back(1.0f);

    return 0;
}
```