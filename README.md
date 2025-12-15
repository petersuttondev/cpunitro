# cpunitro

A Linux utility that sets all CPU frequency scaling governors to `performance`.

* If it's not run as root, it automatically re-runs itself under `sudo`.
* Requires [Microsoft's GSL](https://github.com/microsoft/GSL)


## Build

```
$ cd /path/to/repo
$ meson setup build
$ ninja -C build
```


## Run

```
$ ./build/cpunitro
```
