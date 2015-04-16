# Introduction #

This library provides the following string utilities:
  * normalized strings: given a character conversion function, the `normalized_string<function>` will use the function for comparisons. Two specializations are also provided:
    * `lstring`: string that holds lower-case strings.
    * `ustring`: string that holds upper-case strings.
  * `toupper(text)`, `tolower(text)`: functions that convert texts (std::strings, c-strings) to upper/lower case respectively, returning a std:string.
  * `size(text)`: function that returns the length of a text (any type). Useful for templates.
  * `begins_with(S, text)`, `ends_with(S, text)`: functions that return whether the string S begins/ends with `text` respectivelly. `S` can be either basic\_string, lstring, ustring. `text` can be any text type.
  * Text `<->` Numeric conversion functions: these functions are provided:
    * `to_string(number)`: converts `number` to std::string.
    * `from_string<type>(text)`: tries to convert `text` to `type`. Undefined value if `text` has an invalid format.
    * `from_string(text, value)`: returns `TRUE` if `text` can be converted to the type of `value`. If the conversion is possible, `value` holds the converted value (passed by reference).
  * `trim(string)`: returns a string without whitespace and tabs at both sides.
  * `substr(string, Pos_(number), Count_(number))`: returns the substring resulting of cut the input string starting in the position and has a length of `count` characters.
  * `substr(string, Pos_(number), Pos_(number))`: returns the substring resulting of cut the input string starting in the first position (2nd parameter) until the second position (3rd parameter).

The function `from_string` can be used to convert from string to numbers.

# Normalized Strings Details #

The `normalized_string` template class receives a normalizing function as its template parameter. The prototype of this function is
> `int (*)(int)`.
For example, C's Standard Library `tolower()` and `toupper()` match such prototype.

In fact, `lstring` and `ustring` use those functions as a their normalizer respectively. Therefore, they are case-insensitive when comparing against texts.

These classes are useful for associative containers. For example:
```
   map<lstring, int> m;
   m["hEllO"] = 1;

   cout << m["HEllo"];
```
will print `1` since `"hEllO"` matches with `"HEllo"` when both texts are converted to lowercase (that is what `lstring` does).   map<lstring, int> m;
   m["hEllO"] = 1;

   cout << m["HEllo"];
}}}```