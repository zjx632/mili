Import ('env')

name = 'mili'
inc = env.Dir('.')
ext_inc = env.Dir('mili')
src = []
deps = []

env.AppendUnique(CPPFLAGS = ['-DMILI_NAMESPACE'])
env.CreateHeaderOnlyLibrary(name, inc, ext_inc, deps)

