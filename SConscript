Import ('env')

name = 'mili'
inc = env.Dir('.')
src = []
deps = []

env.AppendUnique(CPPFLAGS = ['-DMILI_NAMESPACE'])
env.CreateHeaderOnlyLibrary(name, inc, deps)

