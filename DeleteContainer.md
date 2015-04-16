# Introduction #

This library defines a set of functions to delete the content of an STL container
containing pointers to objects.

# Details #

Two functions exist:
  * `delete_container(`_container_`)`
  * `vector_delete_container(`_container_`)`


`delete_container` just applies the `delete` operator to each element of _container_.
`vector_delete_container` applies the `delete []` operator to each element.

After deleting the elements, the _container_ is cleared, leaving it empty.

Additionally, two classes exist:
  * `auto_delete_container<Container>`
  * `auto_vector_delete_container<Container>`

These classes just wrap the STL container `Container`, and invoke `delete_container()` and `vector_delete_container()` respectivelly in the destructor.