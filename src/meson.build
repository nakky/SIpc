sipc_inc = include_directories('../include')

sipc_srcs = [
  'SharedMemory.cpp',
  'Process.cpp',
]


sipc_lib = static_library('sipc',
                sipc_srcs,
                install: true,
                include_directories: sipc_inc,
                cpp_args: cpp_define_args
                )
