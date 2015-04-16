# Introduction #
If you don't have write access priviledges, ask an owner (e.g. daniel gutson at gmail) and state what modifications or extensions you want to implement.

# Details #

  1. do your change
  1. update CHANGELOG (see below)
  1. add yourself to CONTRIBUTORS
  1. if adding a new library file
    1. beware of the heading (Boost Software License), copy it from another file of mili
    1. use `NAMESPACE_BEGIN` and `NAMESPACE_END` (see other files)
    1. update mili.h
    1. update README (with the NO\_xxxxx)
    1. add an example.
    1. add a test.
  1. run all tests.
  1. update WIKI.


## How to update the CHANGELOG ##
You will have to either create a new version, or add a change to the current one.
The top version is either released or unreleased. If unreleased, the version has the UNRELEASED word.

Do the following regarding the version number, according with the type of change you are contributing, and depending the state of the release (UNRELEASED):

| | **released** | **UNRELEASED** |
|:|:-------------|:---------------|
|_adding a fix or minor change_|create a new minor version (i.e. `X.(Y+1) UNRELEASED`)| do nothing |
|_adding a new library_|create a new major version (i.e. `(X+1).Y UNRELEASED`)|if the future unreleased version number is minor, renumber it as major|

Then, add a bullet with your change.