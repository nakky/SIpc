cmake = import('cmake')

inc = include_directories([
  './include',
  '../include',
  ])

srcs1 = [
  './src/example1.cpp',
]

srcs2 = [
  './src/example2.cpp',
]


deps = [
  sipc_dep,
]

if ['windows'].contains(host_machine.system())

elif ['darwin'].contains(host_machine.system())
  
elif ['linux'].contains(host_machine.system())

endif

executable(
  'example1',
  srcs1,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

executable(
  'example2',
  srcs2,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

