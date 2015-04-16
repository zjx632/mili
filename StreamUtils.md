# Introduction #

This minimal library provides two functionalities:
  * `istream >> vector`: reads streams of separated values into `std::vectors`
  * `ostream << vector`: writes the content of `std::vectors` into streams of values with any given separator.

Particularly, the reading algorithm is an all-terrain simple parser that manages to extract the data, no matter how it is separated (commas, or any whitespace combination).

# Details #

For both reading and writing, two ways are provided, the `Separator(vector, char)` manipulator can be optionally used. See specifics below.


## Reading ##
In order to read a stream into a vector, just use the `>>` operator.

Two ways are provided:
  1. using the `istream << vector` mode where the the library manages to detect the separator (not useful when mixing strings and commas, since the comma is interpreted as part of the string).
  1. using the `istream << Separator(vector, sep)` mode where the data separator is explicitly specified. (specially useful for reading CSVs with string fields).

```
   ifstream f("data");
   vector<float> v;

   while (f >> v)   // or while(f >> Separator(v, ','))
   {
      process(v);
      v.clear();
   }
```

Note that `f >> v` doesn't clear the previous vector values; instead, it appends the data to them.
This should work with any `istream` class. Particularly, was tested with `ifstream`.

## Writing ##

Two ways are provided:
  1. using the `ostream >> vector` mode where the generated output is a CSV (comma-separated values).
  1. using the `ostream >> Separator(vector, sep)` mode where the data separator is explicitly specified.

For example:
```
   vector<float> v;
   fill(v);

   cout << v << endl;                   /* values separated by commas */
   cout << Separator(v, '\t') << endl;  /* values separated by tabs */
```