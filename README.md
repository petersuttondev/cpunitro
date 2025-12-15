# cpunitro

A Linux utility that sets all CPU frequency scaling governors to `performance`.

* If it's not run as root, it automatically re-runs itself under `sudo`.


## Building

```
$ cd /path/to/repo
$ meson setup build
$ ninja -C build
```


## Running

```
$ ./build/cpunitro
```
