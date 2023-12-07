# S3DMath

SIpc is a portable interprocess communication library, available for Unix-like OSx.

## How to build

### Meson

SIpc uses meson as the build system.
In order to use the new version, it is recommended to install with pip.

```
$ pip3 install meson
$ pip3 install ninja
```

### Meson - build

You can run the build command in the SIpc root folder.

```
$ meson build
$ ninja -C build
```

### Meson - subdir

Download it as a submodule in your project.

```
Project
├─ modules/
│  └─ SIpc/
│     └─ meson.build
└─meson.build
```

Call in subdir for the "src" folder in your project's meson.build.

```
subdir('modules/SIpc/src')
```

Variable ”sipc_lib” can be used for linking.

```
sipc_dep = declare_dependency(link_with: sipc_lib)
...
deps = [
  sipc_dep,
...
}
executable(
...
  dependencies: deps,
...
)
```

Run the following command in the root folder of the project.

```
$ meson build
$ ninja -C build
```
