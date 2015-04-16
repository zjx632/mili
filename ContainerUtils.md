# Introduction #

This library provides the following functions, optimized for each STL container type:
  * `find(container, element)`: returns a (const/non-const) **reference** to the element, if found, or throws `ElementNotFound` otherwise. Useful to avoid usage of iterators. Only available if exceptions are supported.
  * `find(container, element, nothrow)`: returns a (const/non-const) **pointer** to the element, if found, or `NULL` otherwise. Useful to avoid usage of iterators too.
  * `contains(container, element)`: returns `TRUE` if `element` is contained in `container`. Implements the rules described in Scott Meyers' "Effective STL" book.
  * `insert_into(container, element)`: inserts `element` into `container`, using the appropriate method depending on the container type.
  * `copy_container(from, to)`: copies the content of the container `from` to the container `to`. The containers need not to be of the same type.


Additionally, this library provides the following classes to treat different STL containers homogeneously:
  * `ContainerAdapter<T>`: interface to add elements of type `T` to an unknown container.
  * `ContainerAdapterImpl<T, ContainerType>`: Implementation of `ContainerAdapter<T>` with `ContainerType` container.

# Details #

Currently, at least the following containers are supported:
| **Container** | **`find()`** | **`contains()`** | **`insert_into()`** |
|:--------------|:-------------|:-----------------|:--------------------|
| vector | Y | Y | Y |
| list | Y | Y | Y |
| map | Y | Y | n |
| set | Y | Y | Y |
|unordered\_map | Y | Y | n |
|unordered set | Y | Y | Y |

`find` is specially useful in two situations:
  1. When used with `map`, since the `element` parameter is the key, so the mapped object is returned.
  1. When the elements have a custom comparison operator, so a shallow dumb element is used as a key, then the actual contained element is returned.


The container adapters are a tool to handle generic containers, without needing to know what type of container (vector, list, etc.) they are.
Users can call the `insert(const T&)` method to insert an element of type `T` without needing to know what container type is. The method returns a pointer to the just inserted element (not necessarily the parameter passed to the function).

This library was previously named "find-utils.h".