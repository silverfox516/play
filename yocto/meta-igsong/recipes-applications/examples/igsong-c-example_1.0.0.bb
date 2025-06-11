DESCRIPTION = "c examples"
SECTION = "applications"
LICENSE = "CLOSED"

DEPENDS += ""
RDEPENDS_${PN} += ""

SRC_URI = "file:///home/igsong/repo/github/play/yocto/c.tar.gz"

S = "${WORKDIR}/c"

inherit cmake pkgconfig

PACKAGE_ARCH = "${MACHINE_ARCH}"
EXTRA_OECMAKE = ""

RM_WORK_EXCLUDE += "${PN}"
