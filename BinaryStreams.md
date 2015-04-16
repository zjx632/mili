# Introduction #

Use this library to pack different types of data into a single object using stream (i.e. << and >>) operators.

There are two ways to use this library:
  * Pack data into an output object (bostream) using <<.
  * Extract data from an input object (bistream) using >>.


# Details #

Output objects (where you **put** data into) provide an underlying string object containing the packed data and input objects (where you **take** data from) should be initialized with such a string.

This library is useful for communication between separate applications:
  * The sender applications packs the data it wants to communicate and send the underlying string object.
  * The receiver application constructs an input object from the string and loads the appropriate data from this object using the input stream operator >>.

The data must be extracted in the same order it was inserted in the first place.

# Limitations #

It is only possible to insert strings of up to 4GB because all sizes are truncated to 4 bytes in the stream.

In 32 bit machines (i.e. sizeof(size\_t) == 4) you can't extract data from bistreams over 4GB either.

These limitations are pretty far from current use cases however.

This library do not support neither maps nor multimaps. It is intended to be resolved in the future.

# Advanced Example #

A complete example is available in example\_binary-streams.cpp including many uses.