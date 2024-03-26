DESCRIPTION = "dbus examples to study dbus"
SECTION = "applications"
LICENSE = "CLOSED"

DEPENDS += "dbus"
RDEPENDS_${PN} += ""

SRC_URI = "git:///home/perso/igsong/myrepo/igsong-dbus-example;branch=master"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

PACKAGE_ARCH = "${MACHINE_ARCH}"
EXTRA_OECMAKE = ""

RM_WORK_EXCLUDE += "${PN}"
