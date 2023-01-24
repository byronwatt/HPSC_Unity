all: build
	meson compile -C build
	build/byron hello=10

build:
	meson setup build

clean:
	rm -rf build

