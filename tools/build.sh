#!/bin/bash

ARCHITECTURE=$1
LIB_DIR=$2

PACKAGE_NAME="c3e"
VERSION="1.0.0"

PACKAGE_DIR="dist/${PACKAGE_NAME}_${VERSION}_${ARCHITECTURE}"
DEBIAN_DIR="${PACKAGE_DIR}/DEBIAN"

USR_DIR="${PACKAGE_DIR}/usr"
INCLUDE_DIR="${USR_DIR}/include/c3e"
BUILD_DIR="dist/build"
SO_FILE="${BUILD_DIR}/libc3e.so"

case "$ARCHITECTURE" in
    amd64)
        CROSS_COMPILE=""
        ;;
    armhf)
        CROSS_COMPILE="arm-linux-gnueabihf-"
        ;;
    riscv64)
        CROSS_COMPILE="riscv64-linux-gnu-"
        ;;
    *)
        echo -e "\033[93m[-]\033[0m Unsupported architecture: $ARCHITECTURE"
        exit 1
        ;;
esac

mkdir -p "${DEBIAN_DIR}"
mkdir -p "${INCLUDE_DIR}"
mkdir -p "${USR_DIR}/lib/${LIB_DIR}"
mkdir -p "${BUILD_DIR}"

echo -e "\033[92m[+]\033[0m Building shared library for ${ARCHITECTURE}..."
if [ "$ARCHITECTURE" = "amd64" ]; then
    gcc -shared -o "${SO_FILE}" -Iinclude src/c3e/*.c
else
    ${CROSS_COMPILE}gcc -shared -o "${SO_FILE}" -Iinclude src/c3e/*.c
fi

cp -r include/c3e/* "${INCLUDE_DIR}/"
cp "${SO_FILE}" "${USR_DIR}/lib/${LIB_DIR}/"

cat <<EOF > "${DEBIAN_DIR}/control"
Package: ${PACKAGE_NAME}
Version: ${VERSION}
Section: libs
Priority: optional
Architecture: ${ARCHITECTURE}
Depends: libc6 (>= 2.7)
Maintainer: Nathanne Isip <nathanneisip@gmail.com>
Description: C3E - Complex Compute Core Engine Library
 C3E (Complex Compute Core Engine) is a framework, platform,
 library, and an engine for handling complex computational
 tasks involving matrices, vectors, and tensors.
EOF

chmod 755 "${DEBIAN_DIR}"
chmod 755 "${USR_DIR}"
chmod 755 "${INCLUDE_DIR}"
chmod 755 "${USR_DIR}/lib/${LIB_DIR}"

dpkg-deb --build "${PACKAGE_DIR}" > /dev/null

rm -rf "${PACKAGE_DIR}"
rm -rf "${BUILD_DIR}"

echo -e "\033[92m[+]\033[0m Debian package for ${ARCHITECTURE} created successfully!"
